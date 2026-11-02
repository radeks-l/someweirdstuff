/*
 * main.cpp
 *
 *  Created on: 30 sie 2016
 *      Author: Radek
 */

#include "permutations.hpp"
#include "unionfind.hpp"
#include "StopWatch.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <cstring>
#include <list>
#include <thread>

typedef int VertexId;
typedef Node::VertexValue VertexValue;
typedef std::unordered_map<VertexValue, VertexId> VertexHashMap;
typedef std::unordered_map<VertexValue, Node> NodesHashMap;
typedef std::pair<VertexValue, VertexValue> Edge;

namespace std
{

template<>
struct hash<Node> {
    size_t operator()(const Node &node) const noexcept {
        return static_cast<size_t>(node.mValue);
    }
};

template<>
struct hash<Edge> {
    size_t operator()(const Edge &edge) const noexcept {
        static_assert(sizeof(size_t) >= sizeof(uint64_t),
                "Provide better hash function!");
        return static_cast<size_t>(
                static_cast<uint64_t>(edge.first) |
                (static_cast<uint64_t>(edge.second) << 32) );
    }
};
} // namespace std

typedef std::unordered_set<Edge> EdgeSet;
typedef EdgeSet::iterator EdgeSetIt;

VertexValue getNodeValue(const std::string &line, const int numOfBits) noexcept {
    VertexValue result = 0;
    std::uint32_t mask = 0x01 << (numOfBits - 1);

    if (numOfBits > 0 && (false == line.empty())) {
        auto size = line.size();
        decltype(size) it = 0;
        while (it < size) {
            result += (line[it] - '0') * mask;
            it += 2;
            mask >>= 1;
        }
    }
    return result;
}

void loadDataFromFile(const std::string &fileName, VertexHashMap &vertices) {
    std::ifstream inputFile(fileName);
    std::string line;
    std::size_t numOfNodes = 0;
    int numOfBits = 0;

    if (!inputFile) {
        throw std::runtime_error("Open file error!");
    }
    std::getline(inputFile, line);
    std::istringstream lineStream(line);
    lineStream >> numOfNodes;
    lineStream >> numOfBits;
    vertices.reserve(numOfNodes);
    VertexId it = 0;
    while (std::getline(inputFile, line)) {
        vertices[getNodeValue(line, numOfBits)] = ++it;
    }
}

template<typename Container>
void printSize(const std::string &msg, const Container &cont) {
    std::cout << msg << ": " << cont.size() << "." << std::endl;
}

void processVerticess(
        const VertexHashMap &vertices,
        VertexHashMap::const_iterator start,
        VertexHashMap::const_iterator end,
        NodesHashMap &allNodes,
        EdgeSet &edges) {
    PermutationsGenerator generator(24);
    for( ; start != end; ++start) {
        PermutationsResult permForOneVertex = generator(start->first);
        for (auto& perm : permForOneVertex) {
            auto secondNodeOfEdgeIt = vertices.find(std::get<0>(perm));
            auto distance = std::get<1>(perm);
            if (vertices.end() != secondNodeOfEdgeIt) {
                // create node for each vertex, first and second
                Node first(start->first);
                Node second(std::get<0>(perm));
                // > create container for nodes, eg hash table
                allNodes.insert({first.mValue, first});
                allNodes.insert({second.mValue, second});
                // > store edges in container, eg hashtable
                if (first.mValue < second.mValue) {
                    edges.insert(
                            std::make_pair(first.mValue, second.mValue));
                } else {
                    edges.insert(
                            std::make_pair(second.mValue, first.mValue));
                }
            }
        }
    }
}

void mergeNodes(const EdgeSet &edges, NodesHashMap& allNodes,
        std::list<std::pair<Node, Node>> &merged) {
    for(auto &it: allNodes) {
        unionCreate(it.second);
    }
    for (auto edge = edges.begin(), end = edges.end(); edge != end; ++edge) {
        Node& u = allNodes[edge->first];
        Node& v = allNodes[edge->second];
        if (unionFind(u) != unionFind(v)) {
            merged.push_back({u, v});
            unionMerge(u, v);
        }
    }
}

void doJobInOneThread(const VertexHashMap &vertices) {
    NodesHashMap allNodes;
    EdgeSet edges;
    std::list<std::pair<Node, Node>> merged;
    allNodes.reserve(vertices.size());
    edges.reserve(vertices.size());

    processVerticess(vertices, vertices.cbegin(), vertices.cend(), allNodes, edges);
    mergeNodes(edges, allNodes, merged);
    std::cout << "Edges: " << edges.size() << ". Merged: " << merged.size() << "." << std::endl;
}

void doJobInMultipleThreads(const VertexHashMap &vertices) {
    constexpr int NUM_OF_THREADS = 5;
    const int NUM_OF_VERTIVES = vertices.size();
    const int NUM_PER_THREAD = NUM_OF_VERTIVES / NUM_OF_THREADS;

    std::vector<std::thread> threads;
    std::vector<NodesHashMap> allNodesThreads(NUM_OF_THREADS);
    std::vector<EdgeSet> edgesThreads(NUM_OF_THREADS);
    for(auto &it: allNodesThreads) {
        it.reserve(NUM_PER_THREAD);
    }
    auto begin = vertices.begin();
    auto end = begin;
    for(int i = 0; i < NUM_OF_THREADS; ++i) {
        std::advance(end, NUM_PER_THREAD);
        threads.push_back(
                std::thread(processVerticess,
                            vertices,
                            begin,
                            end,
                            std::ref(allNodesThreads[i]),
                            std::ref(edgesThreads[i])) );
        begin = end;
    }

    for(auto &it: threads) {
        it.join();
    }
    NodesHashMap allNodes;
    EdgeSet edges;
    for(auto &it: allNodesThreads) {
        allNodes.insert(it.begin(), it.end());
    }
    for(auto &it: edgesThreads) {
        edges.insert(it.begin(), it.end());
    }
    // create union and process nodes according to algorithm
    std::list<std::pair<Node, Node>> merged;
    mergeNodes(edges, allNodes, merged);

    std::cout << "Edges: " << edges.size() << ". Merged: " << merged.size() << "." << std::endl;
}

int main(int argc, char **argv) {
    int EXIT_RESULT = 0;
    bool isTest = false;
    if (argc > 1) {
        if (0 == std::strcmp("test", argv[1])) {
            isTest = true;
        }
    }
    if (isTest) {
        PermutationsTest();
        return 0;
    }

    try {
        std::string fileName("clustering_big.txt");
        VertexHashMap vertices;

        {
            StopWatch loadFile("reading data from file");
            loadDataFromFile(fileName, vertices);
        }
        {
            StopWatch oneThread("solve with one thread");
            doJobInOneThread(vertices);
        }
        {
            StopWatch multithreaded("multithreaded");
            doJobInMultipleThreads(vertices);
        }
    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
        EXIT_RESULT = -1;
    }
    return EXIT_RESULT;
}

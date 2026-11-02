/*
 * unionfind.hpp
 *
 *  Created on: 17 wrz 2016
 *      Author: Radek
 */

#ifndef UNIONFIND_HPP_
#define UNIONFIND_HPP_

#include <cstdint>

/* simple Node type */

struct Node {
    typedef std::uint32_t VertexValue;

    Node(): Node(0) {}
    Node(VertexValue value):
        mValue(value), mRank(0), mParent(nullptr) {}

    bool operator == (const Node &rhs) const noexcept {
        return mValue == rhs.mValue;
    }

    bool operator < (const Node &rhs) const noexcept {
        return (mValue < rhs.mValue);
    }

    VertexValue mValue;
    int mRank;
    Node *mParent;
};

/* functions to manage UNION/FIND data structure */

void unionCreate(Node &node) noexcept;

Node *unionFind(const Node &node) noexcept;

void unionMerge(Node &first, Node &second) noexcept;

#endif /* UNIONFIND_HPP_ */

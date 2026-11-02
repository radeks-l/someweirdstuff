/*
 * unionfind.cpp
 *
 *  Created on: 30 sie 2016
 *      Author: Radek
 */

#include "unionfind.hpp"


void unionCreate(Node &node) noexcept {
    if (nullptr == node.mParent) {
        node.mParent = &node;
    }
}

Node *unionFind(const Node &node) noexcept {
    if (&node == node.mParent) {
        return node.mParent;
    } else {
        return unionFind(*node.mParent);
    }
}

void unionMerge(Node &first, Node &second) noexcept {
    auto parentFirst = unionFind(first);
    auto parentSecond = unionFind(second);
    if (parentFirst == parentSecond) {
        return;
    }
    if (parentFirst->mRank > parentSecond->mRank) {
        parentSecond->mParent = parentFirst;
    } else if (parentFirst->mRank < parentSecond->mRank) {
        parentFirst->mParent = parentSecond;
    } else {
        parentFirst->mRank++;
        parentSecond->mParent = parentFirst;
    }
}

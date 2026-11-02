#include <iostream>

struct Node {
   int data;
   Node* next;
};

Node *reverseList(Node *head)
{
    Node *_next = head;
    Node *_prev = nullptr;
    Node *_tempNext = nullptr;
    while (_next != nullptr) {
        _tempNext = _next->next;
        _next->next = _prev;
        _prev = _next;
        _next = _tempNext;
    }
    return _prev;
}

int FindMergeNode(Node *headA, Node *headB)
{
    headA = reverseList(headA);
    headB = reverseList(headB);

    int retVal = 0;
    while (headA != nullptr && headB != nullptr &&
           headA->data == headB->data) {

        headA = headA->next;
        if (headA != nullptr)
            retVal = headB->data;
        headB = headB->next;
    }
    return retVal;
}

Node *addToList(Node *head, int value) {
    Node *next = head;
    Node *prev = nullptr;

    while (next != nullptr) {
        prev = next;
        next = next->next;
    }
    auto *newNode = new Node{value, nullptr};
    if (nullptr != prev) {
        prev->next = newNode;
    } else {
        head = newNode;
    }
    return head;
}

int main(void) {
    Node *listA = nullptr;
    Node *listB = nullptr;

    listA = addToList(listA, 1);
    listA = addToList(listA, 2);
    listA = addToList(listA, 3);
    listA = addToList(listA, 6);
    listA = addToList(listA, 7);
    listA = addToList(listA, 8);

    listB = addToList(listB, 4);
    listB = addToList(listB, 5);
    listB = addToList(listB, 6);
    listB = addToList(listB, 7);
    listB = addToList(listB, 8);

    std::cout << FindMergeNode(listA, listB) << std::endl;

    Node *listC = nullptr;
    Node *listD = nullptr;

    listC = addToList(listC, 1);
    listC = addToList(listC, 2);
    listC = addToList(listC, 3);

    listD = addToList(listD, 1);
    listD = addToList(listD, 2);
    listD = addToList(listD, 3);

    std::cout << FindMergeNode(listC, listD) << std::endl;
    return 0;
}

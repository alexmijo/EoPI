#include <memory>
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
struct ListNode {
    T data;
    shared_ptr<ListNode<T>> next = nullptr;
};

template <typename T>
shared_ptr<ListNode<T>> linkedListFromVector(const vector<T>& vec) {
    shared_ptr<ListNode<T>> list = nullptr;
    for (int i = vec.size() - 1; i >= 0; i--) {
        shared_ptr<ListNode<T>> node = make_shared<ListNode<T>>();
        node->data = vec[i];
        node->next = list;
        list = node;
    }
    return list;
}

template <typename T>
void printLinkedList(shared_ptr<ListNode<T>> list) {
    while (list != nullptr) {
        if (list->next == nullptr) {
            cout << list->data;
        } else {
            cout << list->data << " ";
        }
        list = list->next;
    }
    cout << endl;
}

// 8.1
// I got the best solution, I took a little too long but I was going slower than I would've been in
//  an interview. O(min(m, n)), aka O(m + n).
// I do not understand why in their solution they are passing pointers to shared_ptrs. It's as if
//  shared_ptrs aren't actually pointers (i.e., they are value types for the actual thing they
//  hold), which doesn't make any sense. Edit: OK actually I figured that out, they say on page 485
//  that "Input arguments to functions are either values or const references. We never allow
//  non-const references, except when required by convention, e.g., swap(). We use pointers to pass
//  output arguments to functions. (This is motivated by not wanting readers to have to go to the
//  function source code to see if an argument is updated by the called function." I think I won't
//  follow that convention, so actually what I did below was fine. One thing I still don't
//  understand is why they passed head into ReverseLinkedList() on page 112 as a const reference
//  instead of just by value. Like, do they just do that for all non-primitive types where they are
//  able to have the parameter be const? Actually, probably yes. 
// Their code was nicer than mine.
template <typename T>
shared_ptr<ListNode<T>> merge(shared_ptr<ListNode<T>> list1, shared_ptr<ListNode<T>> list2) {
    if (list1 == nullptr) {
        return list2;
    }
    if (list2 == nullptr) {
        return list1;
    }
    shared_ptr<ListNode<T>> mergedList;
    shared_ptr<ListNode<T>> currentNode;
    if (list1->data < list2->data) {
        mergedList = list1;
        list1 = list1->next;
    } else {
        mergedList = list2;
        list2 = list2->next;
    }
    currentNode = mergedList;
    while(true) {
        if (list1 == nullptr) {
            currentNode->next = list2;
            break;
        }
        if (list2 == nullptr) {
            currentNode->next = list1;
            break;
        }
        if (list1->data < list2->data) {
            currentNode->next = list1;
            list1 = list1->next;
        } else {
            currentNode->next = list2;
            list2 = list2->next;
        }
        currentNode = currentNode->next;
    }
    return mergedList;
}

// For 8.2 I was actually able to figure out the algorithm for the best solution really quickly.
//  That problem (and the above one) actually seem really easy if it weren't for dealing with
//  shared_ptrs.

int main() {
    vector<int> vec1 = {0, 3, 5, 6, 7, 9};
    vector<int> vec2 = {1, 2, 4, 8};
    shared_ptr<ListNode<int>> list1 = linkedListFromVector(vec1);
    shared_ptr<ListNode<int>> list2 = linkedListFromVector(vec2);
    printLinkedList(list1);
    printLinkedList(list2);
    printLinkedList(merge(list1, list2));
}
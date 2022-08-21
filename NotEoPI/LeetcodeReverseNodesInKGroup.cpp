#include <vector>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* linkedListFromVector(const vector<int>& vec) {
    ListNode* list = nullptr;
    for (int i = vec.size() - 1; i >= 0; i--) {
        ListNode* node = new ListNode;
        node->val = vec[i];
        node->next = list;
        list = node;
    }
    return list;
}

void printLinkedList(ListNode* list) {
    while (list != nullptr) {
        if (list->next == nullptr) {
            cout << list->val;
        } else {
            cout << list->val << " ";
        }
        list = list->next;
    }
    cout << endl;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) {
            return head;
        }
        ListNode* prevKOrigStart = head;
        ListNode* curr = head;
        ListNode* result = head;
        while (true) {
            if (!curr) {
                break;
            }
            ListNode* thisKOrigStart = curr;
            ListNode* prev = curr;
            if (!curr->next) {
                if (curr != head) {
                    prevKOrigStart->next = curr;
                }
                break;
            }
            curr = curr->next;
            bool reachedEnd = false;
            for (int i = 1; i < k; i++) {
                if (!curr) {
                    reachedEnd = true;
                    ListNode* temp = prev;
                    prev = curr;
                    curr = temp;
                    for (int j = 0; j < i - 1; j++) {
                        ListNode* next = curr->next;
                        curr->next = prev;
                        prev = curr;
                        curr = next;
                    }
                    if (thisKOrigStart != head) {
                        prevKOrigStart->next = thisKOrigStart;
                    }
                    break;
                }
                ListNode* next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            if (reachedEnd) {
                break;
            }
            if (thisKOrigStart != head) {
                prevKOrigStart->next = prev;
            } else {
                result = prev;
            }
            prevKOrigStart = thisKOrigStart;
            if (!curr) {
                thisKOrigStart->next = nullptr;
            }
        }
        return result;
    }
};

int main() {
    vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    ListNode* list1 = linkedListFromVector(vec1);
    printLinkedList(list1);
    Solution s;
    printLinkedList(s.reverseKGroup(list1, 3));
}
// Did well but took too long to do it, however that was only cause of dumb simple bugs. I thought
//  of the correct algorithm very quickly.
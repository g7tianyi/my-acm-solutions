#include <algorithm>
#include <iostream>

/**
 * Definition for singly-linked list.
 */struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) :
            val(x), next(NULL) {
    }
    ListNode() :
            val(0), next(NULL) {
    }
};
class Solution {
public:
    typedef ListNode* pointer;
    pointer reverseKGroup(pointer head, int k) {
        if (head == NULL) {
            return NULL;
        }

        pointer curr = head;
        int length = 0;
        while (curr) {
            ++length;
            curr = curr->next;
        }

        if (k > length) {
            return head;
        }

        int count = 0;
        curr = head;
        pointer newHead = head;
        pointer prevTail = NULL, currTail = head;
        pointer prev = NULL, next;
        while (curr) {
            next = curr->next; // reserve the reference for the next
            curr->next = prev; // reverse curr pointer to the prev
            ++count;
            if (count % k == 0) {
                if (prevTail) {
                    // "split (group) point" in the middle of the list
                    //  ... 1 -> 2 -> 3 -> 4 -> 5
                    //                    curr
                    //                     |
                    //      1 <- 2    3 <- 4    5
                    //      |    |    |         |
                    // prevTail head currTail next
                    prevTail->next = curr;
                    prevTail = currTail;
                } else {
                    // "split (group) point" in the very begining
                    //           1 -> 2 -> 3 -> 4 -> 5
                    //              curr
                    //                |
                    //   NULL <- 1 <- 2    3 -> 4 -> 5
                    //     |     |         |
                    // prevTail currTail  next
                    prevTail = currTail;
                    newHead = curr;
                }
                prev = NULL;
                curr = next;
                currTail = next;
                if (length - count < k) {
                    break;
                }
            } else {
                prev = curr;
                curr = next;
            }
        }

        if (prevTail) {
            prevTail->next = curr;
        } else {
            prevTail = curr;
        }

        return newHead;
    }
};

Solution solu;

ListNode nodes[10];

inline void link() {
    for (int i = 0; i < 9; ++i) {
        nodes[i].val = i + 1;
        nodes[i].next = &nodes[i + 1];
    }
    nodes[9].val = 10;
    nodes[9].next = NULL;
}

inline void print(ListNode* head) {
    while (head) {
        std::cout << head->val << ' ';
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    ListNode* head;

    for (int i = 0; i < 10; ++i) {
        link();
        head = solu.reverseKGroup(&nodes[0], i + 1);
        print(head);
    }

    link();
    nodes[4].next = NULL;
    head = solu.reverseKGroup(&nodes[0], 3);
    print(head);

    link();
    head = solu.reverseKGroup(&nodes[0], 12);
    print(head);

    return 0;
}


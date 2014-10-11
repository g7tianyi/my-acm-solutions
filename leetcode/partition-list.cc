#include <algorithm>
#include <iostream>
#include <vector>
using std::vector;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() :
            val(0), next(NULL) {
    }
    ListNode(int x) :
            val(x), next(NULL) {
    }
};

typedef ListNode* pointer;

class Solution {
public:
    pointer partition(pointer head, int key) {
        pointer small = NULL, large = NULL;
        pointer scurr = NULL, lcurr = NULL;
        pointer curr = head, next;
        while (curr) {
            next = curr->next;
            if (curr->val < key) {
                if (small) {
                    scurr->next = curr;
                    scurr = scurr->next;
                } else {
                    small = curr;
                    scurr = small;
                }
            } else {
                if (large) {
                    lcurr->next = curr;
                    lcurr = lcurr->next;
                } else {
                    large = curr;
                    lcurr = large;
                }
            }
            curr->next = NULL;
            curr = next;
        }

        if (small) {
            scurr->next = large;
            return small;
        } else {
            return large;
        }
    }
};
Solution sol;

int const MAX_NODE = 20;
ListNode nodes[MAX_NODE];

void init() {
    srand((unsigned) time(0));
    for (int i = 0; i < MAX_NODE; ++i) {
        nodes[i].val = std::abs(rand()) % (MAX_NODE << 1);
    }
}

void chain() {
    for (int i = 0; i < MAX_NODE - 1; ++i) {
        nodes[i].next = &nodes[i + 1];
    }
    nodes[MAX_NODE - 1].next = NULL;
}

void print(pointer head) {
    while (head) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

#include <ctime>

int main() {
    init();
    for (int i = 0; i < MAX_NODE; ++i) {
        chain();
        pointer head = &nodes[0];
        print(head);
        std::cout << nodes[i].val << std::endl;
        head = sol.partition(&nodes[0], nodes[i].val);
        print(head);
        std::cout << std::endl;
    }
    return 0;
}


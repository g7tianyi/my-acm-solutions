#include <algorithm>
#include <iostream>
#include <deque>

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

class Solution {
public:
    typedef ListNode* nodeptr;
public:
    ListNode* deleteDuplicates(ListNode* head) {
        nodeptr prev = NULL, curr = head, next;
        while (curr) {
            next = curr->next;
            if (prev && prev->val == curr->val) {
                prev->next = next;
            } else {
                prev = curr;
            }
            curr = next;
        }
        return head;
    }
};

Solution solution;

ListNode nodes[10];

int main() {
    nodes[0].val = 1, nodes[0].next = &nodes[1];
    nodes[1].val = 1, nodes[1].next = &nodes[2];
    nodes[2].val = 2, nodes[2].next = &nodes[3];
    nodes[3].val = 2, nodes[3].next = &nodes[4];
    nodes[4].val = 3, nodes[4].next = &nodes[5];
    nodes[5].val = 4, nodes[5].next = &nodes[6];
    nodes[6].val = 4, nodes[6].next = &nodes[7];
    nodes[7].val = 4, nodes[7].next = &nodes[8];
    nodes[8].val = 4, nodes[8].next = &nodes[9];
    nodes[9].val = 5, nodes[9].next = NULL;

    ListNode* head = solution.deleteDuplicates(&nodes[0]);
    while (head) {
        printf("%d -> ", head->val);
        head = head->next;
    }

    return 0;
}


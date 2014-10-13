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

    pointer deleteDuplicates(pointer head) {
        if (head == NULL) {
            return head;
        }

        pointer prev = NULL, curr = head, next = head->next;
        while (curr && next) {
            if (curr->val == next->val) {
                pointer temp = next->next;
                while (temp && temp->val == curr->val) {
                    temp = temp->next;
                }

                if (prev) {
                    prev->next = temp;
                } else {
                    head = temp;
                }
                curr = temp;
                next = temp ? temp->next : NULL;
            } else {
                prev = curr;
                curr = next;
                next = curr->next;
            }
        }

        return head;
    }
};

Solution solu;

ListNode nodes[9];

void link() {
    for (int i = 0; i < 8; ++i) {
        nodes[i].next = &nodes[i + 1];
    }
    nodes[8].next = NULL;
}

void print(ListNode* head) {
    while (head) {
        std::cout << head->val << ' ';
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {

    nodes[0].val = 1, nodes[1].val = 1, nodes[2].val = 1;
    nodes[3].val = 2, nodes[4].val = 2, nodes[5].val = 3;
    nodes[6].val = 4, nodes[7].val = 5, nodes[8].val = 5;

    ListNode* head;
    head = solu.deleteDuplicates(&nodes[0]);
    print(head);

    link();
    head = solu.deleteDuplicates(&nodes[0]);
    print(head);

    link();
    nodes[0].val = 1, nodes[1].val = 1, nodes[2].val = 1;
    nodes[3].val = 1, nodes[4].val = 1, nodes[5].val = 1;
    nodes[6].val = 1, nodes[7].val = 1, nodes[8].val = 1;
    head = solu.deleteDuplicates(&nodes[0]);
    print(head);

    return 0;
}


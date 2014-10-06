#include <iostream>

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
    bool hasCycle(ListNode* head) {
        nodeptr slow = head, fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }
};
Solution solution;

ListNode nodes[10];

int main() {
    // initialize
    for (int i = 0; i < 10; ++i) {
        nodes[i].val = i;
    }

    // chaining nodes
    for (int i = 0; i < 9; ++i) {
        nodes[i].next = &nodes[i + 1];
    }
    std::cout << "Test no loop => " << solution.hasCycle(&nodes[0])
            << std::endl;

    // make a loop
    nodes[9].next = &nodes[6];
    std::cout << "Test looped  => " << solution.hasCycle(&nodes[0])
            << std::endl;

    return 0;
}


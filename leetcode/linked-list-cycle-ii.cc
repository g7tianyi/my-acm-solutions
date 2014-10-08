#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
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
class Solution {
public:
    typedef ListNode* nodeptr;
    ListNode *detectCycle(ListNode *head) {
        nodeptr slow = head, fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                break;
            }
        }
        if (!fast || !fast->next) {
            return NULL;
        }

        // grab a pen and draw an illustration...
        //
        // the time when fast and slow meet with each other,
        // journey of slow is, S
        // hourney of fast is, 2S = S + n * R
        // n is the count fast has been travelled in the cycle
        // R is the length of the cycle
        //
        // also note the whole length of the list to be L,
        // X to be the length of the meeting point to the node where the cycle begins
        // A to be the length of the start to the node where the cycle begins
        //
        // A + X = n * R = (n - 1) * R + R = (n - 1) * R + L - A
        // ==> A = (n - 1) * R + (L - A - X)
        // (L - A - X) is the length of the meeting point to the node where the cycle begins
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
    }
};

static Solution solution;

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
    ListNode* node = solution.detectCycle(&nodes[0]);
    std::cout << "Test no loop => ";
    if (node == NULL) {
        std::cout << "NULL";
    } else {
        std::cout << node->val;
    }
    std::cout << std::endl;

    // make a loop
    nodes[9].next = &nodes[6];
    std::cout << "Test looped  => ";
    node = solution.detectCycle(&nodes[0]);
    if (node == NULL) {
        std::cout << "NULL";
    } else {
        std::cout << node->val;
    }
    std::cout << std::endl;

    return 0;
}


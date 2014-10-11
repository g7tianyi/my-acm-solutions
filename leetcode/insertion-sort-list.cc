#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using std::string;
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

void print(pointer head);

class Solution {
public:
    pointer insertionSortList(pointer head) {
        if (head == NULL || head->next == NULL) {
            return head;
        }

        pointer prev = head, curr = head->next, next;
        pointer pref, curf; // f means former
        while (curr) {
            next = curr->next;

            pref = NULL, curf = head;
            while (curf != curr && curr->val > curf->val) {
                pref = curf;
                curf = curf->next;
            }

            if (curf == curr) {
                // curr is the largest one, just move one
                prev = curr;
                curr = next;
                continue;
            }

            if (curf == head) {
                // curr is the smallest one, update the header
                curr->next = head;
                head = curr;
            } else if (curf != curr) {
                // insert curr into an intermediate position
                curr->next = curf;
                pref->next = curr;
            }

            prev->next = next;
            curr = next;
        }

        return head;
    }
};
Solution sol;

#include <ctime>
#include <unistd.h>
int const MAX_NODE = 20;
ListNode nodes[MAX_NODE];

void init() {
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
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

int main() {
    for (int i = 0; i < MAX_NODE; ++i) {
        init();
        chain();
        pointer head = &nodes[0];
        print(head);
        head = sol.insertionSortList(&nodes[0]);
        print(head);
        std::cout << std::endl;
        usleep(1000 * 1000);
    }
    return 0;
}


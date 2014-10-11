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
    void reorderList(pointer head) {
        if (head == NULL || head->next == NULL) {
            return;
        }

        int length = 0;
        pointer hCurr = head;
        while (hCurr) {
            ++length;
            hCurr = hCurr->next;
        }

        int i = 1, half = (length + 1) >> 1;
        pointer former = head, fCurr = former; // curr for former
        hCurr = head->next;
        while (i++ < half) {
            fCurr->next = hCurr;
            fCurr = fCurr->next;
            hCurr = hCurr->next;
        }
        fCurr->next = NULL; // don't forget this, make sure the former list has an end

        // latter must be initialized to be NULL, to ensure the latter list has an end
        pointer latter = NULL, lCurr; // curr for latter
        pointer hNext; // next for original list
        while (hCurr) { // reverse the list
            hNext = hCurr->next;
            hCurr->next = latter;
            latter = hCurr;
            hCurr = hNext;
        }

        pointer fNext, lNext; // next for former, next for latter
        fCurr = former, lCurr = latter;
        while (fCurr && lCurr) {
            fNext = fCurr->next; // former next
            lNext = lCurr->next; // latter next

            fCurr->next = lCurr;
            lCurr->next = fNext;

            fCurr = fNext;
            lCurr = lNext;
        }
    }
};

Solution sol;

#include <ctime>
#include <unistd.h>
int const MAX_NODE = 20;
ListNode nodes[MAX_NODE];

void randomInit() {
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
    for (int i = 0; i < MAX_NODE; ++i) {
        nodes[i].val = std::abs(rand()) % (MAX_NODE << 1);
    }
}

void standardInit(int size) {
    for (int i = 0; i < size; ++i) {
        nodes[i].val = i + 1;
    }
}

void chain(int size) {
    for (int i = 0; i < size - 1; ++i) {
        nodes[i].next = &nodes[i + 1];
    }
    nodes[size].next = NULL;
}

void print(pointer head) {
    while (head) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    for (int i = 1; i <= MAX_NODE; ++i) {
        standardInit(i);
        chain(i);
        print(&nodes[0]);
        sol.reorderList(&nodes[0]);
        print(&nodes[0]);
        std::cout << std::endl;
        usleep(1000 * 1000);
    }
    return 0;
}


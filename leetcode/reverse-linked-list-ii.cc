#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
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

class Solution {
public:
    typedef ListNode* pointer;
    ListNode *reverseBetween(ListNode *head, int start, int end) {
        if (head == NULL) {
            return head;
        }

        int count = 1;
        pointer prev = NULL, curr = head;
        while (curr && count < start) {
            prev = curr;
            curr = curr->next;
            ++count;
        }
        pointer rbegin = curr; // reversed begin

        pointer next = curr ? curr->next : NULL;
        while (curr && count < end) {
            curr = next;
            next = curr->next;
            ++count;
        }
        pointer rend = curr; // reversed end

        curr = rbegin;
        pointer rprev = NULL, rnext;
        while (curr != rend) {
            rnext = curr->next;
            curr->next = rprev;
            rprev = curr;
            curr = rnext;
        }
        curr->next = rprev;

        if (rbegin) {
            rbegin->next = next;
        }
        if (prev) {
            prev->next = rend;
        } else {
            head = rend;
        }
        return head;
    }
};

Solution solu;

ListNode nodes[9];

void init() {
    for (int i = 0; i < 9; ++i) {
        nodes[i].val = i + 1;
    }
}

void rechain() {
    for (int i = 0; i < 8; ++i) {
        nodes[i].next = &nodes[i + 1];
    }
    nodes[8].next = NULL;
}

void print(ListNode* head) {
    ListNode* curr = head;
    while (curr) {
        std::cout << curr->val << ' ';
        curr = curr->next;
    }
    std::cout << std::endl;
}

void test(int start, int end) {
    std::cout << "reverse " << start << ' ' << end << ": ";
    rechain();
    print(solu.reverseBetween(&nodes[0], start, end));
}

int main() {
    init();
    test(2, 6);
    test(3, 8);
    test(3, 4);
    test(4, 4);
    test(1, 1);
    test(1, 9);
    test(9, 9);

    return 0;
}


#include <algorithm>
#include <iostream>

#include <string>
using std::string;

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
    pointer addTwoNumbers(pointer l1, pointer l2) {
        if (l1 == NULL) {
            return l2;
        }
        if (l2 == NULL) {
            return l1;
        }

        int summ = l1->val + l2->val;
        pointer l3 = new ListNode(summ % 10);
        int carry = summ / 10;
        pointer curr1 = l1->next, curr2 = l2->next, curr3 = l3;
        while (curr1 && curr2) {
            summ = carry + curr1->val + curr2->val;
            curr1 = curr1->next;
            curr2 = curr2->next;
            curr3->next = new ListNode(summ % 10);
            curr3 = curr3->next;
            carry = summ / 10;
        }

        while (curr1) {
            summ = carry + curr1->val;
            curr3->next = new ListNode(summ % 10);
            curr3 = curr3->next;
            curr1 = curr1->next;
            carry = summ / 10;
        }

        while (curr2) {
            summ = carry + curr2->val;
            curr3->next = new ListNode(summ % 10);
            curr3 = curr3->next;
            curr2 = curr2->next;
            carry = summ / 10;
        }

        if (carry) {
            curr3->next = new ListNode(carry);
        }

        return l3;
    }
};

Solution solu;

ListNode nodes1[20];
ListNode nodes2[20];

void init() {
    for (int i = 0; i < 19; ++i) {
        nodes1[i].next = &nodes1[i + 1];
        nodes2[i].next = &nodes2[i + 1];
    }
    nodes1[19].next = NULL;
    nodes2[19].next = NULL;
}

void printAndDelete(ListNode* head) {
    ListNode* curr = NULL;
    while (head) {
        std::cout << head->val;
        curr = head;
        head = head->next;
        delete curr;
    }
    std::cout << std::endl;
}

int main() {
    ListNode* head;

    init();
    nodes1[0].val = 2, nodes1[1].val = 4, nodes1[2].val = 3;
    nodes1[2].next = NULL;
    nodes2[0].val = 5, nodes2[1].val = 6, nodes2[2].val = 4;
    nodes2[2].next = NULL;
    head = solu.addTwoNumbers(&nodes1[0], &nodes2[0]);
    printAndDelete(head);

    init();
    for (int i = 0; i < 20; ++i) {
        nodes1[i].val = 9;
        nodes2[i].val = 9;
    }
    head = solu.addTwoNumbers(&nodes1[0], &nodes2[0]);
    printAndDelete(head);

    nodes2[9].next = NULL;
    for (int i = 0; i < 9; ++i) {
        nodes2[i].val = i + 1;
    }
    head = solu.addTwoNumbers(&nodes1[0], &nodes2[0]);
    printAndDelete(head);

    return 0;
}


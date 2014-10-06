#include <string>
#include <iostream>
#include <algorithm>

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
    ListNode* mergeTwoLists(ListNode* head1, ListNode* head2) {
        if (head1 == NULL && head2 == NULL) {
            return NULL;
        }
        if (head1 == NULL && head2 != NULL) {
            return head2;
        }
        if (head1 != NULL && head2 == NULL) {
            return head1;
        }

        nodeptr head, rear, other;
        if (head1->val < head2->val) {
            head = head1, rear = head1, other = head2;
        } else {
            head = head2, rear = head2, other = head1;
        }

        while (true) {
            if (!rear->next) {
                break;
            }
            rear = rear->next;
        }
        rear->next = other;

        nodeptr curr1 = head, curr2 = other, next1, next2;
        while (curr1 != rear && curr2) {
            next1 = curr1->next, next2 = curr2->next;
            if (curr1->next->val > curr2->val) { // insert node curr2 in list 2 into list 1
                curr1->next = curr2, curr2->next = next1;
                rear->next = next2;
                curr1 = curr2, curr2 = next2;
            } else {
                curr1 = next1;
            }
        }

        return head;
    }
};
typedef Solution::nodeptr nodeptr;
static Solution solution;

namespace stest {
static int const NODES_COUNT1 = 4, NODES_COUNT2 = 5;
static ListNode nodes1[NODES_COUNT1];
static ListNode nodes2[NODES_COUNT2];

using std::string;
static string prompt1 = "list 1: ";
static string prompt2 = "list 2: ";
static string prompt3 = "merged: ";

inline void printList(nodeptr head, const string& prompt) {
    printf("%s", prompt.c_str());
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

inline nodeptr getHead1() {
    return &nodes1[0];
}
inline nodeptr getHead2() {
    return &nodes2[0];
}
static inline void init() {
    for (int i = 0; i < NODES_COUNT1 - 1; ++i) {
        nodes1[i].next = &nodes1[i + 1];
    }
    nodes1[NODES_COUNT1 - 1].next = NULL;
    for (int i = 0; i < NODES_COUNT2 - 1; ++i) {
        nodes2[i].next = &nodes2[i + 1];
    }
    nodes2[NODES_COUNT2 - 1].next = NULL;
}
inline void setUpTest1() {
    init();

    nodes1[0].val = 1, nodes1[1].val = 8;
    nodes1[2].val = 11, nodes1[3].val = 31;

    nodes2[0].val = 4, nodes2[1].val = 9;
    nodes2[2].val = 14, nodes2[3].val = 23;
    nodes2[4].val = 32;
}
inline void setUpTest2() {
    init();

    nodes1[0].val = 1, nodes1[1].val = 8;
    nodes1[2].val = 11, nodes1[3].val = 31;

    nodes2[0].val = 40, nodes2[1].val = 90;
    nodes2[2].val = 140, nodes2[3].val = 230;
    nodes2[4].val = 320;
}

}

int main() {

    stest::setUpTest1();
    nodeptr head1 = stest::getHead1(), head2 = stest::getHead2();
    stest::printList(head1, stest::prompt1);
    stest::printList(head2, stest::prompt2);
    stest::setUpTest1();
    nodeptr head = solution.mergeTwoLists(head1, head2);
    stest::printList(head, stest::prompt3);

    stest::setUpTest2();
    head1 = stest::getHead1(), head2 = stest::getHead2();
    stest::printList(head1, stest::prompt1);
    stest::printList(head2, stest::prompt2);
    stest::setUpTest2();
    head = solution.mergeTwoLists(head1, head2);
    stest::printList(head, stest::prompt3);

    return 0;
}


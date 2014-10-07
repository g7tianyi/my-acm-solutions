#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <ctime>

using std::vector;
using std::deque;

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
    ListNode *swapPairs(ListNode *head) {
        if (head == NULL) {
            return NULL;
        }
        nodeptr former = head, latter = head->next;
        if (latter) {
            head = latter;
        }
        nodeptr prev = NULL, next_former, next_latter;
        while (former && latter) {
            next_former  = latter->next;
            next_latter  = latter->next ? latter->next->next : NULL;

            former->next = latter->next;
            latter->next = former;
            if (prev) {
                prev->next = latter;
            }

            prev = former;
            former = next_former;
            latter = next_latter;
        }
        return head;
    }
};
static Solution solution;

namespace stest {
static int const MAX_NODE = 10;
static ListNode nodes[MAX_NODE];
int TEST_SIZE[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
inline ListNode* getHead() {
    return &nodes[0];
}
void setUpTest(int size) {
    srand((unsigned) time(0));
    int i = 0;
    for (; i < size - 1; i++) {
        nodes[i].next = &nodes[i + 1];
        nodes[i].val = std::abs(rand() % 100);
    }
    nodes[i].next = NULL;
    nodes[i].val = std::abs(rand() % 100);
}
void print(ListNode* head) {
    printf("list: ");
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}
}

int main() {
    for (int i = 0; i < sizeof(stest::TEST_SIZE) / sizeof(int); ++i) {
        printf("Test %d. Size %d:\n", i + 1, stest::TEST_SIZE[i]);
        stest::setUpTest(stest::TEST_SIZE[i]);
        stest::print(stest::getHead());
        ListNode* head = solution.swapPairs(stest::getHead());
        stest::print(head);
        printf("\n");
    }
    return 0;
}


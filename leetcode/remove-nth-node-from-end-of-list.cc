#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using std::vector;

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

typedef ListNode* nodeptr;

class Solution {
public:
    ListNode *removeNthFromEnd(ListNode* head, int n) {
        if (head == NULL) {
            return head;
        }

        nodeptr curr = head;
        for (int i = 0; i < n; ++i) {
            curr = curr->next;
        }

        nodeptr node = head, prev = NULL;
        while (curr) {
            curr = curr->next;
            prev = node;
            node = node->next;
        }

        if (prev) {
            prev->next = node ? node->next : NULL;
            return head;
        } else {
            return head->next;
        }
    }
};

static Solution solution;
ListNode nodes[10];

void init() {
    for (int i = 0; i < 10; ++i) {
        nodes[i].val = i + 1;
    }
    for (int i = 0; i < 9; ++i) {
        nodes[i].next = &nodes[i + 1];
    }
}

void print(nodeptr head) {
    nodeptr curr = head;
    while (curr) {
        std::cout << curr->val << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

int main() {
    for (int i = 1; i <= 10; ++i) {
        init();
        nodeptr newHead = solution.removeNthFromEnd(&nodes[0], i);
        print(newHead);
    }
    return 0;
}


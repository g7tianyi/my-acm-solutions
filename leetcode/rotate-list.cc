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
    ListNode(int x) :
            val(x), next(NULL) {
    }
    ListNode() :
            val(0), next(NULL) {
    }
};

typedef ListNode* pointer;
class Solution {
public:
    pointer rotateRight(pointer head, int k) {
        if (head == NULL || k < 1) {
            return head;
        }

        int length = 1;
        pointer curr = head;
        while (curr->next) {
            ++length;
            curr = curr->next;
        }
        curr->next = head;

        // stupid edge case, k can be larger than length
        // and the stupid OJ requires to return "k-reversed" list
        int count = (length - k) % length;
        while (count < 0) {
            count += length;
            count %= length;
        }

        int step = 0;
        while (step < count) {
            curr = curr->next;
            ++step;
        }

        head = curr->next;
        curr->next = NULL;
        return head;
    }
};

Solution solu;

static int MAX_NODE = 5;
ListNode nodes[10];

inline void link() {
    int i = 0;
    for (; i < MAX_NODE - 1; ++i) {
        nodes[i].val = i + 1;
        nodes[i].next = &nodes[i + 1];
    }
    nodes[MAX_NODE - 1].val = i + 1;
    nodes[MAX_NODE - 1].next = NULL;
}

inline void print(ListNode* head) {
    while (head) {
        std::cout << head->val << ' ';
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    std::cout << (-3 % 5) << std::endl;
    for (int i = 1; i <= MAX_NODE; ++i) {
        link();
        std::cout << i << ": ";
        print(solu.rotateRight(&nodes[0], i));
    }
    return 0;
}


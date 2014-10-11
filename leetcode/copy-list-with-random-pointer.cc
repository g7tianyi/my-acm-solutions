#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

/**
 * Definition for singly-linked list with a random pointer.
 */
struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

typedef RandomListNode* pointer;

class Solution {
public:
    pointer copyRandomList(pointer pHead) {
        if (pHead == NULL) {
            return pHead;
        }

        pointer pCurr = pHead, pNext; // prev curr, prev next
        while (pCurr) {
            pNext = pCurr->next;
            pointer pTemp = new RandomListNode(pCurr->label);
            pTemp->next = pNext;
            pCurr->next = pTemp;
            pCurr = pNext;
        }

        pCurr = pHead;
        while (pCurr) {
            if (pCurr->random) {
                pCurr->next->random = pCurr->random->next;
            }
            pCurr = pCurr->next->next;
        }

        pointer nHead = pHead->next, nCurr, nNext; // new curr, new next
        pCurr = pHead, nCurr = nHead;
        while (nCurr) {
            pNext = pCurr->next ? pCurr->next->next : NULL;
            nNext = nCurr->next ? nCurr->next->next : NULL;

            pCurr->next = pNext;
            pCurr = pNext;
            nCurr->next = nNext;
            nCurr = nNext;
        }

        return nHead;
    }
};

Solution sol;

#ifdef RANDOM_TEST
#include <ctime>
#include <unistd.h>
#endif

int main() {

    return 0;
}


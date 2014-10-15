#include <algorithm>

#include <iostream>

//#include <string>
//using std::string;

#include <vector>
#include <algorithm>
#include <functional>
using std::vector;

template<typename T, typename Compare> class Heap {
public:
    Heap() :
            compare(Compare()) {
        std::make_heap(container.begin(), container.end(), compare);
    }

    const T& top() const {
        return *(container.begin());
    }

    void push(const T& item) {
        container.push_back(item);
        std::push_heap(container.begin(), container.end(), compare);
    }

    T pop() {
        std::pop_heap(container.begin(), container.end(), compare);
        T popped = container.back();
        container.pop_back();
        return popped;
    }

    bool empty() const {
        return container.empty();
    }

    size_t size() const {
        return container.size();
    }

    void clear() {
        container.clear();
    }

private:
    Compare compare;
    std::vector<T> container;
};

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

typedef ListNode* nodeptr;
struct ListNodeCompare {
    bool operator()(const nodeptr lhs, const nodeptr rhs) {
        return lhs->val > rhs->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode *>& lists) {
        Heap<nodeptr, ListNodeCompare> kHeap;
        for (int i = 0; i < lists.size(); ++i) {
            if (lists[i]) {
                kHeap.push(lists[i]);
            }
        }

        nodeptr head = NULL, hCurr = NULL;
        nodeptr curr, next;
        while (!kHeap.empty()) {
            curr = kHeap.pop();
            next = curr->next;

            if (hCurr) {
                hCurr->next = curr;
                hCurr = hCurr->next;
            } else {
                head = curr;
                hCurr = head;
            }

            if (next) {
                kHeap.push(next);
            }
        }

        return head;
    }
};

Solution solu;

ListNode nodes[5][10];

#include <ctime>

int main() {
    vector<int> v;
    vector<ListNode*> lists;
    srand((unsigned) time(0));
    for (int i = 0, num; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            num = rand() % 100;
            v.push_back(num);
        }
        std::sort(v.begin(), v.end());
        std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        for (int j = 0; j < 9; ++j) {
            nodes[i][j].val = v[j];
            nodes[i][j].next = &nodes[i][j + 1];
        }
        nodes[i][9].val = v[9];
        nodes[i][9].next = NULL;
        lists.push_back(&nodes[i][0]);
        v.clear();
    }

    nodeptr head = solu.mergeKLists(lists);
    nodeptr curr = head;
    while (curr) {
        std::cout << curr->val << ' ';
        curr = curr->next;
    }

    return 0;
}


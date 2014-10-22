#include <iostream>
#include <vector>
using std::vector;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) :
        label(x) {
    }
};

#include <unordered_set>
#include <deque>

class Solution {
public:
    UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node) {
        if (node == NULL) {
            return NULL;
        }

        // clone each node, store it in the rear of the adjacences' list
        std::deque<UndirectedGraphNode*> queue;
        queue.push_back(node);
        std::unordered_set<int> visit;
        visit.insert(node->label);
        while (!queue.empty()) {
            UndirectedGraphNode* curr = queue.front();
            queue.pop_front();

            UndirectedGraphNode* clone = new UndirectedGraphNode(curr->label);
            curr->neighbors.push_back(clone);

            vector<UndirectedGraphNode* >& neighbors = curr->neighbors;
            for (int i = 0; i < neighbors.size() - 1; ++i) {
                if (neighbors[i] && visit.find(neighbors[i]->label) == visit.end()) {
                    visit.insert(neighbors[i]->label);
                    queue.push_back(neighbors[i]);
                }
            }
        }

        // link the new graph
        queue.push_back(node);
        visit.clear();
        visit.insert(node->label);
        UndirectedGraphNode* newNode = node->neighbors.back();
        while (!queue.empty()) {
            UndirectedGraphNode* curr = queue.front();
            queue.pop_front();

            UndirectedGraphNode* newCurr = curr->neighbors.back();
            vector<UndirectedGraphNode *>& neighbors = curr->neighbors;
            for (int i = 0; i < neighbors.size() - 1; ++i) {
                if (neighbors[i]) {
                    newCurr->neighbors.push_back(neighbors[i]->neighbors.back());
                    if (visit.find(neighbors[i]->label) == visit.end()) {
                        visit.insert(neighbors[i]->label);
                        queue.push_back(neighbors[i]);
                    }
                } else {
                    newCurr->neighbors.push_back(NULL);
                }
            }
        }

        // recover the original graph
        queue.push_back(node);
        visit.clear();
        visit.insert(node->label);
        while (!queue.empty()) {
            UndirectedGraphNode* curr = queue.front();
            queue.pop_front();
            curr->neighbors.pop_back();
            vector<UndirectedGraphNode *>& neighbors = curr->neighbors;
            for (int i = 0; i < neighbors.size(); ++i) {
                if (neighbors[i]  && visit.find(neighbors[i]->label) == visit.end()) {
                    visit.insert(neighbors[i]->label);
                    queue.push_back(neighbors[i]);
                }
            }
        }

        return newNode;
    }
};

Solution solu;

int main() {

    return 0;
}


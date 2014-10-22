#include <iostream>
#include <unordered_map>
#include <vector>

struct LRUNode {
    int key, value;
    LRUNode* prev;
    LRUNode* next;
    LRUNode() :
        key(0), value(0), prev(NULL), next(NULL) {
    }
};

class LRUCache {
public:
    LRUCache(int capacity) {
        entries = new LRUNode[capacity];
        for (int i = 0; i < capacity; ++i) {
            freenodes.push_back(entries + i);
        }
        head = new LRUNode;
        tail = new LRUNode;
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        delete head;
        delete tail;
        delete[] entries;
    }

    int get(int key) {
        std::unordered_map<int, LRUNode*>::iterator pos = nodemap.find(key);
        if (pos != nodemap.end()) {
            LRUNode* curr = pos->second;
            detach(curr);
            attach(curr);
            return curr->value;
        } else {
            return -1;
        }
    }

    void set(int key, int value) {
        std::unordered_map<int, LRUNode*>::iterator pos = nodemap.find(key);
        LRUNode* node;
        if (pos != nodemap.end()) {
            node = pos->second;
            detach(node);
            node->value = value;
            attach(node);
        } else { // Here is the real LRU comes in
            if (freenodes.empty()) {
                node = tail->prev;
                detach(node);
                nodemap.erase(node->key);
            } else {
                node = freenodes.back();
                freenodes.pop_back();
            }
            node->key = key;
            node->value = value;
            nodemap.insert(std::make_pair(key, node));
            attach(node);
        }
    }
private:
    // detach from the list
    inline void detach(LRUNode* node) {
        if (node == NULL) {
            return;
        }
        if (node->prev) {
            node->prev->next = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        }
    }
    // attach to the head
    inline void attach(LRUNode* node) {
        if (node == NULL) {
            return;
        }
        node->prev = head;
        node->next = head->next;
        head->next = node;
        node->next->prev = node; // node->next will no be null;
    }

private:
    std::unordered_map<int, LRUNode*> nodemap;
    std::vector<LRUNode*> freenodes;
    LRUNode* head;
    LRUNode* tail;
    LRUNode* entries;
};

int main() {

    return 0;
}


/**
 * http://poj.org/problem?id=2021
 * Relative Relatives
 *
 * use the idea of union-find-set
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

struct relation {
    int pid, age;
};

struct person {
    std::string name;
    int age;
    person(std::string name_, int age_) : name(name_), age(age_) {}
    person(const person& p) {
        this->name = p.name;
        this->age = p.age;
    }
};

inline bool operator< (const person& lhs, const person& rhs){
    if (lhs.age != rhs.age) {
        return lhs.age > rhs.age;
    }
    return lhs.name < rhs.name;
}

class family_tree {
public:
    family_tree() {
        reset();
    }

    inline void reset() {
        next = 0;
        memset(set, 0, sizeof(set));
        index.clear();
        index.insert(std::make_pair("Ted", next++));
    }

    inline void relative(std::string& parent, std::string& child, int age) {
        int cid = getindex(child);
        set[cid].pid = getindex(parent);
        set[cid].age = age;
    }

    void print() {
        std::vector<person> output;
        int curr, age;
        std::map<std::string, int>::iterator pos;
        for (pos = index.begin(); pos != index.end(); ++pos) {
            if (pos->second == 0) {
                continue;
            }
            curr = pos->second, age = 0;
            while (curr) {
                age += set[curr].age;
                curr = set[curr].pid;
            }
            person p(pos->first, 100 - age);
            output.push_back(p);
        }

        std::sort(output.begin(), output.end());
        std::vector<person>::iterator iter;
        for (iter = output.begin(); iter != output.end(); ++iter) {
            std::cout << iter->name << ' ' << iter->age << std::endl;
        }
    }

private:

    inline int getindex(std::string& name) {
        if (index.find(name) == index.end()) {
            index.insert(std::make_pair(name, next++));
        }
        return index[name];
    }

private:

    int next;
    relation set[128]; // simulating union-find set
    std::map<std::string, int> index;
};

family_tree mytree;

int main() {
    int cases, count;
    scanf("%d", &cases);
    for (int t = 1; t <= cases; ++t) {
        mytree.reset();
        scanf("%d", &count);
        std::string parent, child;
        int age;
        while (count--) {
            std::cin >> parent >> child >> age;
            mytree.relative(parent, child, age);
        }
        std::cout << "DATASET " << t << std::endl;
        mytree.print();
    }
    return 0;
}


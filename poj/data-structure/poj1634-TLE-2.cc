/**
 * http://poj.org/problem?id=1634
 * Who's the boss?
 * Building Tree
 */

#include <functional>
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <map>
#include <set>

const int MAX_EMPLOYEE = 30002;

struct employee {
    int id, wage, height;
};

// it is guaranteed that no two employees have the same salary
struct wage_comp: public std::unary_function<employee, bool> {
    inline bool operator()(const employee& e1, const employee& e2) {
        return e1.wage > e2.wage;
    }
};

struct empnode {
public:
    int parid, empid, descendant;
    std::vector<empnode*> children;
    empnode() : parid(0), empid(0), descendant(0) {}
    void clear() {
        clear(this);
    }
private:
    void clear(empnode* enode) {
        for (int i = 0; i < enode->children.size(); ++i) {
            clear(enode->children[i]);
        }
        enode->children.clear();
        enode->parid = 0;
        enode->empid = 0;
        enode->descendant = 0;
    }
};

////////////////////////////////////////////////////////////////////////
int E, Q, C; // employee count, query count, empnode count
employee employees[MAX_EMPLOYEE];
empnode empnodes[MAX_EMPLOYEE];
////////////////////////////////////////////////////////////////////////

struct emptree {
public:
    emptree() : root(NULL) {}
    ~emptree() {
        root->clear();
    }

    void insert(employee employees[], int size) {
        std::sort(employees, employees + size, wage_comp());
        for (int i = 0; i < size; ++i) {
            empmap[employees[i].id] = i;
        }
        for (int i = 0; i < size; ++i) {
            insert(employees[i]);
        }
    }

private:
    void insert(const employee& emp) {
        if (root) {
            insert(root, emp);
        } else {
            root = &empnodes[C++];
            root->parid = 0, root->empid = emp.id;
        }
    }

    void insert(empnode* enode, const employee& emp) {
        ++enode->descendant;
        empnode *echild, *enext = NULL;
        int idx, mindiff = std::numeric_limits<int>::max();
        for (int i = 0; i < enode->children.size(); ++i) {
            echild = enode->children[i];
            idx = empindex(echild->empid);
            if (employees[idx].height <= emp.height) {
                enext = NULL;
                break;
            }
            if (mindiff > employees[idx].height - emp.height) {
                mindiff = employees[idx].height - emp.height;
                enext = enode->children[i];
            }
        }
        if (!enext) {
            enext = &empnodes[C++];
            enext->parid = enode->empid;
            enext->empid = emp.id;
            enode->children.push_back(enext);
        } else {
            insert(enext, emp);
        }
    }

    inline int empindex(int empid) {
        return empmap[empid];
    }

private:
    empnode* root;
    std::map<int, int> empmap;
};

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &E, &Q);
        for (int i = 0; i < E; ++i) {
            scanf("%d %d %d", &employees[i].id, &employees[i].wage, &employees[i].height);
        }

        C = 0;
        emptree etree;
        etree.insert(employees, E);

        for (int i = 0, query; i < Q; ++i) {
            scanf("%d", &query);
            for (int i = 0; i < E; ++i) {
                if (empnodes[i].empid == query) {
                    printf("%d %d\n", empnodes[i].parid, empnodes[i].descendant);
                    break;
                }
            }
        }

    }
    return 0;
}


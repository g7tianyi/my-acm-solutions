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
#include <map>

const int MAX_EMPLOYEE = 30002;
const int MAX_QUERY    = 201;

struct employee {
    int id, wage, height;
};

// it is guaranteed that no two employees have the same salary
struct wage_comp: public std::unary_function<employee, bool> {
    inline bool operator()(const employee& e1, const employee& e2) {
        return e1.wage > e2.wage;
    }
};

int E, Q; // employee count, query count
employee employees[MAX_EMPLOYEE];
int queries[MAX_QUERY];

struct emptree {
public:
    emptree() : root(NULL) {}
    ~emptree() {
        if (root) {
            delete root;
        }
    }

    void insert(employee employees[], int size) {
        std::sort(employees, employees + size, wage_comp());
        for (int i = 0; i < size; ++i) {
            insert(employees[i]);
            empmap[employees[i].id] = i;
        }
    }

    void search(int empid) {
        int empidx = empindex(empid);
        search(root, employees[empidx]);
    }

private:
    struct empnode {
        int parid, empid, descendant;
        std::vector<empnode*> children;
        empnode(int pid, int eid) : parid(pid), empid(eid), descendant(0) {}
        ~empnode() {
            for (int i = 0; i < children.size(); ++i) {
                delete children[i];
            }
            children.clear();
        }
    };

private:
    void insert(const employee& emp) {
        if (root) {
            insert(root, emp);
        } else {
            root = new empnode(0, emp.id);
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
            enext = new empnode(enode->empid, emp.id);
            enode->children.push_back(enext);
        } else {
            insert(enext, emp);
        }
    }

    void search(empnode* enode, const employee& emp) {
        if (enode == NULL) {
            return;
        }
        if (enode->empid == emp.id) {
            printf("%d %d\n", enode->parid, enode->descendant);
            return;
        }
        empnode *echild = NULL, *enext = NULL;
        int idx, mindiff = std::numeric_limits<int>::max();
        for (int i = 0; i < enode->children.size(); ++i) {
            echild = enode->children[i];
            idx = empindex(echild->empid);
            if (employees[idx].height >= emp.height
                    && mindiff > employees[idx].height - emp.height) {
                mindiff = employees[idx].height - emp.height;
                enext = enode->children[i];
            }
        }
        search(enext, emp);
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
        for (int i = 0; i < Q; ++i) {
            scanf("%d", &queries[i]);
        }

        emptree etree;
        etree.insert(employees, E);
        for (int i = 0; i < Q; ++i) {
            etree.search(queries[i]);
        }
    }
    return 0;
}


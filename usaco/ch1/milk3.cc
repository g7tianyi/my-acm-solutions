/*
 ID: fairyroad1106
 PROG: milk3
 LANG: C++
 */

#include<fstream>
#include<deque>
#include<algorithm>
using namespace std;

struct state {
    int tag[3];
    state() {
    }
    state(const state& other) {
        for (int i = 0; i < 3; ++i)
            tag[i] = other.tag[i];
    }
};
ifstream fin("milk3.in");
ofstream fout("milk3.out");
int capacity[3] = { 0 };
int rescount = 0;
int res[21];
const int prime[21] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
        53, 59, 61, 67, 71, 73 };
bool flag[394420] = { false };
deque<state> ds;

inline int mapping(const state& s) {
    return prime[s.tag[0]] * prime[s.tag[0]] * prime[s.tag[0]]
            + prime[s.tag[1]] * prime[s.tag[1]] + prime[s.tag[2]];
}

inline void pouring(const state& s, int active) {
    int i, diff, mapvalue;
    for (i = 0; i < 3; ++i) {
        if (i == active)
            continue;
        if ((diff = capacity[i] - s.tag[i]) != 0) {
            state p(s);
            if (diff < p.tag[active]) {
                p.tag[i] = p.tag[i] + diff;
                p.tag[active] = p.tag[active] - diff;
            } else {
                p.tag[i] = p.tag[i] + p.tag[active];
                p.tag[active] = 0;
            }
            if (p.tag[0] == 0 && count(res, res + rescount, p.tag[2]) == 0)
                res[rescount++] = p.tag[2];
            mapvalue = mapping(p);
            if (!flag[mapvalue]) {
                flag[mapvalue] = true;
                ds.push_back(p);
            }
        }
    }
}

int main() {
    fin >> capacity[0] >> capacity[1] >> capacity[2];
    state s, p;
    s.tag[0] = s.tag[1] = 0;
    s.tag[2] = capacity[2];
    for (int i = 0; i < 21; ++i)
        res[i] = -1;

    rescount = 0;
    ds.push_back(s);

    while (!ds.empty()) {
#ifdef DEBUG1
        for(size_t i = 0; i < ds.size(); ++i) cout<<ds[i].tag[0]<<' '<<ds[i].tag[1]<<' '<<ds[i].tag[2]<<endl;
#endif
        p = ds.front();

        for (int i = 0; i < 3; ++i)
            if (p.tag[i] != 0)
                pouring(p, i);

        ds.pop_front();
    }
    sort(res, res + rescount);
    for (int i = 0; i < rescount - 1; ++i)
        fout << res[i] << ' ';
    fout << res[rescount - 1] << endl;
    return 0;
}


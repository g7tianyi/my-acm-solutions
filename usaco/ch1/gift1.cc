/*
 ID: fairyroad1106
 PROG: gift1
 LANG: C++
 */
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define PROGID "gift1"
#define INPUT  PROGID".in"
#define OUTPUT PROGID".out"

ifstream fin(INPUT);
ofstream fout(OUTPUT);

vector<string> names;
map<string, int> result;
vector<string>::iterator iter;
map<string, int>::iterator pos;

int main() {
    int NP;
    fin >> NP;
    string name;
    for (int i = 0; i < NP; ++i) {
        fin >> name;
        names.push_back(name);
    }

    string sender, receiver;
    int money, num_rece;
    for (int i = 0; i < NP; ++i) {
        fin >> sender >> money >> num_rece;
        if (money == 0 || num_rece == 0) {
            continue;
        }
        money /= num_rece;
        result[sender] -= money * num_rece;
        for (int j = 0; j < num_rece; ++j) {
            fin >> receiver;
            result[receiver] += money;
        }
    }

    for (iter = names.begin(); iter != names.end(); ++iter) {
        fout << *iter << ' ' << result[*iter] << '\n';
    }

    return 0;
}


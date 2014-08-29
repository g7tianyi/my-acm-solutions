/**
 * ZOJ 1059, What's In a Name
 *
 * really frustrated, in the end it turns out to be a perfect-matching problem
 * but the problem description has not specified for maximum matching.
 *
 * The code here will not pass the judge, leave it for now.
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

static const int MAX_USERS = 22;

#define ONLINE     true
#define OFFLINE    false
#define POSSIBLE   true
#define IMPOSSIBLE false

struct user_info {
    int real_index, fake_index;
    user_info(int _real_index, int _fake_index)
        : real_index(_real_index), fake_index(_fake_index) {}
};

vector<string> real_names;
vector<string> fake_names;
vector<user_info> user_infos;
// mapping[i][j] is true indicates that real_name i is possibly related to fake_name j
bool mapping[MAX_USERS][MAX_USERS];
// status[i] is true means fake_name i is online now
bool status[MAX_USERS];
int cases, num_user;

bool comp(const user_info& lhs, const user_info& rhs) {
    return fake_names[lhs.fake_index] < fake_names[rhs.fake_index];
}

int main() {

    cin >> cases;

    while (cases) {
        cin >> num_user;

        real_names.clear();
        fake_names.clear();
        user_infos.clear();

        string name;
        int num_real_name = 0;
        for (int i = 0; i < num_user; ++i) {
            cin >> name;
            if (find(real_names.begin(), real_names.end(), name) == real_names.end()) {
                ++num_real_name;
                real_names.push_back(name);
            }
        }

        memset(mapping, POSSIBLE, sizeof(mapping));
        memset(status,  OFFLINE,  sizeof(status));

        char ch;
        int curr_id, num_fake_name = 0, pos;
        vector<string>::iterator iter;
        while ((cin >> ch) && ch != 'Q') {
            cin >> name;

            if (ch == 'M') {
                iter = find(real_names.begin(), real_names.end(), name);
                pos = iter - real_names.begin();
                for (int i = 0; i < num_user; ++i) {
                    if (!status[i] && mapping[pos][i]) { // user i is offline
                        mapping[pos][i] = false;
                    }
                }
            } else {
                iter = find(fake_names.begin(), fake_names.end(), name);
                if (iter == fake_names.end()) {
                    curr_id = num_fake_name++;
                    fake_names.push_back(name);
                } else {
                    curr_id = iter - fake_names.begin();
                }
                status[curr_id] = (ch == 'E' ? ONLINE : OFFLINE);
            }
        }

        bool updated;
        do {
            updated = false;
            for (int real_name_index = 0; real_name_index < num_real_name; ++real_name_index) {
                int count = 0, sole_pos;
                for (int fake_name_index = 0; fake_name_index < num_fake_name; ++fake_name_index) {
                    if (mapping[real_name_index][fake_name_index] && ++count == 1) {
                        sole_pos = fake_name_index;
                    }
                }
                if (count == 1) {
                    // solely identified the real name
                    // mark other real_name<=>fake_name mappings false
                    for (int other_real_index = 0; other_real_index < num_real_name; ++other_real_index) {
                        if(mapping[other_real_index][sole_pos] && other_real_index != real_name_index) {
                            mapping[other_real_index][sole_pos] = false;
                            updated = true;
                        }
                    }
                }
            }
        } while(updated);

        for (int i = 0; i < num_fake_name; ++i) { // i is the column index ==> fake name
            int count = 0, pos;
            for (int j = 0; j < num_real_name; ++j) { // j is the row index ==> real name
                if (mapping[j][i] && ++count == 1) {
                    pos = j;
                }
            }
            if (count == 1) {
                user_infos.push_back(user_info(pos, i));
            } else {
                user_infos.push_back(user_info(-1, i));
            }
        }

        sort(user_infos.begin(), user_infos.end(), comp);
        for (vector<user_info>::iterator user_iter = user_infos.begin();
                user_iter != user_infos.end();
                ++user_iter) {
            cout << fake_names[user_iter->fake_index]
                 << ":"
                 << (user_iter->real_index < 0 ? "???" : real_names[user_iter->real_index])
                 << "\n";
        }

        if(--cases) {
            cout << "\n";
        }
    }

    return 0;
}


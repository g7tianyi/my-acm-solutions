/*
 ID: fairyroad
 LANG: C++
 TASK: fence8
 */

#include <fstream>
#include <vector>
#include <algorithm>

/*
Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.000 secs, 3368 KB]
   Test 2: TEST OK [0.000 secs, 3368 KB]
   Test 3: TEST OK [0.000 secs, 3368 KB]
  > Run 4: Execution error: Your program (`fence8') used more than the
        allotted runtime of 1 seconds (it ended or was stopped at 1.674
        seconds) when presented with test case 4. It used 3368 KB of
        memory. 

        ------ Data for Run 4 [length=595 bytes] ------
        10 
        11 
        15 
        13 
        15 
        15 
        15 
        15 
        11 
        19 
        15 
        192 
        4 
        4 
        4 
        5 
        5 
        6 
        6 
        6 
        6 
        6 
        6 
        7 
        7 
        8 
        8 
        8 
        9 
        9 
        10 

        ... [and more] ...
        ----------------------------
    Test 4: RUNTIME 1.674>1 (3368 KB)
 */
using std::ifstream;
using std::ofstream;
using std::vector;
ifstream fin("fence8.in");
ofstream fout("fence8.out");

int N, R, result;
int board[51], rail[1024];
int need[129] = { 0 };
bool obtained[1024];
vector<vector<vector<int> > > dp(51);

// How to reduce the duplicated search ?
void dfs_potenial_path(int id, int size, int next, vector<int> path) {
  if (size == 0) {
    dp[id].push_back(path);
    return;
  }

  for (int i = next; i <= R; ++i) {
    if (size < rail[i]/* || ()*/)
      return;
    if (i > 1 && rail[i] == rail[i - 1])
      continue;

    if (need[rail[i]]) {
      --need[rail[i]];
      path.push_back(rail[i]);
      dfs_potenial_path(id, size - rail[i], i, path);
      ++need[rail[i]];
      path.pop_back();
    }
  }
}

inline bool is_needed(const vector<int>& v) {
  vector<int> tmp(need, need + 129);
  for (size_t i = 0; i < v.size(); ++i) {
    if (0 == tmp[v[i]])
      return false;
    --tmp[v[i]];
  }
  return true;
}

inline void set_obtain(const vector<int>& v, int flag) {
  for (size_t i = 0; i < v.size(); ++i)
    need[v[i]] += flag;
}

void dfs_result(int index, int count) {
  if (index > N) {
    if (result < count)
      result = count;
    return;
  }

  dfs_result(index + 1, count);
  for (size_t i = 0; i < dp[index].size(); ++i) {
    if (is_needed(dp[index][i])) {
      set_obtain(dp[index][i], -1);
      dfs_result(index + 1, count + dp[index][i].size());
      set_obtain(dp[index][i], 1);
    }
  }
}

int main() {
  fin >> N;
  for (int i = 1; i <= N; ++i)
    fin >> board[i];
  fin >> R;
  for (int i = 1; i <= R; ++i) {
    fin >> rail[i];
    ++need[rail[i]];
  }

  std::sort(board, board + N + 1);
  std::sort(rail, rail + R + 1);

  vector<int> path;
  for (int i = 1; i <= N; ++i) {
    path.clear();
    dfs_potenial_path(i, board[i], 1, path);
  }

  dfs_result(1, 0);
  fout << result << std::endl;

  return 0;
}
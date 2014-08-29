/*
 ID: fairyroad
 LANG: C++
 TASK: fence8
 */
 
/*
Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.000 secs, 3368 KB]
   Test 2: TEST OK [0.000 secs, 3368 KB]
   Test 3: TEST OK [0.000 secs, 3368 KB]
   Test 4: TEST OK [0.238 secs, 3368 KB]
   Test 5: TEST OK [0.335 secs, 3368 KB]
   Test 6: TEST OK [0.745 secs, 3368 KB]
   Test 7: TEST OK [0.000 secs, 3368 KB]
   Test 8: TEST OK [0.000 secs, 3368 KB]
   Test 9: TEST OK [0.000 secs, 3368 KB]
   Test 10: TEST OK [0.000 secs, 3368 KB]
   Test 11: TEST OK [0.000 secs, 3368 KB]
   Test 12: TEST OK [0.000 secs, 3368 KB]

All tests OK.
Your program ('fence8') produced all correct answers!  This is your
submission #4 for this problem.  Congratulations!
*/

#include <fstream>
#include <algorithm>
using std::ifstream;
using std::ofstream;
using std::endl;

ifstream fin("fence8.in");
ofstream fout("fence8.out");

int board[50];
int remains[50];
int rails[1024];
int from[1024]; // rail i is obtained from from[i]
int N, R;
int total_board = 0;
int waste_max = 0;

bool dfs(int start, int k, int waste) {
  if (k < 0)  // All i boards can be obtained
    return true;

  int i = 0;
  // Pruning 2: 
  // if rail[k]==rail[k+1], rail[k]'s board must not less than rail[k+1]'s.
  if (k != start && rails[k] == rails[k + 1])
    i = from[k + 1];
  for (; i < N; i++) {
    if (remains[i] >= rails[k]) {
      from[k] = i;
      remains[i] -= rails[k];
      if (remains[i] < rails[0])
        waste += remains[i];
      // Pruning 3: 
      // if the waste (can not be fully utilized) is more than before we get...
      if (waste > waste_max) {
        remains[i] += rails[k];
        waste -= remains[i];
        continue;
      }
      if (dfs(start, k - 1, waste))
        return true;
      remains[i] += rails[k];
    }
  }
  return false;
}

int main() {
  fin >> N;
  for (int i = 0; i < N; i++) {
    fin >> board[i];
    total_board += board[i];
    remains[i] = board[i];
  }
  fin >> R;
  for (int i = 0; i < R; i++)
    fin >> rails[i];

  std::sort(board, board + N);
  std::sort(rails, rails + R);

  int rail_sum = 0;
  for (int i = 0; i < R; i++) {
    rail_sum += rails[i];
    // Pruning 1 : Nothing big deal 
    // Make all boards split into small rails can lead to more splits
    if (rail_sum > total_board) {
      rail_sum -= rails[i];
      R = i;
      break;
    }
  }

  for (int i = R - 1; i >= 0; --i) {
    waste_max = total_board - rail_sum;
    rail_sum -= rails[i];
    if (dfs(i, i, 0)) {
      fout << i + 1 << std::endl;
      return 0;
    }
  }

  fout << 0 << endl;
  return 0;
}
/*
 ID: fairyroad
 LANG: C++
 TASK: game1
 */
 /*
Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.000 secs, 3436 KB]
   Test 2: TEST OK [0.000 secs, 3436 KB]
   Test 3: TEST OK [0.000 secs, 3436 KB]
   Test 4: TEST OK [0.000 secs, 3436 KB]
   Test 5: TEST OK [0.000 secs, 3436 KB]
   Test 6: TEST OK [0.000 secs, 3436 KB]
   Test 7: TEST OK [0.000 secs, 3436 KB]
   Test 8: TEST OK [0.000 secs, 3436 KB]
   Test 9: TEST OK [0.000 secs, 3436 KB]
   Test 10: TEST OK [0.000 secs, 3436 KB]
   Test 11: TEST OK [0.000 secs, 3436 KB]
   Test 12: TEST OK [0.000 secs, 3436 KB]
   Test 13: TEST OK [0.000 secs, 3436 KB]
   Test 14: TEST OK [0.000 secs, 3436 KB]
   Test 15: TEST OK [0.000 secs, 3436 KB]
   Test 16: TEST OK [0.000 secs, 3436 KB]

All tests OK.
YOUR PROGRAM ('game1') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
 */
#include <limits>
#include <fstream>

using namespace std;
ifstream fin("game1.in");
ofstream fout("game1.out");

int N;
int dp[101][101];
int sum[101][101];

inline int max(int a, int b) {
  return a > b ? a : b;
}

int main() {
  for (int i = 0; i < 101; ++i) {
    for (int j = 0; j < 101; ++j) {
      dp[i][j] = numeric_limits<int>::min();
    }
  }

  fin >> N;
  for (int i = 0; i < N; ++i) {
    fin >> dp[i][i];
    sum[i][i] = dp[i][i];
  }

  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      sum[i][j] = sum[i][j - 1] + dp[j][j];
    }
  }

  for (int i = 2; i <= N; ++i) { // sub length of the checking array
    for (int j = 0; j + i <= N; ++j) { // start pos of the specific length
      dp[j][j + i - 1] = max(
          dp[j][j] + sum[j + 1][j + i - 1] - dp[j + 1][j + i - 1],
          dp[j + i - 1][j + i - 1] + sum[j][j + i - 2] - dp[j][j + i - 2]);
    }
  }

  fout << dp[0][N - 1]  << ' ' << sum[0][N-1] - dp[0][N - 1] << endl;

}
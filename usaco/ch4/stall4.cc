/*
 ID:fairyroad
 LANG:C++
 TASK:stall4
 */

/*
Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.000 secs, 3396 KB]
   Test 2: TEST OK [0.000 secs, 3396 KB]
   Test 3: TEST OK [0.000 secs, 3396 KB]
   Test 4: TEST OK [0.000 secs, 3396 KB]
   Test 5: TEST OK [0.000 secs, 3396 KB]
   Test 6: TEST OK [0.000 secs, 3396 KB]
   Test 7: TEST OK [0.000 secs, 3396 KB]
   Test 8: TEST OK [0.000 secs, 3396 KB]
   Test 9: TEST OK [0.000 secs, 3396 KB]

All tests OK.
Your program ('stall4') produced all correct answers!  This is your
submission #2 for this problem.  Congratulations! 
*/

#include <fstream>
#include <algorithm>

std::ifstream fin("stall4.in");
std::ofstream fout("stall4.out");

int p, k, stall, n, ans = 0;
bool graph[205][205];
int cow[205];
bool taken[205]; // cowshed occupied or not

// Actually, this is brute force
bool Hungary(int curr) {
  for (int i = 1; i <= stall; i++) {
    if (graph[curr][i] && !taken[i]) {
      taken[i] = true;
      if (cow[i] == 0 || Hungary(cow[i])) {
        cow[i] = curr;
        return true;
      }
    }
  }
  return false;
}

int main() {
  fin >> n >> stall;
  for (int i = 1; i <= n; i++) {
    fin >> k;
    for (int j = 1; j <= k; j++) {
      fin >> p;
      graph[i][p] = true;
    }
  }

  for (int i = 1; i <= n; i++) {
    std::fill(taken, taken + 205, false);
    Hungary(i);
  }

  for (int i = 1; i <= stall; i++)
    if (cow[i] > 0)
      ans++;

  fout << ans << std::endl;
  return 0;
}


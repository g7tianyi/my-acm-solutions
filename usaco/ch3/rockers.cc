/*
 ID: fairyroad
 LANG: C++
 TASK: rockers
 */
 
/**
Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.000 secs, 3360 KB]
   Test 2: TEST OK [0.000 secs, 3360 KB]
   Test 3: TEST OK [0.000 secs, 3360 KB]
   Test 4: TEST OK [0.000 secs, 3360 KB]
   Test 5: TEST OK [0.000 secs, 3360 KB]
   Test 6: TEST OK [0.000 secs, 3360 KB]
   Test 7: TEST OK [0.000 secs, 3360 KB]
   Test 8: TEST OK [0.086 secs, 3360 KB]
   Test 9: TEST OK [0.022 secs, 3360 KB]
   Test 10: TEST OK [0.000 secs, 3360 KB]
   Test 11: TEST OK [0.022 secs, 3360 KB]
   Test 12: TEST OK [0.097 secs, 3360 KB]

All tests OK.
Your program ('rockers') produced all correct answers!  This is your
submission #4 for this problem.  Congratulations!
**/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("rockers.in");
ofstream fout("rockers.out");

int n, t, m, tim[20], ton[21], mmin = 0;

void greedy() {
  int i, j, cont = 0, k = m, a[20];
  for (i = 0; i < n; i++)
    a[i] = tim[i];
  if (k > n)
    k = n;
  for (i = 0; i < k; i++) {
    int s = t;
    sort(a + ton[i], a + ton[i + 1]);
    for (j = ton[i]; j < ton[i + 1]; j++)
      if (s >= a[j])
        s -= a[j], cont++;
      else
        break;
  }
  if (mmin < cont)
    mmin = cont;
}

void dfs(int d, int t) {
  if (d == m || d == n) {
    ton[d] = n;
    greedy();
    return;
  }
  if (t >= n)
    return;
  for (int i = t; i < n; i++) {
    ton[d] = i;
    dfs(d + 1, i + 1);
  }
}

int main() {
  fin >> n >> t >> m;
  for (int i = 0; i < n; i++)
    fin >> tim[i];
  dfs(0, 0);
  fout << mmin << endl;
  return 0;
}

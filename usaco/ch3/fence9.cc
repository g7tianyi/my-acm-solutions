/*
 ID: fairyroad
 LANG: C++
 TASK: fence9
 */

 /**
Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.000 secs, 3356 KB]
   Test 2: TEST OK [0.000 secs, 3356 KB]
   Test 3: TEST OK [0.000 secs, 3356 KB]
   Test 4: TEST OK [0.000 secs, 3356 KB]
   Test 5: TEST OK [0.000 secs, 3356 KB]
   Test 6: TEST OK [0.000 secs, 3356 KB]
   Test 7: TEST OK [0.000 secs, 3356 KB]
   Test 8: TEST OK [0.000 secs, 3356 KB]
   Test 9: TEST OK [0.000 secs, 3356 KB]
   Test 10: TEST OK [0.000 secs, 3356 KB]
   Test 11: TEST OK [0.000 secs, 3356 KB]
   Test 12: TEST OK [0.000 secs, 3356 KB]

All tests OK.
YOUR PROGRAM ('fence9') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
  */
 
#include <fstream>

std::ifstream fin("fence9.in");
std::ofstream fout("fence9.out");
int n, m, p;

// Nothing more to discuss, refer to the fence9.png 
int main() {
  fin >> n >> m >> p;

  int res = 0, count;
  int leftline = 0;
  for (int i = 1; i < n; ++i) {
    count = m * i / n;
    if (m * i % n == 0)
      --count;
    leftline += count;
  }

  int middleline = n == 0 ? 0 : m - 1;

  int rightline = 0, point_on_line = 0, i = n + 1, end = p;
  if (p < n) i = p + 1, end = n;
  for (; i < end; ++i) {
    count = m * (i - p) / (n - p);
    if (m * (i - p) % (n - p) == 0)
      --count, ++point_on_line;
    rightline += count;
  }

  res += leftline;

  if (n < p)
    res += (middleline + rightline);
  else if (n == p)
    res += rightline;
  else 
    res -= (rightline + point_on_line);

  fout << res << std::endl;
  return 0;
}

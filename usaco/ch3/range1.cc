/*
 ID: fairyroad
 LANG: C++
 TASK: range
 */
 
 /**
Compiling...
Compile: OK

Executing...
   Test 1: TEST OK [0.000 secs, 3668 KB]
   Test 2: TEST OK [0.000 secs, 3668 KB]
   Test 3: TEST OK [0.000 secs, 3668 KB]
   Test 4: TEST OK [0.000 secs, 3668 KB]
   Test 5: TEST OK [0.000 secs, 3668 KB]
   Test 6: TEST OK [0.076 secs, 3668 KB]
   Test 7: TEST OK [0.054 secs, 3668 KB]

All tests OK.
YOUR PROGRAM ('range') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
*/
#include <fstream>

using namespace std;
ifstream fin("range.in");
ofstream fout("range.out");

int N;
bool farm[251][251][251];

void dp() {
  int side_len = 2;
  while (true) { // side_len
    int count = 0;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (farm[i][j][side_len - 1] && farm[i][j + 1][side_len - 1]
            && farm[i + 1][j][side_len - 1]
            && farm[i + 1][j + 1][side_len - 1]) {
          farm[i][j][side_len] = true;
          ++count;
        }
      }
    }

    if (count > 0) {
      fout << side_len << ' ' << count << endl;
      ++side_len;
    } else
      return;
  }
}

int main() {
  fin >> N;
  char ch;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) {
      fin >> ch;
      farm[i][j][1] = ch == '0' ? false : true;
    }

  dp();

  return 0;
}

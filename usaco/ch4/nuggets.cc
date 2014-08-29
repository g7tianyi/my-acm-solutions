/*
 ID: fairyroad
 LANG: C++
 TASK: nuggets
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

All tests OK.
YOUR PROGRAM ('nuggets') WORKED FIRST TIME!  That's fantastic
-- and a rare thing.  Please accept these special automated
congratulations.
**/

#include <fstream>

std::ifstream fin("nuggets.in");
std::ofstream fout("nuggets.out");

const int MAXNUM = 2000000000;

int N;
int piece[256];
bool avai[256];

int gcd(int a, int b) {
  int t;
  while (b != 0) {
    t = a % b;
    a = b;
    b = t;
  }
  return a;
}

/*
Three tips worth mentioning,
1.	If the greatest common divisor, say div of all pieces¡¯ size is larger than 1, 
there¡¯re no upper boundary of the size that we cannot get. See 3, 6 as an example,  
any number which meets n % gcd(3,6) = n % 3 = 1, or 2 is unreachable
2.	If continous 256 numbers are reachable, so are the next 256 continous numbers
3.	Please see the comments in code to get the tips about slide window

*/
int main() {
  fin >> N;
  for (int i = 0; i < N; ++i)
    fin >> piece[i];

  int divisor = piece[0]; // greatest common divisor of all pieces
  for (int i = 1; i < N; ++i)
    divisor = gcd(divisor, piece[i]);
  if (divisor != 1) {
    fout << 0 << std::endl;
    return 0;
  }
  
  avai[0] = true;
  int res = 0, curr = 0;
  
  while (curr < MAXNUM) {
    if (curr - res > 256) // refer to nuggets.png 
      break;
    
    if (!avai[curr % 256]) {
      res = curr;
    } else {
      // Not logicly impossible to get
      // but an initilization for the following loop
      // The basic tips for silde window
      avai[curr % 256] = false;
      for (int i = 0; i < N; ++i)
        avai[(curr + piece[i]) % 256] = true;
    }
    ++curr;
  }
  
  if (curr >= MAXNUM) 
    fout << 0 << std::endl;
  else
    fout << res << std::endl;
  
  return 0;
}

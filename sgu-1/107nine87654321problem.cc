/**
 * xiaobengdou
 * sgu107 987654321 problem
 * 1434810  24.03.13 20:51  fairyroad  107  .CPP  Accepted  93 ms 831 kb
 */
#include <cstdio>

// 0. only the last 9 digits of the original number 
//    can effect the last 9 digits of the its square
// 1. when N <= 9, only the following 9 numbers meet the need
//    111111111
//    119357639
//    380642361
//    388888889
//    611111111
//    619357639
//    880642361
//    888888889
// 2. when n > 9, the result can be written as 8*9*10^(n-10)
//    8 is the 8 possibilities as previously discussed
//    9 is the possibilities of the first place of the number

int main() {
  int N;
  scanf("%d", &N);
  if (N <= 8)
    printf("0\n");
  else if (N == 9)
    printf("8\n");
  else {
    // The following code will fail for int overflow
    //
    // int res = 72;
    // for (int i = 0; i < N - 10; ++i)
    //   res *= 10;
    // printf("%d\n", res);

    // But I doubt the efficiency of the following code, IO...
     printf("72");
     for (int i = 0; i < N - 10; i++)
       printf("0");
     printf("\n");
  }
  
  return 0;
}

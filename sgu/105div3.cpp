/**
 * xiaobengdou
 * sgu105 Div 3
 * 1432396  18.03.13 08:31  fairyroad  105  .CPP  Accepted  15 ms 839 kb
 */
#include <cstdio>

// For 3 consecutive positive integers k, k+1, k+2
// k+(k+1)+(k+2) = 3k+3
// based on this discovery
//                     1234567891011
// omit three numbers  12345678
// omit three numbers  12345
// omit three numbers  12
// as 12 can be divided exactly by 3, 1234567891011 does
// 
// Note that,
// 1  12  123 1234 12345 123456 ...
// N  Y   Y   N    Y     N      ...
// 
// Here comes the following formula
// result = 2*(n/3) + 1 , if n % 3 == 2
//       or 2*(n/3), if n % 3 == 1

int main() {
  int n;
  scanf("%d", &n);
  printf("%d", (((n / 3) << 1) + ( n % 3 > 0 ? ( (n % 3)- 1 ) : 0)));
  return 0;
}

/**
 * xiaobengdou
 * sgu102 Coprimes
 * 
 * 1432282  17.03.13 17:42  fairyroad  102  .CPP  Accepted  15 ms 847 kb
 */

#include <cstdio>
#include <cmath>

int N;
int primes[1230] = { 0 }; // there're 1229 prime numbers less than 10000
int prime_count;

int euler(int n) {
  for (int i = 0; primes[i] <= sqrt(n); ++i) {
    if (n % primes[i] == 0) {
      n /= primes[i];
      if (n % primes[i] == 0)
        return primes[i] * euler(n);
      else
        return (primes[i] - 1) * euler(n);
    }
  }
  return n - 1;
}
void prepare_primes() {
  primes[0] = 2;
  for (int i = 3; i <= N; ++i) {
    bool flag = true;
    for (int j = 0; primes[j] <= sqrt(i); ++j) {
      if (i % primes[j] == 0) {
        flag = false;
        break;
      }
    }
    if (flag) {
      primes[++prime_count] = i;
    }
  }
}

int main() {
  scanf("%d", &N);
  prepare_primes();

  if (N == 1)
    printf("1\n");
  else
    printf("%d\n", euler(N));
}

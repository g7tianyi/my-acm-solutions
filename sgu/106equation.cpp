/**
 * xiaobengdou
 * sgu106 The Equation
 * 1432530  18.03.13 21:48  fairyroad  106  .CPP  Accepted  15 ms 831 kb
 */
#include <cstdio>

// extended Euclid algorithm :
// 
// 1. Euclidean algorithm (http://en.wikipedia.org/wiki/Euclidean_algorithm)
//  gcd(a,b) = gcd(b, a % b)
//
// 2. In the processing of Euclidean algorithm
//   2.1 the nature of common division is
//      gcd(a, b) = x * a + y * b
//   2.2 the recusive process can be presented by
//      x0 * a + y0 * b = gcd(a, b)
//      x1 * b + y1 * (a - a / b * b)  = gcd(b, a%b) = gcd(a, b) 
//      x0 * a + y0 * b = x1 * b + y1 * a - (a / b * b) * y1
//                      = x1 * b + (a % b) * y1
//                      = x1 * b + (a - a / b) * y1
//                      = b * x1 - a / b * b * y1 + a * y1
//      thus,
//          x0 = y1, y0 = x1 - a / b * x1
//      This is a naive but correct mathematical transform
//
// 3. Watch out the inequality operation
//    please see the illustration 106Equation_illustration.png
//

long long a, b, c, x1, x2, y1, y2;

void swap(long long& a, long long& b) {
  long long tmp = a;
  a = b;
  b = tmp;
}

long long extend_gcd(long long a, long long b, long long& x, long long& y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  } else {
    long long x1, y1;
    long long gcd = extend_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    printf("%I64d %I64d %I64d %I64d\n", x1, y1, x, y);
    return gcd;
  }
}

int main() {
  scanf("%I64d %I64d %I64d %I64d %I64d %I64d %I64d", &a, &b, &c, &x1, &x2, &y1,
      &y2);
  c = -c;
  long long count = 0;

  // always watch out for special cases
  if (a == 0 && b == 0) {
    if (c == 0)
      count = (x2 - x1 + 1) * (y2 - y1 + 1);
  } else if (a == 0) {
    if (c % b == 0 && c / b >= y1 && c / b <= y2)
      count = x2 - x1 + 1;
  } else if (b == 0) {
    if (c % a == 0 && c / a >= x1 && c / a <= x2)
      count = y2 - y1 + 1;
  } else {
    long long x0, y0;
    long long gcd = extend_gcd(a, b, x0, y0);
    if (c % gcd == 0) {
      long long sx = (c / gcd) * x0;
      long long sy = (c / gcd) * y0;
      long long lx =
          (x1 <= sx || (x1 - sx) * gcd % b == 0) ?
              (x1 - sx) * gcd / b : (x1 - sx) * gcd / b + 1;
      long long rx =
          (x2 >= sx || (x2 - sx) * gcd % b == 0) ?
              (x2 - sx) * gcd / b : (x2 - sx) * gcd / b - 1;
      long long ry =
          (sy <= y2 || (sy - y2) * gcd % a == 0) ?
              (sy - y2) * gcd / a : (sy - y2) * gcd / a + 1;
      long long ly =
          (sy >= y1 || (sy - y1) * gcd % a == 0) ?
              (sy - y1) * gcd / a : (sy - y1) * gcd / a - 1;

      if (lx > rx)
        swap(lx, rx);
      if (ly > ry)
        swap(ly, ry);
      if (lx <= ry && ly <= rx) {
        long long max = (lx > ly) ? lx : ly;
        long long min = (rx < ry) ? rx : ry;
        count = min - max + 1;
      }
    }
  }

  printf("%I64d\n", count);
  return 0;
}

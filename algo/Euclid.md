歐几里得算法與擴展歐几里得算法
=========
歐几里得算法
----
輾轉相除法求最大公約數。
```C++
// Euclid algorithm, recursion
int gcd (int a, int b) {
    if (a < b) {
        return gcd (b , a);
    }
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Euclid algorithm, iteration
int gcd (int a, int b) {
    if (a < b) {
        swap(a, b);
    }
    while (b) {
        int r = b;
        b = a % b;
        a = r;
    }
    return a;
}
```
擴展歐几里得算法
----
對於不全為 0 的非負整數 (a, b),  必然存在整数对 (x, y) ，使得 gcd(a, b) = ax+by. 
```C++
int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int r = exgcd(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - a / b * y;
    return r;
}

int exgcd(int a, int b, int& x int& y) {
    int x1, y1, x0, y0;
    x0 = 1, y0 = 0;
    x1 = 0, y1 = 1;
    x = 0; y = 1;
    int r = a % b;
    int q = (a - r) % b;
    while (r) {
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1, y0 = y1;
        x1 = x, y1 = y;
        a = b; b = r; r = a % b;
        q = (a - r) % b;
    }
    return b;
}
```

動態規劃問題小結
====

動態規劃博大精深，我等菜鳥根本說不明道不盡哎...

揹包問題
---

首先，無論新手還是高手，都應該讀讀dd大神的神作[揹包九講](http://love-oriented.com/pack/pack2alpha1.pdf)吧我覺得...

至於訓練題，以前做了一些，不記得了...

> POJ [1745](http://poj.org/problem?id=1745) [3628](http://poj.org/problem?id=3628)

字符串相關的DP問題
----
基本屬於Palindrome, parentheses, bracket相關的一類.

> POJ [1141](http://poj.org/problem?id=1141) [1159](http://poj.org/problem?id=1159) [1458](http://poj.org/problem?id=1458) [2192](http://poj.org/problem?id=2192) [3267](http://poj.org/problem?id=3267) 

區間和相關的DP問題
----

> POJ [1050](http://poj.org/problem?id=1050) [2479](http://poj.org/problem?id=2479)

公共字串相關的DP問題
----

> POJ [1458](http://poj.org/problem?id=1458) [2127](http://poj.org/problem?id=2127)

最長遞增/減序列問題
----

> POJ [1952](http://poj.org/problem?id=1952) [2533](http://poj.org/problem?id=2533) [3616](http://poj.org/problem?id=3616)

區間動態規劃
----
> 致謝： http://www.cnblogs.com/zsboy/archive/2013/03/08/2950261.html

区间动态规划问题一般都是考虑，对于每段区间，他们的最优值都是由几段更小区间的最优值得到，是分治思想的一种应用，将一个区间问题不断划分为更小的区间直至一个元素组成的区间，枚举他们的组合 ，求合并后的最优值。
设F[i,j](1<=i<=j<=n)表示区间[i,j]内的数字相加的最小代价
最小区间F[i,i]=0（一个数字无法合并，∴代价为0）

每次用变量k (i<=k<=j-1), 将区间分为[i,k]和[k+1,j]两段

```C++
for p:=1 to n do // p是区间长度，作为阶段。 
    for i:=1 to n do // i是穷举的区间的起点
    begin
        j:=i+p-1; // j是 区间的终点，这样所有的区间就穷举完毕
        if j>n then break; // 这个if很关键。
        for k:= i to j-1 do // 状态转移，去推出 f[i,j]
            f[i , j]= max{f[ i,k]+ f[k+1,j]+ w[i,j] } 
    end; 
```

这个结构必须记好，这是区间动态规划的代码结构。

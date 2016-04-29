##问题说明

给一个树结构，计算每个节点的(x, y)坐标点，让一棵树 *不重叠*、*紧凑*、*对称* 地在平面上铺开。

##基本要求

输出：*不重叠*、*紧凑*、*对称*、`尽量美观`。
实现：通用，别太多if-else；好懂；效率高。

##基本想法

1. 先将一棵树按照类似于[二项堆](https://en.wikipedia.org/wiki/Binomial_heap)的方式开展，这一步主要是为了不重叠，效果图如下：

![tree-binomal-heap-style](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/tree-0.jpg)

  为了让底层叶子节点完全不重叠，一开始我们使用了贪婪策略，就是让和面的树节点大于当前最大的offset，所以我们在上图看到，一些节点之间存在没必要的空间。

2. 现在我们运用树的层序遍历，去掉所有`叶子节点`的spacing，这一步主要是为了不重叠紧凑，效果图如下：

![tree-binomal-heap-compact-style](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/tree-1.jpg)

3. 最后的问题是，怎么弄的对称一些呢？

  观察上图，我们每个父节点，或者可以向右移动一些位置，达到其子树所覆盖的区间的中间，或者，当右边已经没有空间让它移动时，则通过移动其子树来时其占据其所覆盖的中间，效果图如下：
  
![tree-binomal-heap-compact-style](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/tree-3.jpg)

##结论

首先，是可以达到基本要求的；时间复杂度都是O(n^2)，空间复杂度，因为层序遍历也达到了O(n)。一棵树要计算其layout，render出来，这个复杂度还是可以接受的。

这个算法，仅仅只是达到了了`不重叠`和`紧凑`，`对称`上是有折扣的。

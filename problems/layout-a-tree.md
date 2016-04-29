##问题说明

给一个树结构，计算每个节点的(x, y)坐标点，让一棵树 *不重叠*、*紧凑*、*对称* 地在平面上铺开。

##基本要求

输出：不重叠；紧凑；对称；尽量美观。
实现：通用，别太多if-else；好懂；效率。

##基本想法

1. 先将一棵树按照类似于二项堆的方式开展，效果图如下：

![tree-binomal-heap-style](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/tree-0.jpg)

  为了让底层叶子节点完全不重叠，一开始我们使用了贪婪策略，就是让和面的树节点大于当前最大的offset，所以我们在上图看到，一些节点之间存在没必要的空间。

2. 现在我们运用树的层序遍历，去掉所有`叶子节点`的spacing，稍微紧凑一些，如下图：

![tree-binomal-heap-compact-style](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/tree-1.jpg)

3. 最后的问题是，怎么弄的对称一些呢？

  观察上图，我们每个父节点，或者可以向右移动一些位置，达到其子树所覆盖的区间的中间，或者，当右边已经没有空间让它移动时，则通过移动其子树来时其占据其所覆盖的中间。
  
  这样就得到下图了：
  
![tree-binomal-heap-compact-style](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/tree-3.jpg)


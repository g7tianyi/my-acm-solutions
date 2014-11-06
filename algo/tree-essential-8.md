Threaded-Tree問題
====

還是從親愛的[馬叔叔](http://users.cis.fiu.edu/~weiss/)哪裡知道這麼個玩意的，計算機歷史上的人不得了啊，什麼都想過，這讓我越發想好好讀讀高老太爺的TAOCP了...

> Since a binary search tree with N nodes has N + 1 null references, half the space allocated in a binary search tree for link information is wasted. Suppose that if a node has a null left child, we make its left child link to its inorder predecessor, and if a node has a null right child, we make its right child link to its inorder successor.
> This is known as a threaded tree, and the extra links are called threads.
> 1. How can we distinguish threads from real children links?
> 2. Write routines to perform insertion and deletion into a tree threaded in themanner described above.
> 3. What is the advantage of using threaded trees?

後來查了查Wikipedia，[好東西呀](http://en.wikipedia.org/wiki/Threaded_binary_tree)，非常感謝！~

關於上面的問題：

1. 引入一些標記域來標識，如兩個 bool 域名 left_threaded, right_threaded
2. 見後面代碼
3. 抄襲Wikipedia：

> A threaded binary tree makes it possible to traverse the values in the binary tree via a linear traversal that is more rapid than a recursive in-order traversal. It is also possible to discover the parent of a node from a threaded binary tree, without explicit use of parent pointers or a stack, albeit slowly. This can be useful where stack space is limited, or where a stack of parent pointers is unavailable (for finding the parent pointer via DFS).

也就是說遍歷會提速，感覺優勢不明顯啊，看來真的需要查查TAOCP看看歷史故事到底咋回事兒~

*未完待續*

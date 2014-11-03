單鏈表問題總結3：合併問題（多路歸併）
====
多路歸併問題的介紹請見CLRS。單鏈表的歸併問題考察點其實還是在單鏈表的操作吧。

鏈表定義
----
```C++
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() :
        val(0), next(NULL) {
    }
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
```
合併兩個鏈表
----
```C++
// 因為就兩個鏈表，一種有趣的想法是，先把兩個鏈表收尾相接
// 然後兩個指針順著兩個鏈表走，發現後面鏈表的值比前面的大，就改變一下指向從而使鏈表有序
// 基本看看代碼就懂了應該
ListNode* mergeTwoLists(ListNode* head1, ListNode* head2) {
    // edge case
    if (head1 == NULL && head2 == NULL) {
        return NULL;
    }
    if (head1 == NULL && head2 != NULL) {
        return head2;
    }
    if (head1 != NULL && head2 == NULL) {
        return head1;
    }
    
    // select the head
    ListNode *head, *rear, *other;
    if (head1->val < head2->val) {
        head = head1, rear = head1, other = head2;
    } else {
        head = head2, rear = head2, other = head1;
    }

    // link two lists
    while (rear->next) {
        rear = rear->next;
    }
    rear->next = other;

    // curr1 is the cursor pointer in the former list
    // curr2 is the cursor pointer in the latter list
    ListNode *curr1 = head, *curr2 = other, *next1, *next2;
    while (curr1 != rear && curr2) {
        next1 = curr1->next, next2 = curr2->next;
        if (curr1->next->val > curr2->val) { 
            // insert node curr2 in list 2 into list 1
            // ...13->21->...->15->19->...
            //     |            |
            //   curr1        curr2
            curr1->next = curr2;
            curr2->next = next1;
            rear->next = next2;
            curr1 = curr2, curr2 = next2;
        } else {
            // ...13->14->16->...->15->19->...
            //     |            |
            //   curr1        curr2
            curr1 = next1;
        }
    }

    return head;
}
```
合併多個鏈表
----
這個就是標準的K路歸併問題的解決辦法了，建立最大/小堆，複雜度為 nlogk。

關於堆的實現，請參考[這裡](https://github.com/g7tianyi/my-acm-solutions/blob/master/algo/heap.md)。

```C++
struct ListNodeCompare {
    bool operator()(const ListNode* lhs, const ListNode* rhs) {
        if (lhs == NULL && rhs == NULL) {
            return true;
        } 
        if (lhs != NULL && rhs == NULL) {
            return true;
        } 
        if (lhs == NULL && rhs != NULL) {
            return false;
        } 
        return lhs->val > rhs->val;
    }
};

ListNode* mergeKLists(vector<ListNode *>& lists) {
    Heap<ListNode*, ListNodeCompare> kHeap;
    for (int i = 0; i < lists.size(); ++i) {
        if (lists[i]) {
            kHeap.push(lists[i]);
        }
    }

    ListNode *head = NULL, *hCurr = NULL;
    ListNode *curr, *next;
    while (!kHeap.empty()) {
        curr = kHeap.pop();
        next = curr->next;

        if (hCurr) {
            hCurr->next = curr;
            hCurr = hCurr->next;
        } else {
            head = curr;
            hCurr = head;
        }

        if (next) {
            kHeap.push(next);
        }
    }

    return head;
}
```


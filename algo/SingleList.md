单链表总结
=========
```C++
// Firstly, define the (Singly) List Node
struct ListNode {
    int value;
    ListNode* next;
        : value(0), next(NULL) {
    }
    ListNode(int val) 
        : value(val), next(NULL) {
    }
};
```
- 反转
----
不知道为什么这么喜欢考，Mark Allen Weiss的宝书啊！

 - Itertion style
```C++
ListNode* reverseIteration(ListNode* head) {
    if (head == NULL) {
        return NULL;
    }
    ListNode* prev = NULL;
    ListNode* curr = head;
    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```
 - Recursion style
```C++
// Helper function
void reverseRecursion(ListNode** pHead) {
    ListNode* first = *pHead;
    if (first == NULL) {
        return;
    }
    if (first->next == NULL) {
        return;
    }
    ListNode* rest = first->next;
    reverseRecursion(&rest);
    first->next->next = first;
    first->next = NULL;
    *pHead = rest;
}

ListNode* reverseRecursion(ListNode* head) {
    if (head == NULL) {
        return NULL;
    }
    reverseRecursion(&head);
    return head;
}
```
 - Test
```C++
ListNode nodes[10];

int main() {

    printf("Test reversing list in iteration style: ");
    for (int i = 0; i < 9; ++i) {
        nodes[i].value = i + 1;
        nodes[i].next = &nodes[i + 1];
    }
    nodes[9].value = 10;
    nodes[9].next = NULL;
    ListNode* head = reverseIteration(&nodes[0]);
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");

    printf("Test reversing list in recursion style: ");
    for (int i = 0; i < 9; ++i) {
        nodes[i].value = i + 1;
        nodes[i].next = &nodes[i + 1];
    }
    nodes[9].next = NULL;
    head = reverseRecursion(&nodes[0]);
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");

    return 0;
}
```
- 单链表环的问题
----
 - 判断是否有环
```C++
// 原理请Google，年纪大了，打字累... >_<
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}
```
- 找到入口
``` C++
ListNode *detectCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }
    
    if (!fast || !fast->next) {
        return NULL;
    }

    // grab a pen and draw an illustration...
    //
    // the time when fast and slow meet with each other,
    // journey of slow is, S
    // hourney of fast is, 2S = S + n * R
    // n is the count fast has been travelled in the cycle
    // R is the length of the cycle
    //
    // also note the whole length of the list to be L,
    // X to be the length of the meeting point to the node where the cycle begins
    // A to be the length of the start to the node where the cycle begins
    //
    // A + X = n * R = (n - 1) * R + R = (n - 1) * R + L - A
    // ==> A = (n - 1) * R + (L - A - X)
    // (L - A - X) is the length of the meeting point to the node where the cycle begins
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return fast;
}
```
- Test
https://github.com/g7tianyi/my-acm-solutions/blob/master/leetcode/linked-list-cycle.cc
https://github.com/g7tianyi/my-acm-solutions/blob/master/leetcode/linked-list-cycle-ii.cc

- 有环链表的反转
----
待续


- 链表排序
----
待续




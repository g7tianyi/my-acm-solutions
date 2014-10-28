单链表总结2: 链表排序
=========
链表定义及辅助函数
----
```C++
struct ListNode {
    int value;
    ListNode* next;
    ListNode() :
        value(0), next(NULL) {
    }
};

static inline void swap(int& a, int& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}
```
冒泡排序
----
```C++
void bubbleSort(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }

    ListNode* slow = head;
    while (slow) {
        ListNode* fast = head;
        while (fast && fast->next) {
            if (fast->value > fast->next->value) {
                swap(fast->value, fast->next->value);
            }
            fast = fast->next;
        }
        slow = slow->next;
    }
}
```
插入排序
----
```C++
void insertionSort(ListNode* &head) {
    if (head == NULL || head->next == NULL) {
        return;
    }

    ListNode *curr = head->next, *prev = NULL, *next = NULL;
    ListNode *temp = NULL;
    head->next = NULL;
    while (curr) {
        next = curr->next;
        if (curr->value < head->value) {
            curr->next = head;
            head = curr;
        } else {
            prev = head;
            temp = head->next;
            while (temp && temp->value < curr->value) {
                prev = prev->next;
                temp = temp->next;
            }
            prev->next = curr;
            curr->next = temp;
        }
        curr = next;
    }
}
```
选择排序
----
```C++
void selectionSort(ListNode* head) {
    ListNode *slow, *fast, *mini;
    for (slow = head; slow->next; slow = slow->next) {
        for (mini = slow, fast = slow->next; fast; fast = fast->next) {
            if (fast->value < mini->value) {
                mini = fast;
            }
        }
        if (mini != slow) {
            swap(mini->value, slow->value);
        }
    }
}
```
归并排序
----
```C++
// 这个最风骚了，单链表排序默认应该就是归并表现最优秀吧
static ListNode* merge(ListNode* head1, ListNode* head2) {
    if (!head1 && !head2) {
        return NULL;
    }
    if (head1 && !head2) {
        return head1;
    }
    if (!head1 && head2) {
        return head2;
    }

    ListNode* head = NULL;
    if (head1->value < head2->value) {
        head = head1;
        head1 = head1->next;
    } else {
        head = head2;
        head2 = head2->next;
    }

    ListNode* curr = head;

    while (head1 && head2) {
        if (head1->value < head2->value) {
            curr->next = head1;
            head1 = head1->next;
        } else {
            curr->next = head2;
            head2 = head2->next;
        }
        curr = curr->next;
    }

    if (head1) {
        curr->next = head1;
    } else if (head2) {
        curr->next = head2;
    } else {
        curr->next = NULL;
    }

    return head;
}

void mergeSort(ListNode* &head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    ListNode* fast = head;
    ListNode* slow = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    ListNode* former = head;
    ListNode* latter = slow->next;
    slow->next = NULL;
    mergeSort(former);
    mergeSort(latter);
    head = merge(former, latter);
}
```
快速排序
----
```C++
// TODO: 比较考验功力呀...
```
测试
----
```C++
#include <random>
#include <ctime>

const int NODE_COUNT = 20;
ListNode nodes[NODE_COUNT];

inline void initTest() {
    for (int i = 0; i < NODE_COUNT - 1; ++i) {
        nodes[i].value = rand() % 100;
        nodes[i].next = &nodes[i + 1];
    }
    nodes[NODE_COUNT - 1].value = rand() % 100;
    nodes[NODE_COUNT - 1].next = NULL;
}

inline void printList(ListNode* head) {
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

int main() {
    ListNode* head = NULL;
    srand((unsigned) time(0));

    printf("Test bubbleSort: ");
    initTest();
    head = &nodes[0];
    bubbleSort(head);
    printList(head);

    printf("Test insertionSort: ");
    initTest();
    head = &nodes[0];
    insertionSort(head);
    printList(head);

    printf("Test selectionSort: ");
    initTest();
    head = &nodes[0];
    selectionSort(head);
    printList(head);

    printf("Test mergeSort: ");
    initTest();
    head = &nodes[0];
    mergeSort(head);
    printList(head);

    return 0;
}
```

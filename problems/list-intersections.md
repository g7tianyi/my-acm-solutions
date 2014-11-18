經典問題：求兩個鏈表的交點
====

簡單說明一下，主要考慮三種情況：

1. 雙方無環，這個case最簡單；
2. 雙方有環： 
	- 2.1 交點在環外
	- 2.2 交點在環上

下圖所示，

![list-intersection](https://github.com/g7tianyi/my-acm-solutions/blob/master/images/list-intersection.png)

##編程實現

```C++
#include <iostream>

namespace list {

template<typename T>
struct list_node {
    T value;
    list_node<T>* next;
    list_node() :
        value(T()), next(NULL) {
    }
    list_node(const T _value) :
        value(_value), next(NULL) {
    }
};

template<typename T>
list_node<T>* list_rear(list_node<T>* head) {
    if (head == NULL) {
        return NULL;
    }
    list_node<T>* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    return curr;
}

// return the distance of two list node
// if two nodes are not in the same list, function return -1
// if node is NULL, function return the length of the list
template<typename T>
int node_distance(list_node<T>* head, list_node<T>* node = NULL) {
    if (head == NULL) {
        return -1;
    }
    int distance = 1;
    list_node<T>* curr = head;
    while (curr->next != node) {
        if (curr->next == NULL) {
            return -1;
        }
        ++distance;
        curr = curr->next;
    }
    return distance;
}

template<typename T>
list_node<T>* check_loop(list_node<T>* head) {
    list_node<T>* slow = head;
    list_node<T>* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }

    if (fast == NULL || fast->next == NULL) {
        return NULL;
    }

    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

template<typename T>
list_node<T>* __get_non_looped_intersection(list_node<T>* head1, list_node<T>* head2) {
    if (head1 == NULL || head2 == NULL) {
        return NULL;
    }

    list_node<T>* rear1 = list_rear(head1);
    list_node<T>* rear2 = list_rear(head2);

    if (rear1 != rear2) {
        return NULL;
    }

    int len1 = node_distance(head1);
    int len2 = node_distance(head2);
    int more = 0;
    list_node<T>* longer = NULL;
    list_node<T>* shorter = NULL;
    if (len1 > len2) {
        more = len1 - len2;
        longer = head1;
        shorter = head2;
    } else {
        more = len2 - len1;
        longer = head2;
        shorter = head1;
    }

    while (more--) {
        longer = longer->next;
    }

    while (longer != shorter) {
        longer = longer->next;
        shorter = shorter->next;
    }

    return longer;
}

template<typename T>
list_node<T>* __get_looped_intersection(
        list_node<T>* head1, list_node<T>* loop_entry1,
        list_node<T>* head2, list_node<T>* loop_entry2) {
    if (loop_entry1 == NULL && loop_entry1 == NULL) {
        return __get_non_looped_intersection(head1, head2);
    }

    if (loop_entry1 == NULL || loop_entry2 == NULL
            || loop_entry1->next == NULL || loop_entry2->next == NULL) {
        return NULL;
    }

    bool intersected = false;
    list_node<T>* curr = loop_entry1;
    do {
        if (curr == loop_entry2) {
            intersected = true;
            break;
        }
        curr = curr->next;
    } while (curr != loop_entry1);

    if (!intersected) {
        return NULL;
    }

    if (loop_entry1 == loop_entry2) { // share the same loop point
        // get the distance between the list head and the loop entry
        int distance1 = node_distance(head1, loop_entry1);
        int distance2 = node_distance(head2, loop_entry2);
        int more = 0;
        list_node<T>* longer = NULL;
        list_node<T>* shorter = NULL;
        if (distance1 > distance2) {
            more = distance1 - distance2;
            longer = head1;
            shorter = head2;
        } else {
            more = distance2 - distance1;
            longer = head2;
            shorter = head1;
        }

        while(more--) {
            longer = longer->next;
        }

        while (longer != shorter) {
            longer = longer->next;
            shorter = shorter->next;
        }
        return longer;

    } else {
        // these two lists share two common node
        // return anyone of them
        return loop_entry1;
    }

}

template<typename T>
list_node<T>* get_intersection(list_node<T>* head1, list_node<T>* head2) {
    if (head1 == NULL || head2 == NULL) {
        return NULL;
    }

    list_node<T>* loop_point1 = check_loop(head1);
    list_node<T>* loop_point2 = check_loop(head2);

    // both of the two list have no loop within
    if (loop_point1 == NULL && loop_point2 == NULL) {
        return __get_non_looped_intersection(head1, head2);
    }

    // both of the two list are looped
    if (loop_point1 && loop_point2) {
        return __get_looped_intersection(head1, loop_point1, head2, loop_point2);
    }

    return NULL;
}

} // end of namespace list


//
// test below
#include <algorithm>

list::list_node<int> nodes1[10];
list::list_node<int> nodes2[10];

void init() {
    for (int i = 0; i < 9; ++i) {
        nodes1[i].value = 10 + i;
        nodes1[i].next  = &nodes1[i + 1];
        nodes2[i].value = 20 + i;
        nodes2[i].next  = &nodes2[i + 1];
    }
    nodes1[9].value = 19, nodes1[9].next = NULL;
    nodes2[9].value = 29, nodes2[9].next = NULL;
}

int main() {

    {
        std::cout << ">>> Testing no intersection: " << std::endl;
        init();
        list::list_node<int>* intersection = list::get_intersection(&nodes1[0], &nodes2[0]);
        if (intersection) {
            std::cout << "intersection node: " << intersection->value << std::endl;
        } else {
            std::cout << "no intersection node found" << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << ">>> Testing intersection with no loop: " << std::endl;
        init();
        nodes2[7].next = &nodes1[4];
        // should output 14
        list::list_node<int>* intersection = list::get_intersection(&nodes1[0], &nodes2[0]);
        if (intersection) {
            std::cout << "intersection node: " << intersection->value << std::endl;
        } else {
            std::cout << "no intersection node found" << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << ">>> Testing intersection with loop (one common node): " << std::endl;
        init();
        // should output 13
        nodes1[9].next = &nodes1[5];
        nodes2[7].next = &nodes1[3];
        list::list_node<int>* intersection = list::get_intersection(&nodes1[0], &nodes2[0]);
        if (intersection) {
            std::cout << "intersection node: " << intersection->value << std::endl;
        } else {
            std::cout << "no intersection node found" << std::endl;
        }
        std::cout << std::endl;
    }

    {
        std::cout << ">>> Testing intersection with loop (two common nodes): " << std::endl;
        init();
        // should output 14 or 17
        nodes1[9].next = &nodes1[4];
        nodes2[7].next = &nodes1[7];
        list::list_node<int>* intersection = list::get_intersection(&nodes1[0], &nodes2[0]);
        if (intersection) {
            std::cout << "intersection node: " << intersection->value << std::endl;
        } else {
            std::cout << "no intersection node found" << std::endl;
        }
        std::cout << std::endl;
    }
}

```

/*
 * list_cpp.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>

struct ListNode {
    int num;
    ListNode *next;
};
ListNode * create(int n)
{
    if (0 == n) {
        return nullptr;
    }
    ListNode *head, *p1, *p2;
    head = p1 = p2 = new ListNode;
    std::cout << "Enter num: ";
    std::cin >> p1->num;
    while (0 < --n) {
        p2 = new ListNode;
        p1->next = p2;
        p1 = p2;
        std::cout << "Enter num: ";
        std::cin >> p1->num;
    }
    p1->next = nullptr;
    return head;
}

void printList(const ListNode *head)
{
    const ListNode *p = head;
    while (p != nullptr) {
        std::cout << p->num << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

int deleteNode(ListNode *head)
{
    int cnt = 0;
    ListNode *p = head;
    while (head != nullptr) {
        p = head;
        head = head->next;
        std::cout << "**" << &p << std::endl;
        delete p;
        std::cout << "**" << &p << std::endl;
        ++cnt;
    }
    return cnt;
}

ListNode* reverse(ListNode *head)
{
    if (nullptr == head)
        return nullptr;
    ListNode *t, *p1, *p2;
    t = p1 = head;
    p2 = head->next;
    while (nullptr != p2) {
        p1 = p2;
        p2 = p2->next;
        p1->next = head;
        head = p1;
    }
    t->next = nullptr;
    return head;
}

int main(void)
{
    int n;
    std::cout << "Enter list length: ";
    std::cin >> n;
    ListNode *head = create(n);
    std::cout << "List: " << std::endl;
    printList(head);
    head = reverse(head);
    std::cout << "Reverse List: " << std::endl;
    printList(head);
    std::cout << "delete: " << deleteNode(head) << " list node." << std::endl;
    return 0;
}



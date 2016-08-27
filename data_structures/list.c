/*
 * list.c
 * Copyright (C) 2016 blueyi <blueyi@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int num;
    struct ListNode *next;
};

struct ListNode* create(int num)
{
    struct ListNode *head, *p1, *p2;
    if (num == 0)
        return NULL;
    head = p1 = p2 = (struct ListNode *) malloc(sizeof(struct ListNode));
    printf("Enter num: ");
    scanf("%d", &p1->num);
    while (--num > 0) {
        p1 = (struct ListNode *)malloc(sizeof(struct ListNode));
        p2->next = p1;
        printf("Enter num: ");
        scanf("%d", &p1->num);
        p2 = p1;
    }
    p2->next = NULL;
    return head;
}
struct ListNode* reverse(struct ListNode *head)
{
    if (head == NULL)
        return NULL;
    struct ListNode *p1, *p2, *t;
    t = p1 = p2 = head;
    while (p2 != NULL) {
        p1 = p2;
        p2 = p2->next;
        p1->next = head;
        head = p1;
    }
    t->next = NULL;
    return head;
}
int delete(struct ListNode *head)
{
    int cont = 0;
    struct ListNode *p;
    while (head != NULL) {
        p = head;
        head = head->next;
        free(p);
        printf("**%d\n", sizeof(p));
        ++cont;
    }
    return cont;
}
void print(struct ListNode *head)
{
    struct ListNode *p = head;
    if (p == NULL)
        return;
    do {
        printf("%d ", p->num);
        p = p->next;
    } while (p != NULL); 

}
int main(void)
{
    printf("Enter list length: ");
    int num;
    scanf("%d", &num);
    struct ListNode *head = create(num);
    if (head == NULL)
        return 0;
    printf("List:\n");
    print(head);
    printf("\nReverse:\n");
    head = reverse(head);
    print(head);
    printf("\n");
    printf("Delete: %d\n", delete(head));
    return 0;
}





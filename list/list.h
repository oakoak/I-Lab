#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct List_elem
{
    struct List_elem* left;
    struct List_elem* right;
    char* data;
};

struct List
{
    List_elem* head;
    List_elem* tail;
    int amount;
};

List* list_crt (List* head);

enum {FALSE = 0, TRUE = 1};
enum {FIRST=0, LAST = 1, BEFORE = 4, AFTER = 5};

enum
{
    GOOD_LIST = 0,
    NULL_LIST_P = 1,
    WRONG_LIST_HEAD,
    WRONG_LIST_TAIL,
    PREV_NEXT_CHAOS,
    NULL_IN_MID,
    NEG_COUNTER,
    UNEXP_RELEV
};

//int List_errno = GOOD_LIST;





List_elem* add_right_element_list(List* head, List_elem* elem, char*    data);
/*
    adds an element after a specified element

    head    -   a pointer to the element after which it is necessary to add a new

    data    -   value of the new item in the list

    return returns a pointer to the new element

*/
List_elem* add_in_beginning_list (List* head, char* data);
/*
    inserts an element at the beginning of the list(

    head    -   pointer to any item in the list

    data    -   value of the new item in the list

    return returns a pointer to the new element
*/
int delete_element_list(List* head, List_elem* elem);
/*
    removes the specified item

    head    -   a pointer to the item you want to delete
*/
int delete_all_list(List* head);
/*
    removes all list
*/

#endif

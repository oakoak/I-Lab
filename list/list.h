#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


struct List
{
    struct List* left;
    struct List* right;
    int data;
};

List* add_right_element_list(List* head, int data);
/*
    adds an element after a specified element

    head    -   a pointer to the element after which it is necessary to add a new

    data    -   value of the new item in the list

    return returns a pointer to the new element

*/
List* add_in_beginning_list (List* head, int data);
/*
    inserts an element at the beginning of the list(

    head    -   pointer to any item in the list

    data    -   value of the new item in the list

    return returns a pointer to the new element
*/
int delete_element_list(List* head);
/*
    removes the specified item

    head    -   a pointer to the item you want to delete
*/
int delete_all_list(List* head);
/*
    removes all list
*/

#endif

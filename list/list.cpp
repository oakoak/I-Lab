#include "list.h"

int list_ok (List* head)

List* add_right_element_list(List* head, int data)
{
    List* New = (List*) malloc(sizeof(List));
    assert(New);
    New->data = data;
    New->right = NULL;
    if (head == NULL)
    {
        head = New;
        New->left = NULL;
    }
    else
    {
        if (head->right != NULL)
        {
            head->right->left = New;
            New->right = head->right->left;
        }
        head->right = New;
        New->left = head;
    }
    return New;
}

List* add_in_beginning_list (List* head, int data)
{
    List* New = (List*) malloc(sizeof(List));
    assert(New);
    New->data = data;
    New->left = NULL;
    if (head == NULL)
    {
        head = New;
        New->right = NULL;
    }
    else
    {
    while (head->left != NULL)
        head = head->left;
        New->right = head;
    head->left = New;
    }
    return New;
}

int delete_element_list(List* head)
{
    if (head->right == NULL)
    {
        if (head->left != NULL)
            head->left->right = NULL;
    }
    else
    {
        if (head->left == NULL)
            head->right->left = NULL;
        else
        {
            head->left->right = head->right;
            head->right->left = head->left;
        }
    }
    free(head);
    head = NULL;
}

int delete_all_list(List* head)
{
    if (head != NULL)
    {
        while (head->left != NULL)
            head = head->left;
        List* del = head;
        while (head != NULL)
        {
            del = head;
            head = head->right;
            free(del);
        }
        del = NULL;
    }
    return 0;
}

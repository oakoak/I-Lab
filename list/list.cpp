#include "list.h"

int list_ok (List* head)
{
    List_elem* counter = head->head;
    for(int i = 0;i < head->amount; i++)
    {
        //if
        //counter = counter->next
    }
}

List* list_crt (List* head)
{
	head->head = NULL;
	head->tail = NULL;
	head->amount = 0;
	return head;
}

/*
#define next right
#define prev left
#define counter amount

int List_ok(struct List* list_p)
{
    if (!list_p)
    {
        List_errno = NULL_LIST_P;
        return FALSE;
    }

	if(list_p->counter < 0)
    {
        List_errno = NEG_COUNTER;
        return FALSE;
    }

	struct List_elem* cur_elem_p = list_p->head;
	for (long i = 0; i < list_p->counter; i++)
	{
    	if (cur_elem_p == NULL)
        {
        	List_errno = NULL_IN_MID;
            return FALSE;
        }
        cur_elem_p = cur_elem_p->next;
    }

    if (cur_elem_p)
    {
 	   List_errno = WRONG_LIST_TAIL;
       return FALSE;
    }

    cur_elem_p = list_p->tail;
    for (long i = 0; i < list_p->counter; i++)
	{
	    if (cur_elem_p == NULL)
        {
	        List_errno = NULL_IN_MID;
            return FALSE;
        }
        cur_elem_p = cur_elem_p->prev;
    }

    if (cur_elem_p)
    {
	    List_errno = WRONG_LIST_HEAD;
        return FALSE;
    }

    cur_elem_p = list_p->head;
    while (cur_elem_p)
    {
    	if ( (cur_elem_p->prev && cur_elem_p->prev->next != cur_elem_p) ||
    	   (cur_elem_p->next && cur_elem_p->next->prev != cur_elem_p))
        {
	        List_errno = PREV_NEXT_CHAOS;
            return FALSE;
        }
        cur_elem_p = cur_elem_p->next;
    }
    List_errno = GOOD_LIST;
    return TRUE;
}
*/




List_elem* add_right_element_list(List* head, List_elem* elem, char* data)
{
    assert(head);
    List_elem* New = (List_elem*) malloc(sizeof(List_elem));
    assert(New);
    New->data = data;
    New->right = NULL;
    if (head->head == NULL)
    {
        head->head = New;
        New->left = NULL;
        head->tail = New;
        head->amount++;
        return New;
    }

    if (elem->right != NULL)
    {
        elem->right->left = New;
        New->right = elem->right->left;
    }
    else
        head->tail = New;

    elem->right = New;
    New->left = elem;
    head->amount++;
    return New;
}

List_elem* add_in_beginning_list (List* head, char* data)
{
    List_elem* New = (List_elem*) malloc(sizeof(List_elem));
    assert(New);
    New->data = data;
    New->left = NULL;
    New->right = head->head;
	if (head->head == NULL)
		head->tail = New;
	else
		head->head->left = New;
    head->head = New;
    head->amount++;
    return New;
}

int delete_element_list(List* head, List_elem* elem)
{
    assert(head);
    assert(elem);
    List_elem* del_elem = elem;
    if (elem->right == NULL)
    {
        head->tail = elem->left;
        if (elem->left != NULL)
            elem->left->right = NULL;
    }
    else
    {
        if (elem->left == NULL)
        {
            head->head = elem->right;
            elem->right->left = NULL;
        }
        else
        {
            elem->left->right = elem->right;
            elem->right->left = elem->left;
        }
    }
    head->amount--;
    free(head);
    head = NULL;
}

int delete_all_list(List* head)
{
    List_elem* del1 = head->head;
    List_elem* del2 = NULL;
    for (int i = 0; i < head->amount; i++)
    {
        del2 = del1;
        del1 = del1->right;
		if(del2 != NULL)
		{
        	del2->left = NULL;
        	del2->right = NULL;
			free(del2);
		}
    }
    head->amount = 0;
    head->head = NULL;
    head->tail = NULL;
    return 0;
}

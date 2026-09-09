#include "dll.h"

int dl_insert_first(Dlist **head, Dlist **tail, int data)
{

}

int dl_insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *newNode = (Dlist *)malloc(sizeof(Dlist));

    if(newNode == NULL)
        return FAILURE;
    
    newNode -> data = data;
    newNode -> prev = NULL;
    newNode -> next = NULL;

    if(*head == NULL)
    {
        *head = newNode;
        *tail = newNode;
        return SUCCESS;
    }

    newNode -> prev = *tail;
    (*tail) -> next = newNode;
    *tail = newNode;

    return SUCCESS;

}

void print_list(Dlist *head)
{
    if(head == NULL)
    {
        printf("INFO : List is empty\n");
        return;
    }

    while (head != NULL)
    {
        printf("%d", head -> data);
        head = head -> next;
    }
    printf("\n");
    
}
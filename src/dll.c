#include "dll.h"

int dl_insert_first(Dlist **head, Dlist **tail, int data)
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

    newNode -> next = *head;
    (*head) -> prev = newNode;
    *head = newNode;

    return SUCCESS;
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

int dl_delete_first(Dlist **head, Dlist **tail)
{
    if(*head == NULL)
        return FAILURE;

    Dlist *temp = *head;
   
    if(*head == *tail)
    {
        *head = NULL;
        *tail = NULL;
    }
    else
    {
        *head = (*head) -> next;
        (*head) -> prev = NULL;
    }
    free(temp);

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
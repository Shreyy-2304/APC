#ifndef APC_H
#define APC_H

#include "dll.h"

int str_to_list(char *str, Dlist **head, Dlist **tail, int *sign);
int addition(Dlist *tail1, Dlist *tail2, Dlist **result_head, Dlist **result_tail);
int subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **result_head, Dlist **result_tail);
int compare_lists(Dlist *head1, Dlist *head2);


#endif
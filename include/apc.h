#ifndef APC_H
#define APC_H

#include "dll.h"

int str_to_list(char *str, Dlist **head, Dlist **tail, int *sign);
int addition(Dlist *tail1, Dlist *tail2, Dlist **result_head, Dlist **result_tail);

#endif
#include "apc.h"

int str_to_list(char *str, Dlist **head, Dlist **tail, int *sign)
{
    int all_zero = 1;

    /* Check sign */
    if (str[0] == '-')
    {
        *sign = -1;
        str++;
    }
    else
    {
        *sign = 1;
    }

    /* Check whether the number is zero */
    char *temp = str;

    while (*temp != '\0')
    {
        if (*temp != '0')
        {
            all_zero = 0;
            break;
        }

        temp++;
    }

    /* Zero should always have positive sign */
    if (all_zero)
    {
        *sign = 1;
    }

    /* Convert each digit into DLL node */
    while (*str != '\0')
    {
        if (dl_insert_last(head, tail, *str - '0') == FAILURE)
        {
            return FAILURE;
        }

        str++;
    }

    return SUCCESS;
}
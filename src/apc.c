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

   /* -0, -00, etc. should become +0 */
    if (all_zero)
    {
        *sign = 1;

        if (dl_insert_last(head, tail, 0) == FAILURE)
        {
            return FAILURE;
        }

        return SUCCESS;
    }

    /* Skip leading zeros */
    while (*str == '0')
    {
        str++;
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

int addition(Dlist *tail1, Dlist *tail2, Dlist **result_head, Dlist **result_tail)
{
    int carry = 0, sum;

    while(tail1 != NULL || tail2 != NULL)
    {
        int digit1 = 0, digit2 = 0;

        if(tail1 != NULL)
            digit1 = tail1 -> data;
        
        if(tail2 != NULL)
            digit2 = tail2 -> data;

        sum = digit1 + digit2 + carry;

        if (dl_insert_first(result_head, result_tail, sum % 10) == FAILURE)
        {
            return FAILURE;
        }

        carry = sum / 10;

        if(tail1 != NULL)
            tail1 = tail1 -> prev;

        if(tail2 != NULL)
            tail2 = tail2 -> prev;  
    }
    if(carry != 0)
    {
        if(dl_insert_first(result_head, result_tail, carry) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}
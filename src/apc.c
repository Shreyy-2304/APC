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

int compare_lists(Dlist *head1, Dlist *head2)
{
    int count1 = 0, count2 = 0;

    Dlist *temp1 = head1, *temp2 = head2;

    //count nodes in list1
    while(temp1 != NULL)
    {
        count1++;
        temp1 = temp1 -> next;
    }

    //count nodes in list2
    while(temp2 != NULL)
    {
        count2++;
        temp2 = temp2 -> next;
    }

    //compare count
    if(count1 > count2)
        return 1;
    else if(count1 < count2)
        return -1;

    //if same no of digits, compare digit by digit
    temp1 = head1, temp2 = head2;

    while(temp1 != NULL)
    {
        if(temp1 -> data > temp2 -> data)
            return 1;
        else if(temp1 -> data < temp2 -> data)
            return -1;

        temp1 = temp1 -> next;
        temp2 = temp2 -> next;
    }
    return 0;
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

int subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **result_head, Dlist **result_tail)
{
    int borrow = 0, diff;

    while(tail1 != NULL)
    {
        int digit1 = tail1 -> data;
        int digit2 = 0;

        if(tail2 != NULL)
        {
            digit2 = tail2 -> data;
        }
        digit1 = digit1 - borrow;

        if(digit1 < digit2)
        {
            digit1 = digit1 + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        diff = digit1 - digit2;

        if(dl_insert_first(result_head, result_tail, diff) == FAILURE)
        {
            return FAILURE;
        }

        tail1 = tail1 -> prev;

        if(tail2 != NULL)
        {
            tail2 = tail2 -> prev;
        }
    }

    while(*result_head != NULL && (*result_head) -> data == 0 && *result_head != *result_tail)
    {
        dl_delete_first(result_head, result_tail);
    }
    return SUCCESS;
}

int multiplication(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **result_head, Dlist **result_tail)
{
    Dlist *temp_head = NULL, *temp_tail = NULL;
    Dlist *new_result_head = NULL, *new_result_tail = NULL;
    Dlist *temp1, *temp2;
    int carry, prod, shift = 0;

    temp2 = tail2;

    while(temp2 != NULL)
    {
        dl_delete_list(&temp_head, &temp_tail);
    
        carry = 0;
        temp1 = tail1;

        while(temp1 != NULL)
        {
            prod = temp1 -> data * temp2 -> data + carry;

            if(dl_insert_first(&temp_head, &temp_tail, prod % 10) == FAILURE)
            {
                return FAILURE;
            }
            carry = prod / 10;
            temp1 = temp1 -> prev;
        }

        if(carry != 0)
        {
            if(dl_insert_first(&temp_head, &temp_tail, carry) == FAILURE)
            {
                return FAILURE;
            }
        }

        for(int i = 0; i < shift; i++)
        {
            if(dl_insert_last(&temp_head, &temp_tail, 0) == FAILURE)
            {
                return FAILURE;
            }
        }
        if(addition(temp_tail, *result_tail,
            &new_result_head, &new_result_tail) == FAILURE)
        {
            return FAILURE;
        }
        
        dl_delete_list(result_head, result_tail);

        *result_head = new_result_head;
        *result_tail = new_result_tail;

        new_result_head = NULL;
        new_result_tail = NULL;

        shift++;
        temp2 = temp2 -> prev;
    }
    return SUCCESS;
}
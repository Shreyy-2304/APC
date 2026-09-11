#include "dll.h"
#include "validate.h"
#include "apc.h"

int main(int argc, char *argv[])
{
    //head and tail for list1
    Dlist *head1 = NULL;
    Dlist *tail1 = NULL;

    //head nad tail for list2
    Dlist *head2 = NULL;
    Dlist *tail2 = NULL;

    //head and tail for result list
    Dlist *result_head = NULL;
    Dlist *result_tail = NULL;

    //sign variables
    int sign1 = 1;
    int sign2 = 1;
    int result_sign = 1;

    if(validate_arguments(argc, argv) == FAILURE)
    {
        return FAILURE;
    }

    //convert first operand to DLL
    if(str_to_list(argv[1], &head1, &tail1, &sign1) == FAILURE)
    {
        printf("ERROR : Failed to parse first operand\n");
        return FAILURE;
    }

    //convert second operand to DLL
    if(str_to_list(argv[3], &head2, &tail2, &sign2) == FAILURE)
    {
        printf("ERROR : Failed to parse the second operand\n");
        return FAILURE;
    }

    // int comparison = compare_lists(head1, head2);
    // printf("Comparison: %d\n", comparison);

    printf("First Number : ");
    print_list(head1);

    printf("Second Number : ");
    print_list(head2);

    printf("Sign 1: %d\n", sign1);
    printf("Sign 2: %d\n", sign2);

    int comparison;
    /* Select operation */
    switch (argv[2][0])
    {
        case '+':
            {
                if(sign1 == sign2)
                {
                    if (addition(tail1, tail2, &result_head, &result_tail) == FAILURE)
                    {
                        printf("ERROR: Addition failed\n");
                        return FAILURE;
                    } 
                    result_sign = sign1;      
                }
                else
                {
                    comparison = compare_lists(head1, head2);

                    if(comparison > 0)
                    {
                        if (subtraction(head1, tail1, head2, tail2, &result_head, &result_tail) == FAILURE)
                        {
                            printf("ERROR: Subtraction failed\n");
                            return FAILURE;
                        }
                        result_sign = sign1; 
                    }
                    else if (comparison < 0)
                    {
                        if (subtraction(head2, tail2, head1, tail1, &result_head, &result_tail) == FAILURE)
                        {
                            printf("ERROR: Subtraction failed\n");
                            return FAILURE;
                        }
                        result_sign = sign2;
                    }
                    else
                    {
                        if (dl_insert_first(&result_head, &result_tail, 0) == FAILURE)
                        {
                            printf("ERROR: Failed to create result\n");
                            return FAILURE;
                        }
                        result_sign = 1;
                    }
                    
                }
                break;
            }
            
        case '-':
        {
            if(sign1 == 1 && sign2 == 1)
            {
                /* +A - +B */
                comparison = compare_lists(head1, head2);

                if(comparison > 0)
                {
                    if (subtraction(head1, tail1, head2, tail2, &result_head, &result_tail) == FAILURE)
                    {
                        printf("ERROR: Subtraction failed\n");
                        return FAILURE;
                    }
                    result_sign = 1;
                }
                else if (comparison < 0)
                {
                    if (subtraction(head2, tail2, head1, tail1, &result_head, &result_tail) == FAILURE)
                    {
                        printf("ERROR: Subtraction failed\n");
                        return FAILURE;
                    }
                    result_sign = -1;
                }
                else
                {
                    dl_insert_first(&result_head, &result_tail, 0);
                    result_sign = 1;
                }
            }
            else if(sign1 == 1 && sign2 == -1)
            {
                //+A - (-B) = A + B, sign +
                if (addition(tail1, tail2, &result_head, &result_tail) == FAILURE)
                {
                    printf("ERROR: Addition failed\n");
                    return FAILURE;
                }
                result_sign = 1;
            }
            else if(sign1 == -1 && sign2 == 1)
            {
                /* -A - (+B) = -(A + B) */
                if (addition(tail1, tail2, &result_head, &result_tail) == FAILURE)
                {
                    printf("ERROR: Addition failed\n");
                    return FAILURE;
                }
                result_sign = -1;
            }
            else
            {
                //-A - (-B) = B - A
                comparison = compare_lists(head1, head2);

                if(comparison > 0)
                {
                    /* A > B → B - A → negative */

                    if (subtraction(head1, tail1, head2, tail2, &result_head, &result_tail) == FAILURE)
                    {
                        printf("ERROR: Subtraction failed\n");
                        return FAILURE;
                    }
                    result_sign = -1;
                }
                else if (comparison < 0)
                {
                    /* B > A → B - A → positive */

                    if (subtraction(head2, tail2, head1, tail1, &result_head, &result_tail) == FAILURE)
                    {
                        printf("ERROR: Subtraction failed\n");
                        return FAILURE;
                    }
                    result_sign = 1;
                }
                else
                {
                    /* Equal magnitudes */
                    dl_insert_first(&result_head, &result_tail, 0);
                    result_sign = 1;
                }
                
            }
            break;
        }

        case '*':
           if (multiplication(head1, tail1, head2, tail2, &result_head, &result_tail) == FAILURE)
            {
                printf("ERROR: Multiplication failed\n");
                return FAILURE;
            }

            result_sign = sign1 * sign2;
            break;

        case '/':
            /* division will be implemented here */
            break;

        default:
            printf("ERROR: Invalid operator\n");
            return FAILURE;
    }

    printf("Result: ");
    if (result_sign == -1)
        printf("-");

    print_list(result_head);

    return SUCCESS;
}
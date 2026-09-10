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

    printf("First Number : ");
    print_list(head1);

    printf("Second Number : ");
    print_list(head2);

    printf("Sign 1: %d\n", sign1);
    printf("Sign 2: %d\n", sign2);

    /* Select operation */
    switch (argv[2][0])
    {
        case '+':
            if (addition(tail1, tail2, &result_head, &result_tail) == FAILURE)
            {
                printf("ERROR: Addition failed\n");
                return FAILURE;
            }
            break;

        case '-':
            /* subtraction will be implemented here */
            break;

        case '*':
            /* multiplication will be implemented here */
            break;

        case '/':
            /* division will be implemented here */
            break;

        default:
            printf("ERROR: Invalid operator\n");
            return FAILURE;
    }

    printf("Result: ");
    print_list(result_head);

    return SUCCESS;
}
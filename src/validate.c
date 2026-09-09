#include "validate.h"
#include <stdio.h>

int validate_operand(char *operand)
{
    int i = 0;

    if(operand == NULL || operand[0] == '\0')
    {
        return FAILURE;
    }

    if(operand[0] == '-')
    {
        i = 1;
        if(operand[1] == '\0')
        {
            return FAILURE;
        }
    }

    while(operand[i] != '\0')
    {
        if(operand[i] < '0' || operand[i] > '9')
        {
            return FAILURE;
        }
        i++;
    }
    return SUCCESS;
}

int validate_operator(char *operator)
{
    if(operator == NULL)
    {
        return FAILURE;
    }

    if(operator[0] == '\0' || operator[1] != '\0')
    {
        return FAILURE;
    }

    if(operator[0] == '+' ||
        operator[0] == '-' ||
        operator[0] == '*' ||
        operator[0] == '/')
        {
            return SUCCESS;
        }
    
    return FAILURE;
}

int validate_divisor(char *divisor)
{
    int i = 0;

    if (divisor == NULL)
    {
        return FAILURE;
    }

    /* Skip negative sign */
    if (divisor[0] == '-')
    {
        i = 1;
    }

    /* Check whether all digits are zero */
    while (divisor[i] != '\0')
    {
        if (divisor[i] != '0')
        {
            return SUCCESS;
        }

        i++;
    }

    return FAILURE;
}

int validate_arguments(int argc, char *argv[])
{
    /* Check number of arguments */
    if (argc != 4)
    {
        printf("ERROR: Invalid number of arguments\n");
        return FAILURE;
    }

    /* Validate first operand */
    if (validate_operand(argv[1]) == FAILURE)
    {
        printf("ERROR: Invalid first operand\n");
        return FAILURE;
    }

    /* Validate operator */
    if (validate_operator(argv[2]) == FAILURE)
    {
        printf("ERROR: Invalid operator\n");
        return FAILURE;
    }

    /* Validate second operand */
    if (validate_operand(argv[3]) == FAILURE)
    {
        printf("ERROR: Invalid second operand\n");
        return FAILURE;
    }

    /* Check division by zero */
    if (argv[2][0] == '/')
    {
        if (validate_divisor(argv[3]) == FAILURE)
        {
            printf("ERROR: Division by zero\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}

#include "dll.h"
#include "validate.h"

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

    if(validate_arguments(argc, argv) == FAILURE)
    {
        return FAILURE;
    }


    return SUCCESS;
}
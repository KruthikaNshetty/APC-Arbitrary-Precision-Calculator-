#include <stdio.h>
#include "apc.h"

void print_list(APC *head)
{
    if (head == NULL)//check if list is empty or not
    {
        printf("INFO : List is empty\n");
    }
    else
    {
        while (head)//printing node
        {
            printf("%d", head->data);
            head = head->next;
        }
        printf("\n");
    }
}

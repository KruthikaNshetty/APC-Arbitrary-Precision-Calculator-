#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

int delete_list(APC **head, APC **tail)
{
    if (*head ==NULL)//check node is present or not
    {
        return FAILURE;
    }
    APC *temp = *head;
    while (temp!= NULL) //traverse till null
    {
       *head = temp->next; // move head to next node
        free(temp);         // free current node
        temp = *head;      // update temp
    }
    *tail = NULL;
    return SUCCESS;
}


#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

int insert_last(APC **head, APC **tail, int data)
{
    APC *new = malloc(sizeof(APC));
    if (new == NULL)//checking new node created or not
        return FAILURE;
   //updating new node data and links
    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)//checking list is empty
    {
        //updating head and tail
        *head = new;
        *tail = new;
    }
    else
    {
        new->prev = *tail;// updating new node previous link
        (*tail)->next = new;// updating last node next link
        *tail = new; //updating tail with new node address
    }
    return SUCCESS;
}

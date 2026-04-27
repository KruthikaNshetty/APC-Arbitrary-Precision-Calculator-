#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

int insert_first(APC **head, APC **tail, int data)
{
    APC *new = malloc(sizeof(APC));
    if (new == NULL)//checking new node created or not
        return FAILURE;

    //updating new node data and links
    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)
    {
       //updating head and tail
        *head = new;
        *tail = new;
    }
    else
    {
       //list is not empty
        new->next=*head; //updating new node next link
        (*head)->prev=new; //first node previous link
        *head=new; //updating head
    }
    return SUCCESS;
}

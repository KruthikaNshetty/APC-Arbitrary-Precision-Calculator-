#include <stdio.h> 
#ifndef APC_H
#define APC_H

#define SUCCESS 0
#define FAILURE -1

// Node structure for APC linked list
typedef struct node
{
    int data;
    struct node *prev;  // previous node
    struct node *next;  // next node
} APC;

int insert_last(APC **head, APC **tail, int data);   // function declaration insert at end
int insert_first(APC **head, APC **tail, int data);  // function declaration insert at first
int delete_list(APC **head, APC **tail);             //function declaration delete whole list
void print_list(APC *head);                          // function declaration print list

void add(APC *tail1,APC *tail2,APC **rhead,APC **rtail);  // function declaration add two numbers
int compare_list(APC *head1,APC *head2);                  // function declaration compare two numbers
void sub(APC *tail1,APC *tail2,APC **rhead,APC **rtail);  // function declaration subtract numbers
void multiplication(APC *tail1,APC *tail2,APC **rhead,APC **rtail); //function declaration  multiply
void division(APC **tail1,APC **head1,APC *tail2,APC *head2,
              APC **rhead,APC **rtail,APC **counthead,APC **counttail); //function declaration  divide
void add_one(APC **counthead,APC **counttail);           //function declaration  add 1
void remove_zero(APC **head);                            // function declaration remove leading zeros

#endif

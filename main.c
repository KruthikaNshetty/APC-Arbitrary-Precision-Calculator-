
/*

Name: Kruthika N Shetty

Project Name: Arbitrary Precision Calculator (APC)

Project Description:

This project is an Arbitrary Precision Calculator written in C. It can perform operations on very large numbers that
normal data types cannot handle. Each number is stored in a doubly linked list, with each node holding a single digit,
so the calculator can work with numbers of any size. It supports addition, subtraction, multiplication, and division,
and can handle both positive and negative numbers. Leading zeros are removed automatically, and the result is displayed 
correctly even for very large numbers. This project also shows how linked lists can be used to manage data dynamically in memory.

*/

#include <stdio.h>
#include "apc.h"
#include <string.h>
int main(int argc,char *argv[])
{
  
    APC *rhead=NULL;   //Head pointer for the result linked list
    APC *rtail=NULL;  // Tail pointer for result linked list
    APC *head1=NULL;  // Head pointer for operand 1 linked list
    APC *head2=NULL; // Head pointer for operand 2 linked list
    APC *tail1=NULL; // Tail pointer for operand 1 linked list
    APC *tail2=NULL; // Tail pointer for operand 2 linked list

    APC *counthead=NULL;  
    APC *counttail=NULL;
    insert_first(&counthead,&counttail,0); //Initializing quotient list with 0
    
    if(argc!=4)//condition to check the arguments
    {
        printf("ERROR: Invalid arguments\n");
        printf("Usage: ./a.out [operand 1] [operater] [operand 2]\n");
        return 0;
    }
     int i=0,j=0,data,flag1=0,flag2=0;
     if(argv[1][i]=='+' || argv[1][i]=='-')// Check sign of operand 1
     {
        flag1=1;// Set flag if operand 1 has sign
        i++;   // Skip sign character
     }
    while(argv[1][i]!='\0') //Traverse operand 1 string
    {
        if(argv[1][i]>='0' && argv[1][i]<='9')// condition to check digit or not
        {
            data=argv[1][i]-'0';// Convert character to integer
            insert_last(&head1,&tail1,data);  // Insert digit into linked list
        }
        else
        {
           printf("Invalid Operand1\n") ; // Invalid character in operand 1
           return 0;
        }
        i++;  //Move to next character
    }
    remove_zero(&head1); //Remove leading zeros from operand 1

    if(argv[3][j]=='+' || argv[3][j]=='-') //Check sign of operand 2
     {
        flag2=1; //Set flag if operand 2 has sign 
        j++;
     }
    while(argv[3][j]!='\0')  //Traverse operand 2 string
    {
        if(argv[3][j]>='0' && argv[3][j]<='9')//condition to check digit or not
        {
            data=argv[3][j]-'0'; //Convert character to integer.
            insert_last(&head2,&tail2,data); //Insert digit into linked list
        }
        else
        {
           printf("Invalid Operand2\n") ;
           return 0;
        }
        j++;
    }
    remove_zero(&head2);//Remove leading zeros from operand 2
    if(strlen(argv[2])!=1)  //conditon to check operator must be single character
    {
        printf("Invalid operator\n");
        return 0;
    }
    printf("Result: ");

    switch(argv[2][0])
    {
        case '+' :
        if(flag1==flag2) //If both operands have same sign
        add(tail1,tail2,&rhead,&rtail);//call add function
        else
        {
            if(compare_list(head1,head2)==0)//If both values equal
            {
                printf("0\n");
                return 0;
            }
            else if(compare_list(head1,head2)==-1) //Operand2 > Operand1
            {
                sub(tail2,tail1,&rhead,&rtail);//Subtract operand1 from operand2
                remove_zero(&rhead);
                if(flag2==1)
                printf("-");
            }
        else
        {
            sub(tail1,tail2,&rhead,&rtail);//Subtract operand2 from operand1
            remove_zero(&rhead);
            if(flag1==1)
            printf("-");
        }
        }
        if(flag1==1 && flag2==1 && rhead->data!=0) //condition to check both operands negative
        printf("-");
        print_list(rhead);
        break;

        case '-':     //Subtraction case
        if(flag1==0 && flag2==1)
        add(tail1,tail2,&rhead,&rtail);
        else if(flag1==1 && flag2==0)
        {
            add(tail1,tail2,&rhead,&rtail);
            printf("-");
        }
        else
        {
            if(compare_list(head1,head2)==0) //if both operands have equal values
            {
                printf("0\n");
                return 0;
            }
            else if(compare_list(head1,head2)==-1) //Operand2 > Operand1
            {
                sub(tail2,tail1,&rhead,&rtail);
                remove_zero(&rhead);
                if(flag1==0)
                printf("-");
            }
            else
            {
                sub(tail1,tail2,&rhead,&rtail);
                remove_zero(&rhead);
                if(flag1==1)
                printf("-");
            }
        }
        print_list(rhead);
        break;

        case 'x':
        case 'X':
        multiplication(tail1,tail2,&rhead,&rtail); //Multiply operands
        remove_zero(&rhead);
        if((flag1==1 && flag2==0 && rhead->data!=0))
        printf("-");
        else if(flag1==0 && flag2==1 && rhead->data!=0)
        printf("-");
        print_list(rhead);  //Print multiplication result
        break;

        case '/': //division case
        if(head2->data==0)
        {
           printf("Error: Cannot divide by zero\n");
            return 0;
        }
        division(&tail1,&head1,tail2,head2,&rhead,&rtail,&counthead,&counttail);
        if(flag1==1 && flag2==0 && counthead->data!=0)
        printf("-");
        else if(flag1==0 && flag2==1 && counthead->data!=0)
        printf("-");
        print_list(counthead);//Print quotient
        
        break;

        default: //Print quotien
        printf("\nINVALID OPERATOR\n");
    }
    return 0;

}
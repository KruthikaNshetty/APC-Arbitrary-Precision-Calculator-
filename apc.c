#include<stdio.h>        
#include "apc.h"         
#include <stdlib.h>      
#include<string.h>       

int compare_list(APC *head1,APC *head2) //function to compare two numbers as lists
{
    int len1=0, len2=0;        
    APC *temp1=head1;          //temp pointer for list1
    APC *temp2=head2;          //temp pointer for list2

    while(temp1!=NULL)         //count nodes in list1
    {
        len1++;
        temp1=temp1->next; // move temp to next node
    }
    while(temp2!=NULL)         // count nodes in list2
    {
        len2++;
        temp2=temp2->next;
    }
    if(len1<len2)              // if list1 smaller
    {
        return -1;
    }
    else if(len1==len2)        // if lengths are equal
    {
        while(head1!=NULL && head2!=NULL) // compare digit by digit
        {
            if(head1->data < head2->data)
            {
                return -1;      //return -1 if list1 is smaller
            }
            else if(head1->data > head2->data)
                return 1;       // list1 bigger

            head1=head1->next;  // move to next node
            head2=head2->next;
        } 
        return 0;              
    }
    else
        return 1;            
}

void add(APC *tail1,APC *tail2,APC **rhead,APC **rtail) //function to add two numbers
{
    APC *temp1=tail1;          //start from end of list1
    APC *temp2=tail2;          // start from end of list2
    int res=0,carry=0;         // store result and carry

    while(temp1!=NULL || temp2!=NULL) // traverse loop till both list null
    {
        if(temp1!=NULL && temp2!=NULL)
        {
            res=temp1->data + temp2->data + carry; // add digits + carry
            temp1=temp1->prev;
            temp2=temp2->prev;
        }
        else if(temp1!=NULL)   // if only list1 present
        {
            res=temp1->data + carry;
            temp1=temp1->prev;
        }
        else if(temp2!=NULL)   // only list2 present
        {
            res=temp2->data + carry;
            temp2=temp2->prev;
        }

        if(res>9)              //if digit >9
        {
            res=res%10;        
            carry=1;           // carry 1
        }
        else
            carry=0;

        insert_first(rhead,rtail,res); //insert at front
    }
    if(carry==1)                //if carry remains
        insert_first(rhead,rtail,carry);
}

void sub(APC *tail1,APC *tail2,APC **rhead,APC **rtail) // subtract numbers
{
    APC *temp1=tail1;         // pointer for list1
    APC *temp2=tail2;         // pointer for list2
    int res=0,flag=0,d1,d2;   // result, borrow flag, digits

    while(temp1!=NULL || temp2!=NULL) // loop digits
    {
        d1=0,d2=0;             // reset digits
        if(temp1!=NULL)
            d1=temp1->data;
        if(temp2!=NULL)
            d2=temp2->data;

        if(flag==1)            // if previous borrow
            d1=d1-1;

        if(temp1!=NULL && temp2!=NULL)
        {
            if(d1 < d2)        // need borrow
            {
                res=d1+10-d2;
                flag=1;
            }
            else
            {
                res=d1-d2;
                flag=0;
            }
            temp1=temp1->prev;
            temp2=temp2->prev;
        }
        else if(temp1!=NULL && temp2==NULL) // only list1 left
        {
            res=d1;
            if(res<0)
            {
                res=9;
                flag=1;
            }
            else
                flag=0;
            temp1=temp1->prev;
        }
        insert_first(rhead,rtail,res); // insert result digit
    }
}   

void multiplication(APC *tail1,APC *tail2,APC **rhead,APC **rtail) // function to multiply
{
    APC *temp2=tail2;           
    APC *restail1=NULL;         
    APC *restail2=NULL;         
    APC *reshead1=NULL;         
    APC *reshead2=NULL;         
    int res=0;    //result digit 
    int count=0; // position counter
    int carry;  // carry

    while(temp2!=NULL) // travrse loop through digits of second number
    {
        APC *temp1=tail1; // pointer for first number
        carry=0;

        if(count!=0)    // shift for position
        {
            for(int i=0;i<count;i++)
                insert_first(&reshead2,&restail2,0); // add zeros
        }

        while(temp1!=NULL)
        {
            res=temp1->data*temp2->data+carry; 
            if(res>9)
            {
                carry=res/10;
                res=res%10;
            }
            else
                carry=0;

            if(count==0)
                insert_first(&reshead1,&restail1,res); //first iteration
            else
                insert_first(&reshead2,&restail2,res); //later iterations

            temp1=temp1->prev;
        }

        if(carry!=0) //insert remaining carry
        {
            if(count==0)
                insert_first(&reshead1,&restail1,carry);
            else
                insert_first(&reshead2,&restail2,carry);
        }

        count++; //increment  count

        if(count>=2)  //add intermediate results
        {
            add(restail1,restail2,rhead,rtail);
            delete_list(&reshead1,&restail1); // delete old res
            delete_list(&reshead2,&restail2);
            reshead1=*rhead;      
            restail1=*rtail;
            *rhead=NULL;
            *rtail=NULL;
        }

        temp2=temp2->prev; // move left in second number
    }

    *rhead=reshead1;             
    *rtail=restail1;    
}

void division(APC **tail1,APC **head1,APC *tail2,APC *head2, APC **rhead, APC **rtail, APC **counthead, APC **counttail)
{
    while(compare_list(*head1,head2)==1 || compare_list(*head1,head2)==0) // while loop if the dividend >= divisor
    {
        add_one(counthead,counttail); // increment quotient
        sub(*tail1,tail2,rhead,rtail); // subtract divisor
        delete_list(head1,tail1);     // delete old dividend
        *tail1=*rtail;  // update tail
        *head1=*rhead;   //update head
        *rhead=NULL;
        *rtail=NULL;
        remove_zero(head1);           
    }
}

void remove_zero(APC **head) 
{
    while(*head && (*head)->data==0 && (*head)->next!=NULL)
    {
        APC *temp=*head;
        *head=temp->next; // move head forward
        (*head)->prev=NULL;
        free(temp);   // free old node
    }
}

void add_one(APC **counthead,APC **counttail) // increment number by 1
{
    APC *temp=*counttail;       // start from last
    int carry=1;                // initial carry is 1
    while(temp!=NULL && carry==1)
    {
        temp->data=temp->data+carry; // add carry
        if(temp->data>9)
        {
            temp->data=0;
            carry=1;
        }
        else
            carry=0;

        temp=temp->prev;   // move left of node
    }
    if(carry==1)
        insert_first(counthead,counttail,carry); // add new digit if needed
}

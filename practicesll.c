#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int data;
    struct node *next;
};

int main()
{
    struct node *head = NULL;
    struct node *tail = NULL;
    int data = 0;
    char choice;

    do
    {
        printf("enter node data");
        scanf("&d",&data);
        struct node *newnode = (struct node*)malloc(sizeof(struct node));
        newnode->data=data;
        if(head==NULL)
        {
            newnode->data=data;
            head=newnode;
            tail=newnode;
        }

        newnode->next= head;
        head = newnode;
        printf("do you want to continue ?(y/n)");
        scanf("%c",&choice);
    } while (choice!='y');
    
    return 0;
}
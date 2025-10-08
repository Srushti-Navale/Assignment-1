#include <stdio.h>
#include <stdlib.h>
//stack operations using linked list
// function declaration
void push(struct node **ftop, char cdata);
void pop(struct node **ftop, char *ddata);
void displaytop(struct node *ftop);
int isempty(struct node *ftop);

// struct node for char datatype
struct node 
{
    char data;
    struct node *next;
};

int main ()
{
    struct node *top=NULL;
    char data;
    char ddata;
    int choice=0;
    do
    {
        printf("\n\nstack menu\n");
        printf("1.push data.\n");
        printf("2.pop data.\n");
        printf("3.display top of the stack.\n");
        printf("4.check stack is empty or not.\n");
        printf("5.exit\n");
        printf("enter your choice:");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1:
                printf("enter the data to push into stack :");
                scanf(" %c", &data);
                push(&top,data);
                break;
            case 2:
                pop(&top,&ddata);
                break;
            case 3:
                displaytop(top);
                break;
            case 4:
                if(isempty(top) == 0)
                {
                    printf("stack is not empty\n");
                }
                else
                {
                    printf("stack is empty\n");
                }
                break;
            case 5:
                printf("exiting");
                break;
            
        }
        
    }while(choice != 5);
    return 0;
}

void push(struct node **ftop, char cdata)
{
    struct node *newnode=(struct node *)malloc(sizeof(struct node));
    newnode->data = cdata;
    newnode->next= *ftop;
    *ftop = newnode;
}

void pop(struct node **ftop, char *ddata)
{
    if(*ftop == NULL)
    {
        printf("stack is empty\n");
        return;
    }else{
        struct node *temp = *ftop;
        *ddata = temp->data;
        *ftop= temp->next;
        printf("poped data is %c\n",*ddata);
        free(temp);
    }
}

void displaytop(struct node *ftop)
{
    printf("top of stack is : %c\n",ftop->data);
}

int isempty(struct node *ftop)
{
    return ftop == NULL;
}


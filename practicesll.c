#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int data;
    struct node *next;
};

void traverse(struct node **head);
void insertathead(struct node **head,struct node **tail,int data);
void insertatend(struct node **head ,struct node **tail,int data);
void insertatposition(struct node **head,struct node **tail,int data,int position);
void deleteathead(struct node **head,struct node **tail,int *ddata);
void deleteatend(struct node **head,struct node **tail,int *ddata);
void deleteatposition(struct node **head,struct node **tail,int position,int *ddata);


int main()
{
    struct node *head = NULL;
    struct node *tail = NULL;
    int data = 0;
    char choice='n';
    int position=0;

    do
    {
        printf("enter node data");
        scanf("%d",&data);
        struct node *newnode = (struct node*)malloc(sizeof(struct node));
        newnode->data=data;
        if(head==NULL)
        {
            head=newnode;
            tail=newnode;
        }
        else
        {
        tail->next= newnode;
        tail = newnode;
        }
        printf("do you want to continue ?(y/n)");
        scanf("% c",&choice);
    } while (choice!='y');

    int ch=0;
    do
    {
        printf("/n menu/n");
        printf("1.display/n");
        printf("2.insert at head/n");
        printf("3.insert at end/n");
        printf("4.insert at position/n");
        printf("5.delete at head/n");
        printf("6.delete at end/n");
        printf("7.delete at position/n");
        printf("0.exit/n");
        printf("enter your choice");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                traverse(&head);
                break;
            case 2:
                printf("which data you want to enter at head of list :");
                scanf("%d",&data);
                insertathead(&head,&tail,data);
                break;
            case 3:
                printf("which data you want to enter at end of list :");
                scanf("%d",&data);
                insertatend(&head,&tail,data);
                break;
            case 4:
                printf("which data you want to enter :");
                scanf("%d",&data);
                printf("at which position you want to enter :");
                scanf("%d",&position);
                insertatposition(&head,&tail,data,position);
                break;
            case 5:
                deleteathead(&head,&tail,&data);
                printf("deleted data is %d",data);
                break;
            case 6:
                deleteatend(&head,&tail,&data);
                printf("deleted data is %d",data);
                break;
            case 7:
                printf("at which position you want to delete :");
                scanf("%d",&position);
                deleteatposition(&head,&tail,position,&data);
                printf("deleted data is %d",data);
                break;  
            case 0:
                printf("exiting...");
                break;
        }
    } while (ch!=0);
    
    return 0;
}


void traverse(struct node **head)
{
    if(head == NULL)
    {
        printf("list is empty");
    }else{
        struct node *temp=*head;
        while(temp!=NULL)
        {
            printf("%d",temp->data);
            temp=temp->next;
        }
    }
    
}


void insertathead(struct node **head,struct node **tail,int data)
{
    struct node *newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    if(*head == NULL)
   {
      *head=newnode;
      *tail = newnode;
   }
   else
   {
     newnode->next=*head;
     *head=newnode;
   }
   traverse(&head);
}

void insertatend(struct node **head ,struct node **tail,int data)
{
    struct node *newnode=(struct node *)malloc(sizeof(struct node));
    newnode->data=data;

    if(*head == NULL)
   {
      *head=newnode;
      *tail = newnode;
   }
   else
   {
      newnode->next=NULL;
      (*tail)->next=newnode;
      *tail=newnode;
   }
    traverse(&head);
}

void insertatposition(struct node **head,struct node **tail,int data,int position)
{
    struct node *newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=data;

    if(position==0)
    {
        insertathead(&head,&tail,data);
    }
    else
    {
        struct node *temp = *head;
        for(int i=0;i<position-1;i++)
        {
            temp=temp->next;
            if(temp==NULL)
            {
                printf("position is invalid");
                i=position+1;
            }
        }

        if(temp!=NULL)
        {
            newnode->next=temp->next;
            temp->next=newnode;
        }
    }
    traverse(&head);
}

void deleteathead(struct node **head,struct node **tail,int *ddata)
{
    if(*head == NULL)
    {
        printf("list is empty");
    }
    else
    {
        struct node *temp = *head;

        *head=(*head)->next;
        *ddata = temp->data;
        free(temp);
    }
    traverse(&head);
}

void deleteatend(struct node **head,struct node **tail,int *ddata)
{
    if(*head == NULL)
    {
        printf("list is empty");
    }
    else
    {
        struct node *temp = *head;
        if((*head)->next == NULL)
        {
            free(*head);
            *head = NULL;
            *tail = NULL;
        }
        else
        {
            while(temp->next != *tail)
            {
                temp=temp->next;
            }
            *ddata = (*tail)->data;
            free(*tail);
            temp->next=NULL;
            *tail=temp;
        }
    }
    traverse(&head);
}

void deleteatposition(struct node **head,struct node **tail,int position,int *ddata)
{
    if(*head == NULL)
    {
        printf("list is empty");
    }
    else
    {
        if(position==0)
        {
            deleteathead(&head,&tail,&ddata);
        }
        else
        {
            struct node *temp = *head;
            for(int i=0;i<position-1;i++)
            {
                temp=temp->next;
                if(temp==NULL)
                {
                    printf("position is invalid");
                    i=position+1;
                }
            }

            if(temp!=NULL && temp->next != NULL)
            {
                struct node *todelete = temp->next;
                temp->next = temp->next->next;
                if(todelete == *tail)
                {
                    *tail = temp;
                }
                *ddata = todelete->data;
                free(todelete);
            }
        }
    }
    traverse(&head);
}

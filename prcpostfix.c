#include<stdio.h>
#include<stdlib.h>

struct stackop
{
  char data;
  struct stackop *next;
};

void push(struct stackop **ftop , char data)
{
    struct stackop *newnode = (struct stackop *)malloc(sizeof(struct stackop));
    newnode->data=data;
    newnode->next=NULL;
    if(ftop == NULL)
    {
      *ftop=newnode;
    }
    else
    {
        newnode->next = *ftop;
        *ftop = newnode;
    }
}

void pop(struct stackop **ftop , char *ddata)
{
    struct stackop *temp = *ftop;
    if(*ftop == NULL)
    {
        printf("memory full");
    }
    else
    {
    *ddata = (*ftop)->data;
    *ftop=(*ftop)->next;
    free(temp);
    }
    
}

int isemptystackop(struct stackop *ftop)
{
    return (ftop == NULL);
}
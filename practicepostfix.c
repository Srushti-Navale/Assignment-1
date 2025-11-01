#include <stdio.h>
#include <stdlib.h>

struct stackop
{
    char data;
    struct stackop *next;
};


void pushop(struct stackop **head ,char val)
{
    struct stackop *newNode = (struct stackop *)malloc(sizeof(struct stackop));
    newNode->data = val;
    newNode->next = *head;
    *head = newNode;
}

char popop(struct stackop **head)
{
    if (*head == NULL) 
    {
        printf("Stack underflow\n");
        return '\0';
    }
    struct stackop *temp = *head;
    char poppedValue = temp->data;
    *head = (*head)->next;
    free(temp);
    return poppedValue;
}

char peekop(struct stackop *head)
{
    if (head == NULL)
   {
        printf("Stack is empty\n");
        return '\0';
    }
    return head->data;
}

int isEmptyop(struct stackop *head)
{
    return head == NULL;
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}


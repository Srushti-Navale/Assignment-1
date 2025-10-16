#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Doubly Linked List Stack Node for char/int stack
struct dllNode
{
    struct dllNode *prev;
    int data;  // Can store char or int (ASCII or value)
    struct dllNode *next;
};

// String stack used in prefix conversion
struct StringNode
{
    char str[100];
    struct StringNode *next;
};

// Stack operations for dllNode
int push(struct dllNode **head, struct dllNode **last, int *data);
int pop(struct dllNode **head, struct dllNode **last, int *deletedData);
int top(struct dllNode **head, struct dllNode **last, int *topData);
int isEmpty(struct dllNode *last);

// String stack operations
void pushStr(struct StringNode **top, char *str);
void popStr(struct StringNode **top, char *outStr);
void processOperator(struct StringNode **operandStack, char op);

// Expression utilities
int menu(void);
int precedence(char op);
void infixToPostfix(char infix[], char postfix[]);
void infixToPrefix(char infix[], char prefix[]);
int evaluatePostfix(char postfix[]);

// --- MAIN FUNCTION ---
int main()
{
    int ch = 0;
    char infix[100], postfix[100], prefix[100];
    int result;

    do
    {
        ch = menu();

        switch (ch)
        {
            case 1:
                printf("\nEnter infix expression: ");
                scanf("%s", infix);
                infixToPostfix(infix, postfix);
                printf("Postfix expression: %s\n", postfix);
                break;

            case 2:
                printf("\nEnter infix expression: ");
                scanf("%s", infix);
                infixToPrefix(infix, prefix);
                printf("Prefix expression: %s\n", prefix);
                break;

            case 3:
                printf("\nEnter postfix expression: ");
                scanf("%s", postfix);
                result = evaluatePostfix(postfix);
                printf("Result of postfix evaluation: %d\n", result);
                break;

            case 0:
                printf("\nThank you, visit again!\n");
                break;

            default:
                printf("\nInvalid choice, try again!\n");
                break;
        }
    } while (ch != 0);

    return 0;
}

// Menu
int menu(void)
{
    int choice = 0;
    printf("\n\nStack ADT Application Menu");
    printf("\n1. Infix to Postfix conversion");
    printf("\n2. Infix to Prefix conversion");
    printf("\n3. Evaluate Postfix expression");
    printf("\n0. Exit");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    return choice;
}

// Precedence
int precedence(char op)
{
    switch (op)
    {
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

// Doubly linked list stack functions

int push(struct dllNode **head, struct dllNode **last, int *data)
{
    struct dllNode *newNode = (struct dllNode *)malloc(sizeof(struct dllNode));
    if (!newNode) return 1;

    newNode->data = *data;
    newNode->prev = *last;
    newNode->next = NULL;

    if (*last)
        (*last)->next = newNode;
    else
        *head = newNode;

    *last = newNode;
    return 0;
}

int pop(struct dllNode **head, struct dllNode **last, int *deletedData)
{
    if (*last == NULL)
        return 1;

    struct dllNode *temp = *last;
    *deletedData = temp->data;

    *last = temp->prev;
    if (*last)
        (*last)->next = NULL;
    else
        *head = NULL;

    free(temp);
    return 0;
}

int top(struct dllNode **head, struct dllNode **last, int *topData)
{
    if (*last == NULL)
        return 1;

    *topData = (*last)->data;
    return 0;
}

int isEmpty(struct dllNode *last)
{
    return (last == NULL);
}

// String Stack (used for prefix conversion)
void pushStr(struct StringNode **top, char *str)
{
    struct StringNode *newNode = (struct StringNode *)malloc(sizeof(struct StringNode));
    strcpy(newNode->str, str);
    newNode->next = *top;
    *top = newNode;
}

void popStr(struct StringNode **top, char *outStr)
{
    if (*top == NULL) return;

    struct StringNode *temp = *top;
    strcpy(outStr, temp->str);
    *top = temp->next;
    free(temp);
}

void processOperator(struct StringNode **operandStack, char op)
{
    char op1[100], op2[100], temp[200];
    popStr(operandStack, op2);
    popStr(operandStack, op1);
    sprintf(temp, "%c%s%s", op, op1, op2);
    pushStr(operandStack, temp);
}

// Infix to Postfix
void infixToPostfix(char infix[], char postfix[])
{
    struct dllNode *head = NULL, *last = NULL;
    int i = 0, k = 0;
    char symbol;
    int temp;

    while ((symbol = infix[i++]) != '\0')
    {
        if (isalnum(symbol))
        {
            postfix[k++] = symbol;
        }
        else if (symbol == '(')
        {
            int c = (int)symbol;
            push(&head, &last, &c);
        }
        else if (symbol == ')')
        {
            while (!isEmpty(last))
            {
                pop(&head, &last, &temp);
                if ((char)temp == '(')
                    break;
                postfix[k++] = (char)temp;
            }
        }
        else
        {
            while (!isEmpty(last))
            {
                top(&head, &last, &temp);
                if (precedence((char)temp) < precedence(symbol))
                    break;

                pop(&head, &last, &temp);
                postfix[k++] = (char)temp;
            }
            int c = (int)symbol;
            push(&head, &last, &c);
        }
    }

    while (!isEmpty(last))
    {
        pop(&head, &last, &temp);
        postfix[k++] = (char)temp;
    }

    postfix[k] = '\0';
}

// Infix to Prefix
void infixToPrefix(char infix[], char prefix[])
{
    struct dllNode *opHead = NULL, *opLast = NULL;
    struct StringNode *operandStack = NULL;

    int i = 0;
    char symbol;

    while ((symbol = infix[i++]) != '\0')
    {
        if (isalnum(symbol))
        {
            char operand[2] = {symbol, '\0'};
            pushStr(&operandStack, operand);
        }
        else if (symbol == '(')
        {
            int c = (int)symbol;
            push(&opHead, &opLast, &c);
        }
        else if (symbol == ')')
        {
            int op;
            while (!isEmpty(opLast))
            {
                pop(&opHead, &opLast, &op);
                if ((char)op == '(')
                    break;
                processOperator(&operandStack, (char)op);
            }
        }
        else
        {
            int opTop;
            while (!isEmpty(opLast))
            {
                top(&opHead, &opLast, &opTop);
                if (precedence((char)opTop) < precedence(symbol))
                    break;

                pop(&opHead, &opLast, &opTop);
                processOperator(&operandStack, (char)opTop);
            }
            int c = (int)symbol;
            push(&opHead, &opLast, &c);
        }
    }

    while (!isEmpty(opLast))
    {
        int op;
        pop(&opHead, &opLast, &op);
        processOperator(&operandStack, (char)op);
    }

    popStr(&operandStack, prefix);
}

// Evaluate Postfix
int evaluatePostfix(char postfix[])
{
    struct dllNode *head = NULL, *last = NULL;
    int i = 0;
    char symbol;

    while ((symbol = postfix[i++]) != '\0')
    {
        if (isdigit(symbol))
        {
            int num = symbol - '0';
            push(&head, &last, &num);
        }
        else
        {
            int op2, op1;
            pop(&head, &last, &op2);
            pop(&head, &last, &op1);

            int result;
            switch (symbol)
            {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
                default:
                    printf("Invalid operator %c\n", symbol);
                    exit(1);
            }
            push(&head, &last, &result);
        }
    }

    int finalResult;
    pop(&head, &last, &finalResult);
    return finalResult;
}

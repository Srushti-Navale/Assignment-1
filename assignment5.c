#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node
{
    char data;
    struct Node *next;
};

// For string operands stack
struct StringNode
{
    char str[100];
    struct StringNode *next;
};

// Function Declarations
int menu(void);
int push(struct Node **ftop, char cdata);
int pop(struct Node **ftop, char *pdata);
int isEmpty(struct Node *top);
int precedence(char op);

void pushStr(struct StringNode **top, char *str);
void popStr(struct StringNode **top, char *outStr);

void infixToPostfix(char infix[], char postfix[]);
void infixToPrefix(char infix[], char prefix[]);
int evaluatePostfix(char postfix[]);

void processOperator(struct StringNode **operandStack, char op);

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

// Stack (char) operations
int push(struct Node **ftop, char cdata)
{
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->data = cdata;
    newnode->next = *ftop;
    *ftop = newnode;
    return 0;
}

int pop(struct Node **ftop, char *pdata)
{
    if (*ftop == NULL)
        return 1;

    struct Node *temp = *ftop;
    *pdata = temp->data;
    *ftop = temp->next;
    free(temp);
    return 0;
}

int isEmpty(struct Node *top)
{
    return (top == NULL);
}

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

// String stack operations
void pushStr(struct StringNode **top, char *str)
{
    struct StringNode *newNode = (struct StringNode *)malloc(sizeof(struct StringNode));
    strcpy(newNode->str, str);
    newNode->next = *top;
    *top = newNode;
}

void popStr(struct StringNode **top, char *outStr)
{
    if (*top == NULL)
        return;

    struct StringNode *temp = *top;
    strcpy(outStr, temp->str);
    *top = temp->next;
    free(temp);
}

// Combine two operands with an operator (used in prefix)
void processOperator(struct StringNode **operandStack, char op)
{
    char op1[100], op2[100], temp[200];

    popStr(operandStack, op2);
    popStr(operandStack, op1);

    sprintf(temp, "%c%s%s", op, op1, op2);
    pushStr(operandStack, temp);
}

// Infix → Postfix Conversion
void infixToPostfix(char infix[], char postfix[])
{
    struct Node *top = NULL;
    int i = 0, k = 0;
    char symbol, temp;

    while ((symbol = infix[i++]) != '\0')
    {
        if (isalnum(symbol))
        {
            postfix[k++] = symbol;
        }
        else if (symbol == '(')
        {
            push(&top, symbol);
        }
        else if (symbol == ')')
        {
            while (!isEmpty(top))
            {
                pop(&top, &temp);
                if (temp == '(')
                    break;
                postfix[k++] = temp;
            }
        }
        else // Operator
        {
            while (!isEmpty(top))
            {
                pop(&top, &temp);
                if (precedence(temp) < precedence(symbol))
                {
                    push(&top, temp);
                    break;
                }
                postfix[k++] = temp;
            }
            push(&top, symbol);
        }
    }

    while (!isEmpty(top))
    {
        pop(&top, &temp);
        postfix[k++] = temp;
    }

    postfix[k] = '\0';
}

// Infix → Prefix Conversion
void infixToPrefix(char infix[], char prefix[])
{
    struct Node *opStack = NULL;
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
            push(&opStack, symbol);
        }
        else if (symbol == ')')
        {
            char op;
            while (!isEmpty(opStack))
            {
                pop(&opStack, &op);
                if (op == '(')
                    break;
                processOperator(&operandStack, op);
            }
        }
        else // Operator
        {
            char opTop;
            while (!isEmpty(opStack))
            {
                pop(&opStack, &opTop);
                if (precedence(opTop) < precedence(symbol))
                {
                    push(&opStack, opTop);
                    break;
                }
                processOperator(&operandStack, opTop);
            }
            push(&opStack, symbol);
        }
    }

    while (!isEmpty(opStack))
    {
        char op;
        pop(&opStack, &op);
        processOperator(&operandStack, op);
    }

    popStr(&operandStack, prefix);
}

// Evaluate Postfix Expression
int evaluatePostfix(char postfix[])
{
    struct Node *top = NULL;
    int i = 0;
    char symbol;

    while ((symbol = postfix[i++]) != '\0')
    {
        if (isdigit(symbol))
        {
            push(&top, symbol - '0');
        }
        else
        {
            int op2, op1;
            char temp;

            pop(&top, &temp);
            op2 = temp;
            pop(&top, &temp);
            op1 = temp;

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
            push(&top, result);
        }
    }

    char finalResult;
    pop(&top, &finalResult);
    return finalResult;
}
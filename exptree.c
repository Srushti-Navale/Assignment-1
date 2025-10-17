#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Tree node for expression tree
struct TreeNode 
{
    char data;
    struct TreeNode *left, *right;
};

// Operator stack (DLL)
struct oprstack
{
    struct oprstack *prev;
    struct oprstack *next;
    char data;
};

// Operand stack (DLL) now stores TreeNode*
struct opndstack 
{
    struct opndstack *prev;
    struct opndstack *next;
    struct TreeNode *tree;
};

// Function prototypes
int precedence(char op);
struct TreeNode *createTreeFromInfix(char *infix);
void inorder(struct TreeNode *root);
void preorder(struct TreeNode *root);
void postorder(struct TreeNode *root);

// Operator Stack Operations
void pushopr(struct oprstack **top, char data);
char popopr(struct oprstack **top);
char topopr(struct oprstack *top);
int isEmptyopr(struct oprstack *top);

// Operand Stack Operations
void pushopnd(struct opndstack **top, struct TreeNode *node);
struct TreeNode *popopnd(struct opndstack **top);
int isEmptyopnd(struct opndstack *top);


int main() 
{
    char infix[100]={'\0'};
    int choice=0;

    printf("Enter infix expression (single characters or digits only): ");
    scanf("%s", infix);

    struct TreeNode *exprTree = createTreeFromInfix(infix);

    do
    {
        printf("\n\nmenu for traversal:\n");
        printf("1. Inorder\n");
        printf("2. Preorder\n");
        printf("3. Postorder\n");
        printf("0. Exit\n");
        printf("enter your choice :");
        scanf("%d",&choice);
    
    switch(choice)
    {
        case 1:
            printf("\nInorder Traversal:");
            inorder(exprTree);
            break;
        case 2:
            printf("\nPreorder Traversal:");
            preorder(exprTree);
            break;
        case 3:
            printf("\nPostorder Traversal:");
            postorder(exprTree);
            break;
        case 0:
            printf("exiting....");
            break;
        default:
            printf("Invalid choice.");
            break;
    }
  }while(choice!=0);
    return 0;
}

// Precedence
int precedence(char op) 
{
    switch (op) 
    {
        case '*': case '/': return 2;
        case '+': case '-': return 1;
        default: return 0;
    }
}

//  Expression Tree Builder from Infix 
struct TreeNode *createTreeFromInfix(char *infix) 
{
    struct oprstack *opStack = NULL;
    struct opndstack *operandStack = NULL;

    int i = 0;
    char ch;
    while ((ch = infix[i++]) != '\0') 
    {
        if (isspace(ch)) continue;

        if (isalnum(ch)) 
        {
            struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
            newNode->data = ch;
            newNode->left = newNode->right = NULL;
            pushopnd(&operandStack, newNode);
        } 
        else if (ch == '(') 
        {
            pushopr(&opStack, ch);
        } 
        else if (ch == ')') 
        {
            while (!isEmptyopr(opStack) && topopr(opStack) != '(') 
            {
                char op = popopr(&opStack);

                struct TreeNode *right = popopnd(&operandStack);
                struct TreeNode *left = popopnd(&operandStack);

                struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                newNode->data = op;
                newNode->left = left;
                newNode->right = right;

                pushopnd(&operandStack, newNode);
            }
            if (!isEmptyopr(opStack)) popopr(&opStack); 
        } 
        else 
        { // operator
            while (!isEmptyopr(opStack) && precedence(topopr(opStack)) >= precedence(ch)) 
            {
                char op = popopr(&opStack);

                struct TreeNode *right = popopnd(&operandStack);
                struct TreeNode *left = popopnd(&operandStack);

                struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                newNode->data = op;
                newNode->left = left;
                newNode->right = right;

                pushopnd(&operandStack, newNode);
            }
            pushopr(&opStack, ch);
        }
    }

    // Remaining operators
    while (!isEmptyopr(opStack)) 
    {
        char op = popopr(&opStack);
        struct TreeNode *right = popopnd(&operandStack);
        struct TreeNode *left = popopnd(&operandStack);

        struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        newNode->data = op;
        newNode->left = left;
        newNode->right = right;

        pushopnd(&operandStack, newNode);
    }

    return popopnd(&operandStack);  // Root of the expression tree
}

// Tree Traversals 

void inorder(struct TreeNode *root) 
{
    if (root == NULL) return;
    if (root->left) printf("(");
    inorder(root->left);
    printf("%c", root->data);
    inorder(root->right);
    if (root->right) printf(")");
}

void preorder(struct TreeNode *root) 
{
    if (root == NULL) return;
    printf("%c", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct TreeNode *root) 
{
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c", root->data);
}

//  Operator Stack Functions 

void pushopr(struct oprstack **top, char data) 
{
    struct oprstack *newNode = (struct oprstack *)malloc(sizeof(struct oprstack));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = *top;
    if (*top) (*top)->prev = newNode;
    *top = newNode;
}

char popopr(struct oprstack **top) 
{
    if (*top == NULL) {
        printf("Operator stack underflow!\n");
        exit(1);
    }

    char val = (*top)->data;
    struct oprstack *temp = *top;
    *top = (*top)->next;
    if (*top) (*top)->prev = NULL;
    free(temp);
    return val;
}

char topopr(struct oprstack *top) 
{
    if (top == NULL) 
    {
        printf("Operator stack empty!\n");
        exit(1);
    }
    return top->data;
}

int isEmptyopr(struct oprstack *top) 
{
    return top == NULL;
}

//Operand Stack Functions (TreeNode pointers

void pushopnd(struct opndstack **top, struct TreeNode *node) 
{
    struct opndstack *newNode = (struct opndstack *)malloc(sizeof(struct opndstack));
    newNode->tree = node;
    newNode->prev = NULL;
    newNode->next = *top;
    if (*top) (*top)->prev = newNode;
    *top = newNode;
}

struct TreeNode *popopnd(struct opndstack **top) 
{
    if (*top == NULL) 
    {
        printf("Operand stack underflow!\n");
        exit(1);
    }

    struct TreeNode *tree = (*top)->tree;
    struct opndstack *temp = *top;
    *top = (*top)->next;
    if (*top) (*top)->prev = NULL;
    free(temp);
    return tree;
}

int isEmptyopnd(struct opndstack *top) 
{
    return top == NULL;
}

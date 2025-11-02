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

// Operand stack (DLL) -> stores TreeNode*
struct opndstack 
{
    struct opndstack *prev;
    struct opndstack *next;
    struct TreeNode *tree;
};

// Function prototypes
struct TreeNode *createTreeFromPostfix(char *postfix);
void inorder(struct TreeNode *root);
void preorder(struct TreeNode *root);
void postorder(struct TreeNode *root);

// Operand Stack Operations
void pushopnd(struct opndstack **top, struct TreeNode *node);
struct TreeNode *popopnd(struct opndstack **top);
int isEmptyopnd(struct opndstack *top);

int main() 
{
    char postfix[100] = {'\0'};
    int choice = 0;

    printf("Enter postfix expression: ");
    scanf("%s", postfix);

    struct TreeNode *exprTree = createTreeFromPostfix(postfix);

    do
    {
        printf("\n\nMenu for traversal:\n");
        printf("1. Inorder\n");
        printf("2. Preorder\n");
        printf("3. Postorder\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nInorder: ");
                inorder(exprTree);
                break;
            case 2:
                printf("\nPreorder: ");
                preorder(exprTree);
                break;
            case 3:
                printf("\nPostorder: ");
                postorder(exprTree);
                break;
            case 0:
                printf("Exiting...");
                break;
            default:
                printf("Invalid Choice");
                break;
        }

    } while(choice != 0);

    return 0;
}

// Create Expression Tree from Postfix
struct TreeNode *createTreeFromPostfix(char *postfix) 
{
    struct opndstack *operandStack = NULL;
    int i = 0;
    char ch;

    while ((ch = postfix[i++]) != '\0') 
    {
        if (isspace(ch))
            continue;

        if (isalnum(ch))   // Operand
        {
            struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
            newNode->data = ch;
            newNode->left = newNode->right = NULL;
            pushopnd(&operandStack, newNode);
        }
        else   // Operator
        {
            struct TreeNode *right = popopnd(&operandStack);
            struct TreeNode *left = popopnd(&operandStack);

            struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
            newNode->data = ch;
            newNode->left = left;
            newNode->right = right;

            pushopnd(&operandStack, newNode);
        }
    }

    return popopnd(&operandStack);   // Final root of expression tree
}

// Traversals
void inorder(struct TreeNode *root) 
{
    if (!root) return;
    if (root->left) printf("(");
    inorder(root->left);
    printf("%c", root->data);
    inorder(root->right);
    if (root->right) printf(")");
}

void preorder(struct TreeNode *root) 
{
    if (!root) return;
    printf("%c", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct TreeNode *root) 
{
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c", root->data);
}

// Operand Stack functions
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

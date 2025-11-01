#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Tree node structure
struct treenode
{
    char data;
    struct treenode *left;
    struct treenode *right;
};

// Operand stack (stores treenode pointers)
struct opndstack
{
    struct opndstack *next;
    struct treenode *treedata;
};

// Function prototypes
void inorder(struct treenode *root);
void preorder(struct treenode *root);
void postorder(struct treenode *root);
struct treenode *createtreefrompostfix(char postfix[]);
void opndpush(struct opndstack **top , struct treenode *opnd);
struct treenode *opndpop(struct opndstack **top);
int isemptyopndstack(struct opndstack *top);

int main()
{
    char postfix[100];
    struct treenode *exprtree = NULL;
    int choice;

    printf("Enter postfix expression: ");
    scanf("%s", postfix);

    exprtree = createtreefrompostfix(postfix);

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
                inorder(exprtree);
                break;
            case 2:
                printf("\nPreorder: ");
                preorder(exprtree);
                break;
            case 3:
                printf("\nPostorder: ");
                postorder(exprtree);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);

    return 0;
}

// Create Expression Tree from Postfix
struct treenode *createtreefrompostfix(char postfix[])
{
    struct opndstack *opndstack = NULL;
    int i = 0;
    char ch;

    while((ch = postfix[i]) != '\0')
    {
        if(isalnum(ch)) // operand
        {
            struct treenode *newnode = (struct treenode *)malloc(sizeof(struct treenode));
            newnode->data = ch;
            newnode->left = newnode->right = NULL;
            opndpush(&opndstack, newnode);
        }
        else // operator
        {
            struct treenode *right = opndpop(&opndstack);
            struct treenode *left = opndpop(&opndstack);

            struct treenode *newnode = (struct treenode *)malloc(sizeof(struct treenode));
            newnode->data = ch;
            newnode->left = left;
            newnode->right = right;

            opndpush(&opndstack, newnode);
        }
        i++;
    }

    return opndpop(&opndstack);  // Return root
}

// Operand stack push
void opndpush(struct opndstack **top , struct treenode *opnd)
{
    struct opndstack *newnode = (struct opndstack *)malloc(sizeof(struct opndstack));
    newnode->treedata = opnd;
    newnode->next = *top;
    *top = newnode;
}

// Operand stack pop
struct treenode *opndpop(struct opndstack **top)
{
    if(*top == NULL)
    {
        printf("\nError: Operand stack underflow!\n");
        exit(1);
    }

    struct treenode *tempdata = (*top)->treedata;
    struct opndstack *temp = *top;
    *top = (*top)->next;
    free(temp);
    return tempdata;
}

// Check if stack empty
int isemptyopndstack(struct opndstack *top)
{
    return top == NULL;
}

// Traversals
void inorder(struct treenode *root)
{
    if(root == NULL)
        return;

    if(root->left) printf("(");
    inorder(root->left);
    printf("%c", root->data);
    inorder(root->right);
    if(root->right) printf(")");
}

void preorder(struct treenode *root)
{
    if(root == NULL)
        return;

    printf("%c", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct treenode *root)
{
    if(root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf("%c", root->data);
}


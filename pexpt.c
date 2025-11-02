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

void inorederNRC(struct treenode *root) {
    struct opndstack *stack = NULL;
     struct treenode *curr = root;

    while (curr != NULL || stack != NULL) {
        while (curr != NULL) {
            struct opndstack *newNode =(struct opndstack *)malloc(sizeof(struct opndstack));
            newNode->treedata = curr;
            newNode->next = stack;
            stack = newNode;
            curr = curr->left;
        } //curr goes to leftmost node

         struct opndstack *temp = stack;
        stack = stack->next;
        curr = temp->treedata;
        printf("%c ", curr->data);
        free(temp);

        curr = curr->right;
    }
}       

void inorderNR(struct treenode *root)
{
    struct opndstack *st = NULL;
    struct treenode *curr = root;

    while(curr != NULL || !isemptyopndstack(st))
    {
        while(curr != NULL)
        {
            opndpush(&st, curr);
            curr = curr->left;
        }
        curr = opndpop(&st);
        printf("%c", curr->data);
        curr = curr->right;
    }
}

// Preorder Non-Recursive
void preorderNR(struct treenode *root)
{
    if(root == NULL) return;

    struct opndstack *st = NULL;
    opndpush(&st, root);

    while(!isemptyopndstack(st))
    {
        root = opndpop(&st);
        printf("%c", root->data);

        if(root->right) opndpush(&st, root->right);
        if(root->left) opndpush(&st, root->left);
    }
}

// Postorder Non-Recursive (Using 2 stacks)
void postorderNR(struct treenode *root)
{
    if(root == NULL) return;

    struct opndstack *st1 = NULL, *st2 = NULL;

    opndpush(&st1, root);

    while(!isemptyopndstack(st1))
    {
        root = opndpop(&st1);
        opndpush(&st2, root);

        if(root->left) opndpush(&st1, root->left);
        if(root->right) opndpush(&st1, root->right);
    }

    while(!isemptyopndstack(st2))
    {
        root = opndpop(&st2);
        printf("%c", root->data);
    }
}

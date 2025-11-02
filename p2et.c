#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct treenode
{
    char data;
    struct treenode *right;
    struct treenode *left;
};

struct opndstack
{
    struct treenode *treedata;
    struct opndstack *next;
};

struct treenode *createexptpostfix(char postfix[]);
void pushopnd(struct opndstack **top , struct treenode *data );
struct treenode *popopnd(struct opndstack **top);
int isemptyopndstack(struct opndstack *top);
void inorder(struct treenode *root);
void preorder(struct treenode *root);
void postorder(struct treenode *root);


int main()
{
    struct treenode *exptree =NULL;
    char postfix[20];
    printf("enter postfix expresion to create exp tree :");
    scanf("%s",postfix);
    int choice=0;

    exptree = createexptpostfix(postfix);
    
    do
    {
        printf("\n\nexp tree traversal menu :\n");
        printf("1.inorder\n2.preorder\n3.postorder\n0.exit\n\n");
        printf("enter your choice :");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("\ninorder traversal :");
                inorder(exptree);
                break;
            case 2:
                printf("\npreorder traversal :");
                preorder(exptree);
                break;
            case 3:
                printf("\npostorder traversal :");
                postorder(exptree);
                break;
            case 0:
                printf("\nexiting...");
                break;
            default:
                printf("invalid choice try again"); 
                    
        }
    } while (choice !=0);
    
    return 0;
}

struct treenode *createexptpostfix(char postfix[])
{
    struct opndstack *opndstack = NULL;
    int i=0;
    char ch;

    while( (ch = postfix[i]) != '\0')
    {
       if(isalnum(ch))
       {
        //operand
        struct treenode *newnode = (struct treenode *)malloc(sizeof(struct treenode));
        newnode->data = ch ;
        newnode->right=NULL;
        newnode->left =NULL;
        pushopnd(&opndstack,newnode);

       }
       else{
        //operator
        struct treenode *right = popopnd(&opndstack);
        struct treenode *left = popopnd(&opndstack);

        struct treenode *newnode = (struct treenode *)malloc(sizeof(struct treenode));
        newnode->data=ch;
        newnode->right=right;
        newnode->left = left;

        pushopnd(&opndstack,newnode);
       }
       i++;

    }
     return popopnd(&opndstack);
}


void pushopnd(struct opndstack **top , struct treenode *data )
{
    struct opndstack *newnode = (struct opndstack*)malloc(sizeof(struct opndstack));
    newnode->treedata= data;
    newnode->next = *top;
    *top = newnode;
}

struct treenode *popopnd(struct opndstack **top)
{
    if(*top == NULL)
    {
        printf("stack empty");
        exit(1);
    }

    struct opndstack *temp = *top;
    struct treenode *tempdata = (*top)->treedata;
    *top = (*top)->next;
    free(temp);
    return tempdata;
}

int isemptyopndstack(struct opndstack *top)
{
    return (top == NULL);
}

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


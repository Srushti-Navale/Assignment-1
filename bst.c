#include<stdio.h>
#include<stdlib.h>

struct treenode 
{
    int data;
    struct treenode *left;
    struct treenode *right;
};

struct treenode* newnode(int data)
{
    struct treenode* newnode = (struct treenode*)malloc(sizeof(struct treenode));
    newnode->data = data;
    newnode->left =NULL;
    newnode->right =NULL;
    return newnode;
}

int main()
{
    int data;
    printf("enter to add in bst");
}
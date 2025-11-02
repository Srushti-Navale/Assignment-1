#include <stdio.h>
#include <stdlib.h>

struct node
{
    char data;
    struct node *right;
    struct node *left;
};

struct node *createnode(int val)
{
    struct node* newnode = (struct node*)mallloc(sizeof(struct node));
    newnode->data=val;
    newnode->right = NULL;
    newnode->left = NULL;
    return newnode;
}

struct node *insert(struct node *root,int val)
{
    if(root == NULL)
    {
        return createnode(val);
    }

    if(val<root->data)
    {
        root->left = insert(root->left,val);
    }
    else
    {
        root->right = insert(root->right, val);
    }

    return root;
}

struct node *minvalue(struct node *root )
{
    struct node *temp = root;
    while(root->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

struct node *deletenode(struct node *root, int val)
{
    if(root==NULL)
    return;

    if(val>root->data)
    {
        root->right = deletenode(root->right , val);
    }
    else if(val< root->data)
    {
        root->left = deletenode(root->left , val);
    }
    else{
        //data == val
        if(root->left == NULL && root->right == NULL)//no child
        {
            free(root);
        }
        else if(root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right== NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        
        struct node *temp = minvalue(root->right);
        root->data=temp->data;
        root->right = deletenode(root->right,temp->data);

    }
    return root;
}

struct node *search(struct node *root,int val)
{
    if(root==NULL || root->data == val )
    {
        return root;
    }

    if(val < root->data)
    {
       return search(root->left , val);
    }
    else{
        return search(root->right ,val);
    }
    
}   
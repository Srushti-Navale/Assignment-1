#include<stdio.h>
#include<stdlib.h>

// Structure for BST node
struct node
{
    int data;
    struct node *right;
    struct node *left;
};

// Function prototypes
struct node* createnode(int val);
struct node* insert(struct node* root, int val);
struct node* deleteNode(struct node* root, int value);
struct node* search(struct node* root, int val);
struct node* minvaluenode(struct node* root);

// Traversals
void inorder(struct node* root);
void preorder(struct node* root);
void postorder(struct node* root);

int main()
 {
    struct node* root = NULL;
    int choice=0;
    int value=0;
    int n=0;
    int i=0;

    printf("Enter number of elements to add in BST: ");
    scanf("%d", &n);

    printf("Enter %d values:\n", n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &value);
        root = insert(root, value);
    }

    do
     {
        printf("\nBinary Search Tree Menu\n");
        printf("1. Insert\n2. Delete\n3. Search\n");
        printf("4. Inorder Traversal\n5. Preorder Traversal\n6. Postorder Traversal\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
         {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);// updates the root after inserting new node
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);// updates the root after deletion
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value))
                    printf("%d found in BST.\n", value);
                else
                    printf("%d not found in BST.\n", value);
                break;

            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("enter valid choice\n");
        }

    } while (choice != 0);

    return 0;
}


struct node *createnode(int val)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = val;
    newnode->right = NULL;
    newnode->left = NULL;
    return newnode;
}

// Insert (duplicates go to right subtree)
struct node *insert(struct node *root , int val)
{
    if(root == NULL)
        return createnode(val);

    if(val < root->data)
        root->left = insert(root->left , val);
    else  // duplicates also go right
        root->right = insert(root->right , val);

    return root;
}

//used to find the min value node from right subtree to replace deleted node
struct node* minvaluenode(struct node* root) 
{
    struct node* temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}


struct node *deleteNode(struct node *root, int value)
{
    if(root == NULL)
        return root;

    if(value < root->data)
        root->left = deleteNode(root->left, value);
    else if(value > root->data)
        root->right = deleteNode(root->right, value);
    else//value == root->data
    {
        if(root->left == NULL && root->right == NULL)// no child
        {
            free(root);
            return NULL;
        }
        else if(root->left == NULL)// having only right child
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL) // having only left child
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        // having two children
        struct node *temp = minvaluenode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;//returns root after deletion
}

struct node *search(struct node *root , int val)
{
    if(root == NULL || root->data == val)
        return root;

    if(val < root->data)
        return search(root->left,val);
    else
        return search(root->right,val);
}

void inorder(struct node *root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}

void preorder(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

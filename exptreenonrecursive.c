#include <stdio.h>
#include <stdlib.h>

// Tree node
typedef struct node
{
    char data;
    struct node *left, *right;
} node;

// Stack node for linked list stack
typedef struct StackNode 
{
    node *treePtr;
    struct StackNode *next;
} StackNode;

StackNode *top = NULL;

void push(node *ptr);
node *pop();
node *peek();
int isEmpty();
node *createNode(char data);
node *constructTree(char *exp);
int isOperand(char ch);
void inorder(node *root);
void preorder(node *root);
void postorder(node *root);
void inorderNonRec(node *root);
void preorderNonRec(node *root);
void postorderNonRec(node *root);

int main() {
    char *exp;
    node *root = NULL;
    exp = (char *)malloc(100 * sizeof(char));

    printf("Enter postfix expression: ");
    scanf("%s", exp);

    root = constructTree(exp);

    int choice;
    do {
        printf("1. Recursive Inorder\n");
        printf("2. Recursive Preorder\n");
        printf("3. Recursive Postorder\n");
        printf("4. Non-Recursive Inorder\n");
        printf("5. Non-Recursive Preorder\n");
        printf("6. Non-Recursive Postorder\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Recursive Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 2:
                printf("Recursive Preorder: ");
                preorder(root);
                printf("\n");
                break;
            case 3:
                printf("Recursive Postorder: ");
                postorder(root);
                printf("\n");
                break;
            case 4:
                printf("Non-Recursive Inorder: ");
                inorderNonRec(root);
                printf("\n");
                break;
            case 5:
                printf("Non-Recursive Preorder: ");
                preorderNonRec(root);
                printf("\n");
                break;
            case 6:
                printf("Non-Recursive Postorder: ");
                postorderNonRec(root);
                printf("\n");
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! \n");
        }
    } while (choice > 0 && choice < 7);

    free(exp);
    return 0;
}

void push(node *ptr) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->treePtr = ptr;
    newNode->next = top;
    top = newNode;
}

node *pop() {
    if (top == NULL)
        return NULL;
    StackNode *temp = top;
    node *ptr = temp->treePtr;
    top = top->next;
    free(temp);
    return ptr;
}

node *peek() {
    if (top == NULL)
        return NULL;
    return top->treePtr;
}

int isEmpty() {
    return (top == NULL);
}

int isOperand(char ch) {
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'));
}

node *createNode(char data) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

node *constructTree(char *exp) {
    node *T1, *T2, *temp;
    for (char *p = exp; *p != '\0'; p++) {
        char symbol = *p;

        if (isOperand(symbol)) {
            temp = createNode(symbol);
            push(temp);
        } else {  // Operator
            T2 = pop();
            T1 = pop();
            temp = createNode(symbol);
            temp->left = T1;
            temp->right = T2;
            push(temp);
        }
    }
    return pop(); // root node
}

void inorder(node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
}

void preorder(node *root) {
    if (root != NULL) {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}

void inorderNonRec(node *root) {
    StackNode *stack = NULL;
    node *curr = root;

    while (curr != NULL || stack != NULL) {
        while (curr != NULL) {
            StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
            newNode->treePtr = curr;
            newNode->next = stack;
            stack = newNode;
            curr = curr->left;
        }

        StackNode *temp = stack;
        stack = stack->next;
        curr = temp->treePtr;
        printf("%c ", curr->data);
        free(temp);

        curr = curr->right;
    }
}

void preorderNonRec(node *root) {
    if (root == NULL)
        return;

    StackNode *stack = NULL;
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->treePtr = root;
    newNode->next = NULL;
    stack = newNode;

    while (stack != NULL) {
        StackNode *temp = stack;
        node *curr = temp->treePtr;
        stack = stack->next;
        free(temp);

        printf("%c ", curr->data);

        if (curr->right != NULL) {
            StackNode *rightNode = (StackNode *)malloc(sizeof(StackNode));
            rightNode->treePtr = curr->right;
            rightNode->next = stack;
            stack = rightNode;
        }
        if (curr->left != NULL) {
            StackNode *leftNode = (StackNode *)malloc(sizeof(StackNode));
            leftNode->treePtr = curr->left;
            leftNode->next = stack;
            stack = leftNode;
        }
    }
}

void postorderNonRec(node *root) {
    if (root == NULL)
        return;

    StackNode *stack1 = NULL, *stack2 = NULL;

    // push root to stack1
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->treePtr = root;
    newNode->next = NULL;
    stack1 = newNode;

    while (stack1 != NULL) {
        StackNode *temp = stack1;
        node *curr = temp->treePtr;
        stack1 = stack1->next;
        free(temp);

        StackNode *s2node = (StackNode *)malloc(sizeof(StackNode));
        s2node->treePtr = curr;
        s2node->next = stack2;
        stack2 = s2node;

        if (curr->left != NULL) {
            StackNode *leftNode = (StackNode *)malloc(sizeof(StackNode));
            leftNode->treePtr = curr->left;
            leftNode->next = stack1;
            stack1 = leftNode;
        }
        if (curr->right != NULL) {
            StackNode *rightNode = (StackNode *)malloc(sizeof(StackNode));
            rightNode->treePtr = curr->right;
            rightNode->next = stack1;
            stack1 = rightNode;
        }
    }

    // print and free stack2
    while (stack2 != NULL) {
        StackNode *temp = stack2;
        printf("%c ", temp->treePtr->data);
        stack2 = stack2->next;
        free(temp);
    }
}
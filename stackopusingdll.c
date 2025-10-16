#include <stdio.h>
#include <stdlib.h>

// Doubly Linked List Node Structure
struct dllNode
{
    struct dllNode *prev;
    int data;
    struct dllNode *next;
};

// Function Declarations
int menu(void);
int push(struct dllNode** head, struct dllNode** last, int* data);
int pop(struct dllNode** head, struct dllNode** last, int* deletedData);
int top(struct dllNode** head, struct dllNode** last, int* topData);
int displayStack(struct dllNode** head, struct dllNode** last);
int deleteStack(struct dllNode** head, struct dllNode** last);

int main(void)
{
    int choice = 0;
    int data = 0;
    int result = 0;

    struct dllNode *head = NULL;
    struct dllNode *last = NULL;

    do
    {
        choice = menu();

        switch (choice)
        {
        case 1: // Push
            printf("\n\tEnter data to push: ");
            scanf("%d", &data);
            result = push(&head, &last, &data);
            if (result == 0)
                printf("\n\t%d pushed onto stack.\n", data);
            else
                printf("\n\tPush failed. Memory allocation error.\n");
            break;

        case 2: // Pop
            result = pop(&head, &last, &data);
            if (result == 0)
                printf("\n\t%d popped from stack.\n", data);
            else
                printf("\n\tStack underflow. Nothing to pop.\n");
            break;

        case 3: // Display
            result = displayStack(&head, &last);
            if (result != 0)
                printf("\n\tStack is empty.\n");
            break;

        case 4: // Top
            result = top(&head, &last, &data);
            if (result == 0)
                printf("\n\tTop of stack: %d\n", data);
            else
                printf("\n\tStack is empty. No top element.\n");
            break;

        case 0: // Exit
            break;
        }
    } while (choice != 0);

    return 0;
}

// Menu for Stack
int menu(void)
{
    int choice = 0;
    do
    {
        printf("\n\n\t--- STACK MENU ---");
        printf("\n\t1. Push");
        printf("\n\t2. Pop");
        printf("\n\t3. Display Stack");
        printf("\n\t4. Top");
        printf("\n\t0. Exit");
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);
    } while (choice < 0 || choice > 4);
    return choice;
}

// Push Operation
int push(struct dllNode** head, struct dllNode** last, int* data)
{
    struct dllNode* newNode = (struct dllNode*)calloc(1, sizeof(struct dllNode));
    if (newNode == NULL)
        return 1;

    newNode->data = *data;

    if (*head == NULL)
    {
        *head = *last = newNode;
    }
    else
    {
        (*last)->next = newNode;
        newNode->prev = *last;
        *last = newNode;
    }

    return 0;
}

// Pop Operation
int pop(struct dllNode** head, struct dllNode** last, int* deletedData)
{
    if (*last == NULL)
        return 1;

    struct dllNode* temp = *last;
    *deletedData = temp->data;

    if (*head == *last)
    {
        // Only one node
        *head = *last = NULL;
    }
    else
    {
        *last = temp->prev;
        (*last)->next = NULL;
    }

    free(temp);
    return 0;
}

// Top Operation
int top(struct dllNode** head, struct dllNode** last, int* topData)
{
    if (*last == NULL)
        return 1;

    *topData = (*last)->data;
    return 0;
}

// Display Stack
int displayStack(struct dllNode** head, struct dllNode** last)
{
    if (*head == NULL)
        return 1;

    struct dllNode* current = *head;
    printf("\n\tStack contents (bottom to top): ");
    while (current != NULL)
    {
        printf("%4d", current->data);
        current = current->next;
    }
    printf("\n");
    return 0;
}



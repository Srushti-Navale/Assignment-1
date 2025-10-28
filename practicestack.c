#include <stdio.h>
#include <stdlib.h>

// Define stack node structure
struct stack {
    int data;
    struct stack *next;
};

// Function prototypes
void push(struct stack **head, int val);
int pop(struct stack **head);
void display(struct stack *head);
void displaytop(struct stack *head);

int main() {
    struct stack *head = NULL;
    int choice, val;

    do {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Display Top\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &val);
                push(&head, val);
                break;

            case 2:
                pop(&head);
                break;

            case 3:
                display(head);
                break;

            case 4:
                displaytop(head);
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
                break;
        }

    } while (choice != 0);

    return 0;
}

// Push operation
void push(struct stack **head, int val) {
    struct stack *newNode = (struct stack *)malloc(sizeof(struct stack));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = val;
    newNode->next = *head;
    *head = newNode;
    printf("Pushed %d onto stack\n", val);
}

// Pop operation
int pop(struct stack **head) {
    if (*head == NULL) {
        printf("Stack is empty\n");
        return -1;
    }

    struct stack *temp = *head;
    int poppedValue = temp->data;
    *head = (*head)->next;
    free(temp);

    printf("Popped %d from stack\n", poppedValue);
    return poppedValue;
}

// Display entire stack
void display(struct stack *head) {
    if (head == NULL) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Display top element
void displaytop(struct stack *head) {
    if (head == NULL) {
        printf("Stack is empty\n");
        return;
    }

    printf("Top element: %d\n", head->data);
}

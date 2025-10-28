#include<stdio.h>
#include<stdlib.h>

struct queue
{
    int data;
    struct queue *next;
};

int main() 
{
    struct queue *front = NULL;
    struct queue *rear = NULL;
    int choice, value;

    do {
        printf("\nQueue Menu\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&front, &rear, value);
                break;

            case 2:
                dequeue(&front);
                if (front == NULL) {
                    rear = NULL; // Reset rear if queue is empty
                }
                break;

            case 3:
                displayQueue(front);
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

void enqueue(struct queue **front, struct queue **rear, int value) 
{
    struct queue *newNode = (struct queue *)malloc(sizeof(struct queue));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (*rear) {
        (*rear)->next = newNode;
    }
    *rear = newNode;

    if (*front == NULL) {
        *front = newNode;
    }

    printf("Enqueued %d\n", value);
}

int dequeue(struct queue **front) {
    if (*front == NULL) {
        printf("Queue is empty\n");
        return -1;
    }

    struct queue *temp = *front;
    int dequeuedValue = temp->data;
    *front = (*front)->next;
    free(temp);

    printf("Dequeued %d\n", dequeuedValue);
    return dequeuedValue;
}

void displayQueue(struct queue *front) {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue elements: ");
    while (front != NULL) {
        printf("%d ", front->data);
        front = front->next;
    }
    printf("\n");
}

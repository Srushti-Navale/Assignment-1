#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for each node in priority queue
struct Node {
    char name[50];
    int priority;
    struct Node *next;
};

// Function prototypes
void enqueue(struct Node **front, char name[], int priority);
void dequeue(struct Node **front);
void display(struct Node *front);
int isEmpty(struct Node *front);

// Applications
void vehicleTrafficManagement();
void hospitalManagement();

int main()
{
    int choice;
    do
    {
        printf("\n");
        printf("\n PRIORITY QUEUE APPLICATIONS ");
        printf("\n");
        printf("\n1. Vehicle Traffic Management at Toll Plaza");
        printf("\n2. Hospital Management System");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                vehicleTrafficManagement();
                break;
            case 2:
                hospitalManagement();
                break;
            case 3:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while(choice != 3);

    return 0;
}

// PRIORITY QUEUE ADT FUNCTIONS

void enqueue(struct Node **front, char name[], int priority)
{
    struct Node *temp, *curr;
    temp = (struct Node*) malloc(sizeof(struct Node));
    strcpy(temp->name, name);
    temp->priority = priority;
    temp->next = NULL;

    // Insert according to priority (smaller number = higher priority)
    if (*front == NULL || priority < (*front)->priority)
    {
        temp->next = *front;
        *front = temp;
    } 
    else
    {
        curr = *front;
        while (curr->next != NULL && curr->next->priority <= priority)
            curr = curr->next;
        temp->next = curr->next;
        curr->next = temp;
    }
}

void dequeue(struct Node **front) 
{
    if (*front == NULL)
    {
        printf("\nQueue is empty!\n");
        return;
    }
    struct Node *temp = *front;
    printf("\nDequeued: %s (Priority %d)\n", temp->name, temp->priority);
    *front = (*front)->next;
    free(temp);
}

void display(struct Node *front)
{
    if (front == NULL)
    {
        printf("\nQueue is empty\n");
        return;
    }
    printf("\nCurrent Queue:\n");
    printf("\n");
    while (front != NULL)
    {
        printf("Name: %-15s | Priority: %d\n", front->name, front->priority);
        front = front->next;
    }
    printf("\n");
}

int isEmpty(struct Node *front)
{
    return front == NULL;
}


void vehicleTrafficManagement()
{
    struct Node *front = NULL;
    int choice, priority;
    char vehicle[50];

    do
    {
        printf("\nVehicle Traffic Management");
        printf("\n1. Add Vehicle");
        printf("\n2. Allow Vehicle to Pass");
        printf("\n3. Display Queue");
        printf("\n4. Exit to Main Menu");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter vehicle number: ");
                scanf("%s", vehicle);
                printf("Enter priority (1=Emergency, 2=VIP, 3=Regular): ");
                scanf("%d", &priority);
                enqueue(&front, vehicle, priority);
                break;

            case 2:
                dequeue(&front);
                break;

            case 3:
                display(front);
                break;

            case 4:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while(choice != 4);
}



void hospitalManagement()
{
    struct Node *front = NULL;
    int choice, priority;
    char patient[50];

    do {
        printf("\nHospital Management System");
        printf("\n1. Add Patient");
        printf("\n2. Attend Patient");
        printf("\n3. Display Queue");
        printf("\n4. Exit to Main Menu");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter patient name: ");
                scanf("%s", patient);
                printf("Enter priority (1=Critical, 2=Serious, 3=Normal): ");
                scanf("%d", &priority);
                enqueue(&front, patient, priority);
                break;

            case 2:
                dequeue(&front);
                break;

            case 3:
                display(front);
                break;

            case 4:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while(choice != 4);
}
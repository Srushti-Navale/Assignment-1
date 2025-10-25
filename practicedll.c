#include <stdio.h>
#include <stdlib.h>

struct node
{
   int data;
   struct node *next;
   struct node *prev;
};

void traverse(struct node **head);
void insertathead(struct node **head, struct node **tail, int data);
void insertatend(struct node **head, struct node **tail, int data);
void insertatposition(struct node **head, struct node **tail, int data, int position);
void deleteathead(struct node **head, struct node **tail, int *ddata);
void deleteatend(struct node **head, struct node **tail, int *ddata);
void deleteatposition(struct node **head, struct node **tail, int position, int *ddata);


int main()
{  
    struct node *head = NULL;
    struct node *tail = NULL;
    int data = 0;
    char choice = 'y';
    int position = 0;

    // Input initial list
    do
    {
        printf("Enter node data: ");
        scanf("%d", &data);

        struct node *newnode = (struct node *)malloc(sizeof(struct node));
        newnode->data = data;
        newnode->next = NULL;
        newnode->prev = NULL;

        if (head == NULL)
        {
            head = newnode;
            tail = newnode;
        }
        else
        {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }

        printf("Do you want to continue (y/n)? ");
        scanf(" %c", &choice); // space before %c to consume newline

    } while (choice == 'y' || choice == 'Y');

    int ch = 0;
    do
    {
        printf("\nMenu\n");
        printf("1. Display\n");
        printf("2. Insert at head\n");
        printf("3. Insert at end\n");
        printf("4. Insert at position\n");
        printf("5. Delete at head\n");
        printf("6. Delete at end\n");
        printf("7. Delete at position\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            traverse(&head);
            break;
        case 2:
            printf("Enter data to insert at head: ");
            scanf("%d", &data);
            insertathead(&head, &tail, data);
            break;
        case 3:
            printf("Enter data to insert at end: ");
            scanf("%d", &data);
            insertatend(&head, &tail, data);
            break;
        case 4:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            printf("Enter position (0-based): ");
            scanf("%d", &position);
            insertatposition(&head, &tail, data, position);
            break;
        case 5:
            deleteathead(&head, &tail, &data);
            printf("Deleted data is %d\n", data);
            break;
        case 6:
            deleteatend(&head, &tail, &data);
            printf("Deleted data is %d\n", data);
            break;
        case 7:
            printf("Enter position to delete: ");
            scanf("%d", &position);
            deleteatposition(&head, &tail, position, &data);
            printf("Deleted data is %d\n", data);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (ch != 0);

    return 0;
}

void traverse(struct node **head)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
    }
    else
    {
        struct node *temp = *head;
        printf("List: ");
        while (temp != NULL)
        {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void insertathead(struct node **head, struct node **tail, int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = *head;
    newnode->prev = NULL;

    *head = newnode;
    if (*tail == NULL)
        *tail = newnode;

    traverse(head);
}

void insertatend(struct node **head, struct node **tail, int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;

    if (*head == NULL)
    {
        *head = newnode;
        *tail = newnode;
    }
    else
    {
        (*tail)->next = newnode;
        newnode->prev = *tail;
        *tail = newnode;
    }
    traverse(head);
}

void insertatposition(struct node **head, struct node **tail, int data, int position)
{
    if (position == 0)
    {
        insertathead(head, tail, data);
        return;
    }

    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = *head;
    for (int i = 0; i < position - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Invalid position!\n");
        free(newnode);
        return;
    }

    newnode->next = temp->next;
    temp->next->prev=newnode;
    newnode->prev=temp;
    temp->next = newnode;

    if (newnode->next == NULL)
        *tail = newnode;

    traverse(head);
}

void deleteathead(struct node **head, struct node **tail, int *ddata)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    struct node *temp = *head;
    *ddata = temp->data;
    *head = (*head)->next;

    if (*head == NULL)
        *tail = NULL;

    free(temp);
    traverse(head);
}

void deleteatend(struct node **head, struct node **tail, int *ddata)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    struct node *temp = *head;

    if ((*head)->next == NULL)
    {
        *ddata = (*head)->data;
        free(*head);
        *head = NULL;
        *tail = NULL;
    }
    else
    {
        while (temp->next != *tail)
        {
            temp = temp->next;
        }

        *ddata = (*tail)->data;
        free(*tail);
        *tail = temp;
        (*tail)->next = NULL;
    }
    traverse(head);
}

void deleteatposition(struct node **head, struct node **tail, int position, int *ddata)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    if (position == 0)
    {
        deleteathead(head, tail, ddata);
        return;
    }

    struct node *temp = *head;
    for (int i = 0; i < position - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL)
    {
        printf("Invalid position!\n");
        return;
    }

    struct node *todelete = temp->next;
    *ddata = todelete->data;
    temp->next = todelete->next;
    todelete->next->prev=temp;

    if (todelete == *tail)
        *tail = temp;

    free(todelete);
    traverse(head);
}

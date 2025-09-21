#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

void traverse(struct node *fhead);
void addathead(struct node **fhead, int fval);
void addatend(struct node **fhead, int fval);
void addatposition(struct node **fhead, int fval, int fpos);
void insertaftervalue(struct node **fhead, int faftervalue, int fval);
void deleteathead(struct node **fhead);
void deleteatend(struct node **fhead);
void deleteatposition(struct node **fhead, int fpos);
void reverselist(struct node **fhead);
int menu(void);

int main()
{
    struct node *head = NULL;
    struct node *last = NULL;
    struct node *newnode;
    int choice = 0;
    int data = 0;
    int pos = 0; 
    int aftervalue = 0;
    char ch;
    
    do
    {
        newnode = (struct node *)calloc(1,sizeof(struct node));
        printf("\n\t Enter the node data:");
        scanf("%d",&newnode->data);
        if(head==NULL)
        {
            head = newnode;
            last = newnode;
        }
        else
        {
            last->next=newnode;
            last=newnode;
        }
        printf("\n\t do you want to add more node(y/n)");
        scanf(" %c",&ch);
    }while( ch == 'y' || ch == 'Y');

    do 
    {
        choice = menu();
        switch (choice)
        {
            case 1:
                traverse(head);
                break;
            case 2:
                printf("Enter value to add at head: ");
                scanf("%d", &data);
                addathead(&head, data);
                break;
            case 3:
                printf("Enter value to add at end: ");
                scanf("%d", &data);
                addatend(&head, data);
                break;
            case 4:
                printf("Enter value to insert: ");
                scanf("%d", &data);
                printf("Enter position (starting from 1): ");
                scanf("%d", &pos);
                addatposition(&head, data, pos);
                break;
            case 5:
                printf("Enter value to insert: ");
                scanf("%d", &data);
                printf("Enter the value after which to insert: ");
                scanf("%d", &aftervalue);
                insertaftervalue(&head, aftervalue, data);
                break;
            case 6:
                deleteathead(&head);
                break;
            case 7:
                deleteatend(&head);
                break;
            case 8:
                printf("Enter position from 1 to delete: ");
                scanf("%d", &pos);
                deleteatposition(&head, pos);
                break;
            case 9:
                reverselist(&head);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);
    return 0;
}


int menu(void)
{
    int choice = -1;
    do
    {
        printf("\n Linked List Menu\n");
        printf("1. Traverse\n");
        printf("2. Add Node at Head\n");
        printf("3. Add Node at End\n");
        printf("4. Add Node at Position\n");
        printf("5. Insert Node after Value\n");
        printf("6. Delete Node at Head\n");
        printf("7. Delete Node at End\n");
        printf("8. Delete Node at Position\n");
        printf("9. Reverse List\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
    } while (choice < 0 || choice > 9);
    return choice;
}

// Function definitions
void traverse(struct node *fhead)
{
    int flag = 0;
    struct node *temp = fhead;

    if (temp == NULL) 
    {
        printf("List is empty!\n");
        flag = 1;
    }

    if (flag == 0)
    {
        printf("Linked List: ");
        while (temp != NULL) 
        {
            printf("%d\t ", temp->data);
            temp = temp->next;
        }
    }
}

void addathead(struct node **fhead, int fval)
{
    struct node *newnode = (struct node*)calloc(1, sizeof(struct node));
    newnode->data = fval;
    newnode->next = *fhead;
    *fhead = newnode;
    printf("Node inserted at head.\n");
    traverse(*fhead);
}

void addatend(struct node **fhead, int fval) 
{
    struct node *newnode = (struct node*)calloc(1, sizeof(struct node));
    newnode->data = fval;
    newnode->next = NULL;

    if (*fhead == NULL)
    {
        *fhead = newnode;
    } 
    else
    {
        struct node *temp = *fhead;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }
    printf("Node inserted at end.\n");
    traverse(*fhead);
}

void addatposition(struct node **fhead, int fval, int fpos)
{
    int flag = 0;

    if (fpos == 1) 
    {
        addathead(fhead, fval);
        flag = 1;
    }

    if (flag == 0)
    {
        struct node *newnode = (struct node*)calloc(1, sizeof(struct node));
        newnode->data = fval;

        struct node *temp = *fhead;
        for (int i = 1; i < fpos - 1 && temp != NULL; i++)
        {
            temp = temp->next;
        }

        if (temp == NULL)
        {
            printf("Invalid position!\n");
            free(newnode);
            flag = 1;
        }

        if (flag == 0) 
        {
            newnode->next = temp->next;
            temp->next = newnode;
            printf("Node inserted at position %d.\n", fpos);
            traverse(*fhead);
        }
    }
}

void insertaftervalue(struct node **fhead, int faftervalue, int fval)
{
    int flag = 0;
    struct node *temp = *fhead;

    while (temp != NULL && temp->data != faftervalue)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Value %d not found in the list.\n", faftervalue);
        flag = 1;
    }

    if (flag == 0)
    {
        struct node *newnode = (struct node*)calloc(1, sizeof(struct node));
        newnode->data = fval;
        newnode->next = temp->next;
        temp->next = newnode;

        printf("Node inserted after value %d.\n", faftervalue);
        traverse(*fhead);
    }
}

void deleteathead(struct node **fhead)
{
    int flag = 0;

    if (*fhead == NULL)
    {
        printf("List is empty!\n");
        flag = 1;
    }

    if (flag == 0)
    {
        struct node *temp = *fhead;
        *fhead = (*fhead)->next;
        free(temp);

        printf("Node deleted from head.\n");
        traverse(*fhead);
    }
}

void deleteatend(struct node **fhead)
{
    int flag = 0;

    if (*fhead == NULL)
    {
        printf("List is empty!\n");
        flag = 1;
    }

    if (flag == 0 && (*fhead)->next == NULL)
    {
        free(*fhead);
        *fhead = NULL;
        printf("Node deleted from end.\n");
        flag = 1;
    }

    if (flag == 0)
    {
        struct node *temp = *fhead;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;

        printf("Node deleted from end.\n");
        traverse(*fhead);
    }
}


void deleteatposition(struct node **fhead, int fpos) 
{
    int flag = 0;

    if (*fhead == NULL)
    {
        printf("List is empty!\n");
        flag = 1;
    }

    if (flag==0 && fpos == 1)
    {
        deleteathead(fhead);
        flag =1;
    }

    if(flag == 0)
    {
        struct node *temp = *fhead;
        for (int i = 1; i < fpos - 1 && temp != NULL; i++)
        {
            temp = temp->next;
        }

        if (temp == NULL || temp->next == NULL)
        {
            printf("Invalid position!\n");
            flag = 1;
        }

        if (flag == 0) 
        {
            struct node *delnode = temp->next;
            temp->next = delnode->next;
            free(delnode);

            printf("Node deleted at position %d.\n", fpos);
            traverse(*fhead);
         }
    }
}

void reverselist(struct node **fhead)
{
    struct node *prev = NULL, *current = *fhead, *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *fhead = prev;
    printf("Linked List reversed.\n");
    traverse(*fhead);
}

#include <stdio.h>
#include <stdlib.h>

struct dllNode
{
    struct dllNode *prev;
    int data;
    struct dllNode *next;
};

int menu(void);
int addNodeAfterLast(struct dllNode** fHead, struct dllNode** fLast, int* fIData);
int addNodeBeforeHead(struct dllNode** fHead, struct dllNode** fLast, int* fIData);
int deleteNodeHead(struct dllNode** fHead, struct dllNode** fLast, int* fDData);
int deleteNodeLast(struct dllNode** fHead, struct dllNode** fLast, int* fDData);
int displayFirstNodeData(struct dllNode** fHead, struct dllNode** fLast, int* fDData);
int displayLastNodeData(struct dllNode** fHead, struct dllNode** fLast, int* fDData);
int displayLL(struct dllNode** fHead, struct dllNode** fLast);
int deleteDLL(struct dllNode** fHead, struct dllNode** fLast);


int main(void)
{
    int choice = 0;
    int iData = 0;
    int dData = 0;
    int succ = 0;
    struct dllNode *head = NULL;
    struct dllNode *last = NULL;

    do
    {
        choice = menu();
        switch (choice)
        {
        case 1:printf("\n\t Enter data = ");
            scanf("%d", &iData);
            succ = addNodeBeforeHead(&head, &last, &iData);
            if (succ == 0)
            {
                printf("\n\t %d data added successfully before head", iData);
            }
            else
            {
                printf("\n\t %d data not added before head, memory allocation failed", iData);
            }
            break;
        case 2:printf("\n\t Enter data = ");
            scanf("%d", &iData);
            succ = addNodeAfterLast(&head, &last, &iData);
            if (succ == 0)
            {
                printf("\n\t %d data added successfully after last", iData);
            }
            else
            {
                printf("\n\t %d data not added before head, memory allocation failed", iData);
            }
            break;
        case 3: succ = deleteNodeHead(&head, &last, &dData);
            if (succ == 0)
            {
                printf("\n\t %d data deleted", dData);
            }
            else
            {
                printf("\n\t Data not deleted, LL empty");
            }

            break;
        case 4: succ = deleteNodeLast(&head, &last, &dData);
            if (succ == 0)
            {
                printf("\n\t %d data deleted", dData);
            }
            else
            {
                printf("\n\t Data not deleted, LL empty");
            }
            break;
        case 5: succ = displayLL(&head, &last);
            if (succ != 0)
            {
                printf("\n\t LL is empty, no display");
            }
            break;
        case 6: succ = displayFirstNodeData(&head, &last, &dData);
            if (succ == 0)
            {
                printf("\n\t First node data = %d", dData);
            }
            else
            {
                printf("\n\t Data not displayed, LL empty");
            }
            break;
        case 7: succ = displayLastNodeData(&head, &last, &dData);
            if (succ == 0)
            {
                printf("\n\t Last node data = %d", dData);
            }
            else
            {
                printf("\n\t Data not displayed, LL empty");
            }
            break;
        case 0: succ = deleteDLL(&head, &last);
            if (succ == 0)
            {
                printf("\n\t DLL memeory freed successfully");
            }
            else
            {
                printf("\n\t DLL empty, No memory freed");
            }
            printf("\n\t Thank You, visit again");
            break;

        }
    } while (choice != 0);

    return 0;
}

int menu(void)
{
    int choice = 0;
    do
    {
        printf("\n\t DLL Menu");
        printf("\n\t 1. Add node before head");
        printf("\n\t 2. Add node after last");
        printf("\n\t 3. Delete head node");
        printf("\n\t 4. Delete last node");
        printf("\n\t 5. Display LL");
        printf("\n\t 6. Display first node data");
        printf("\n\t 7. Display last node data");
        printf("\n\t 0. Exit");
        printf("\n\t Enter your choice = ");
        scanf("%d", &choice);
    } while (choice < 0 || choice > 7);
    return choice;
}

int addNodeBeforeHead(struct dllNode** fHead, struct dllNode** fLast, int* fIData)
{
    int succ = 0;
    struct dllNode* h = NULL;
    struct dllNode* l = NULL;
    struct dllNode* newnode = NULL;

    h = *fHead;
    l = *fLast;

    newnode = (struct dllNode*)calloc(1, sizeof(struct dllNode));
    if (newnode == NULL)
    {
        // memory allocated failed
        succ = 1;
    }
    else
    {
        newnode->data = *fIData;
        if (h == NULL)
        {
            // LL empty
            h = newnode;
            l = newnode;
        }
        else
        {
            newnode->next = h;
            h->prev = newnode;
            h = newnode; // head updated
        }
    }
    *fHead = h;
    *fLast = l;

    return succ;
}

int addNodeAfterLast(struct dllNode** fHead, struct dllNode** fLast, int* fIData)
{
    int succ = 0;
    struct dllNode* h = NULL;
    struct dllNode* l = NULL;
    struct dllNode* newnode = NULL;

    h = *fHead;
    l = *fLast;

    newnode = (struct dllNode*)calloc(1, sizeof(struct dllNode));
    if (newnode == NULL)
    {
        // memory allocated failed
        succ = 1;
    }
    else
    {
        newnode->data = *fIData;
        if (h == NULL)
        {
            // LL empty
            h = newnode;
            l = newnode;
        }
        else
        {
            l->next = newnode;
            newnode->prev = l;
            l = newnode; // last updated
        }
    }
    *fHead = h;
    *fLast = l;

    return succ;
}

int deleteNodeHead(struct dllNode** fHead, struct dllNode** fLast, int* fDData)
{
    int succ = 0;
    struct dllNode* h = NULL;
    struct dllNode* l = NULL;
    struct dllNode* dnode = NULL;

    h = *fHead;
    l = *fLast;

    if (h == NULL)
    {
        // LL empty
        succ = 1;
    }
    else
    {
        dnode = h;
        if (h->next != NULL)
        {
            // LL is having atleast 2 nodes
            h = h->next;        // last is updated
            h->prev = NULL;     // dnode is seperated
            dnode->next = NULL; // dnode is seperated    
        }

        *fDData = dnode->data;
        free(dnode);
        dnode = NULL;
    }

    *fHead = h;
    *fLast = l;

    return succ;
}


int deleteNodeLast(struct dllNode** fHead, struct dllNode** fLast, int* fDData)
{
    int succ = 0;
    struct dllNode* h = NULL;
    struct dllNode* l = NULL;
    struct dllNode* dnode = NULL;

    h = *fHead;
    l = *fLast;

    if (h == NULL)
    {
        // LL empty
        succ = 1;
    }
    else
    {
        dnode = l;
        if (l->prev != NULL)
        {
            // LL is having atleast 2 nodes
            l = l->prev;        // last is updated
            l->next = NULL;     // dnode is seperated
            dnode->prev = NULL; // dnode is seperated    
        }

        *fDData = dnode->data;
        free(dnode);
        dnode = NULL;
    }

    *fHead = h;
    *fLast = l;

    return succ;
}


int displayFirstNodeData(struct dllNode** fHead, struct dllNode** fLast, int* fDData)
{
    // Display Front node data - queue operation
    int succ = 0;
    struct dllNode* h = NULL;
    struct dllNode* l = NULL;
    struct dllNode* dnode = NULL;

    h = *fHead;
    l = *fLast;

    if (h == NULL)
    {
        // LL empty
        succ = 1;
    }
    else
    {
        dnode = h;
        *fDData = dnode->data;
    }

    *fHead = h;
    *fLast = l;

    return succ;
}

int displayLastNodeData(struct dllNode** fHead, struct dllNode** fLast, int* fDData)
{
    // Display Last node data - stack operation - Stack Top
    int succ = 0;
    struct dllNode* h = NULL;
    struct dllNode* l = NULL;
    struct dllNode* dnode = NULL;

    h = *fHead;
    l = *fLast;

    if (l == NULL)
    {
        // LL empty
        succ = 1;
    }
    else
    {
        dnode = l;
        *fDData = dnode->data;
    }

    *fHead = h;
    *fLast = l;

    return succ;
}


int displayLL(struct dllNode** fHead, struct dllNode** fLast)
{
    int succ = 0;
    struct dllNode* h = NULL;
    struct dllNode* l = NULL;
    struct dllNode* i = NULL;
    h = *fHead;
    l = *fLast;

    if (h == NULL)
    {
        // LL empty
        succ = 1;
    }
    else
    {
        printf("\n\t DLL data = ");
        for (i = h; i != NULL; i = i->next)
        {
            printf("%4d", i->data);
        }
    }



    *fHead = h;
    *fLast = l;
    return succ;
}

int deleteDLL(struct dllNode** fHead, struct dllNode** fLast)
{
    int succ = 0;
    struct dllNode* h = NULL;
    struct dllNode* l = NULL;
    struct dllNode* dnode = NULL;

    h = *fHead;
    l = *fLast;

    if (h == NULL)
    {
        // LL empty
        succ = 1;
    }
    else
    {
        while (h != NULL)
        {
            dnode = h;
            if (h->next != NULL)
            {
                // LL is having atleast 2 nodes
                h = h->next;        // last is updated
                h->prev = NULL;     // dnode is seperated
                dnode->next = NULL; // dnode is seperated    
            }          
            else
            {
                h = NULL;
                l = NULL;
            }
            free(dnode);
            dnode = NULL;
        }
       
    }

    *fHead = h;
    *fLast = l;

    return succ;
}

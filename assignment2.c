#include <stdio.h>

// function declarations
int menu(void);
void acceptSet(int fa[], int fn);
void displaySet(int fa[], int fn);
int isPresent(int element, int fa[], int fn);
void unionSet(int fa[], int fb[], int fn, int fm);
void intersectionSet(int fa[], int fb[], int fn, int fm);
void differenceSet(int fa[], int fb[], int fn, int fm);
void symmetricDifference(int fa[], int fb[], int fn, int fm);


int main() 
{
    int A[10] = {0}, B[10] = {0}, n = 0, m = 0, choice = 0;

    printf("Enter the cardinality of set A: ");
    scanf("%d", &n);
    acceptSet(A, n);

    printf("Enter the cardinality of set B: ");
    scanf("%d", &m);
    acceptSet(B, m);

    do 
    {
        choice = menu();

        switch (choice)
        {
            case 1:
                printf("Set A: ");
                displaySet(A, n);
                printf("Set B: ");
                displaySet(B, m);
                break;
            case 2:
                unionSet(A, B, n, m);
                break;
            case 3:
                intersectionSet(A, B, n, m);
                break;
            case 4:
                differenceSet(A, B, n, m);
                break;
            case 5:
                symmetricDifference(A, B, n, m);
                break;
            case 0:
                printf("\nThank you, exiting program.\n");
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
        printf("\nSet Operations Menu\n");
        printf("1. Display Sets\n");
        printf("2. Union\n");
        printf("3. Intersection\n");
        printf("4. Difference (A - B)\n");
        printf("5. Symmetric Difference\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
    } while (choice < 0 || choice > 5);

    return choice;
}


// function to accept set elements
void acceptSet(int fa[], int fn)
{
    int element;

    for (int i = 0; i < fn; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &element);

        // check for duplicate
        int flag = isPresent(element, fa, i);
        if (flag == 1)
        {
            printf("Duplicate element not allowed! Enter a different element.\n");
            i--;
        }
        else 
        {
            fa[i] = element;
        }
    }
}


// function to display a set
void displaySet(int fa[], int fn)
{
    printf("{ ");
    for (int i = 0; i < fn; i++)
    {
        printf("%d ", fa[i]);
    }
    printf("}\n");
}


// function to check presence of an element
int isPresent(int element, int fa[], int fn)
{
    int flag = 0; 
    for (int i = 0; i < fn; i++) {
        if (element == fa[i]) {
            flag = 1;   // found
        }
    }
    return flag;
}


// union of two sets
void unionSet(int fa[], int fb[], int fn, int fm) 
{
    int result[20];
    int size = 0;

    for (int i = 0; i < fn; i++) 
    {
        result[size++] = fa[i];
    }
    for (int i = 0; i < fm; i++)
    {
        int flag = isPresent(fb[i], result, size);
        if (flag == 0)
        {
            result[size++] = fb[i];
        }
    }

    printf("Union Set: ");
    displaySet(result, size);
}


// intersection of two sets
void intersectionSet(int fa[], int fb[], int fn, int fm)
{
    int result[20];
    int size = 0;

    for (int i = 0; i < fn; i++)
    {
        int flag = isPresent(fa[i], fb, fm);
        if (flag == 1)
        {
            result[size++] = fa[i];
        }
    }

    printf("Intersection Set: ");
    displaySet(result, size);
}


// difference of two sets (A - B)
void differenceSet(int fa[], int fb[], int fn, int fm) 
{
    int result[20];
    int size = 0;

    for (int i = 0; i < fn; i++) 
    {
        int flag = isPresent(fa[i], fb, fm);
        if (flag == 0)
        {
            result[size++] = fa[i];
        }
    }

    printf("A - B: ");
    displaySet(result, size);
}


// symmetric difference
void symmetricDifference(int fa[], int fb[], int fn, int fm)
{
    int result[20];
    int size = 0;

    for (int i = 0; i < fn; i++)
    {
        int flag = isPresent(fa[i], fb, fm);
        if (flag == 0) 
        {
            result[size++] = fa[i];
        }
    }
    for (int i = 0; i < fm; i++)
    {
        int flag = isPresent(fb[i], fa, fn);
        if (flag == 0)
        {
            result[size++] = fb[i];
        }
    }

    printf("Symmetric Difference: ");
    displaySet(result, size);
}

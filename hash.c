#include <stdio.h>


void createTable(int hash[][3], int mod);
void displayTable(int hash[][3], int mod);
int chaininsert(int hash[][3], int mod, int key);
int search(int hash[][3], int mod, int target);
int menu(void);


int main()
{
    int mod = 0, key = 0, ch = 0, success = 0, found = 0, target = 0;


    printf("\nEnter the mod : ");
    fflush(stdout);
    scanf("%d", &mod);
    int hash[mod][3];
    createTable(hash, mod);


    do
    {
        ch = menu();


        switch (ch)
        {
        case 1:


            do
            {
                printf("\nEnter the value to be inserted: ");
                fflush(stdout);
                scanf("%d", &key);


                success = chaininsert(hash, mod, key);
                if (success == 0)
                {
                    printf("\n%d not inserted.\nHash Table is full.\n", key);
                    break;
                }


                printf("\nEnter the choice:\n1.Yes\n2.No\n");
                fflush(stdout);
                scanf("%d", &ch);
            } while (ch != 2);
            break;


        case 2:
            displayTable(hash, mod);
            break;


        case 3:
            printf("\nEnter the element to search : ");
            scanf("%d", &target);
            found = search(hash, mod, target);
            if (found == 1)
            {
                printf("\nElement found\n");
            }
            else
            {
                printf("\nElement not found\n");
            }
            break;


        case 0:
            printf("\nExiting...");
            break;
        }


    } while (ch != 0);


    return 0;
}


int menu(void)
{
    int ch = 0;


    do
    {
        printf("\nHashing Operations:");
        printf("\n1.Create");
        printf("\n2.Display");
        printf("\n3.Search");
        printf("\n0.Exit");
        printf("\nEnter the choice: ");
        scanf("%d", &ch);


    } while (ch < 0 || ch > 3);
}


void createTable(int hash[][3], int mod)
{
    for (int i = 0; i < mod; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j == 0)
            {
                hash[i][0] = i;
            }
            else if (j == 1)
            {
                hash[i][1] = 0;
            }
            else
            {
                hash[i][2] = -1;
            }
        }
    }
}


void displayTable(int hash[][3], int mod)
{
    int i = 0, j = 0;
    printf("\nIndex Value  Chain\n");
    for (i = 0; i < mod; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("  %d    ", hash[i][j]);
        }
        printf("\n");
    }
}


int chaininsert(int hash[][3], int mod, int key)
{
    int index = 0;
    int flag = 0;
    int newIndex = -1;
    int prev = 0;
    index = key % mod;


    if (hash[index][1] == 0)
    {
        hash[index][1] = key;
        hash[index][2] = -1;
        flag = 1;
    }
    else
    {
        prev = index;
        while (hash[prev][2] != -1 && (hash[hash[prev][2]][1] % mod) == index)//when 2nd position is not available and next chained index points to same hash index
        {
            prev = hash[prev][2];
        }


        for (int i = 1; i < mod; i++)
        {
            newIndex = (index + i) % mod;
            if (hash[newIndex][1] == 0)
            {
                hash[newIndex][1] = key;
                hash[newIndex][2] = -1;

                if (hash[prev][1] % mod == index)
                {
                    hash[prev][2] = newIndex;
                }
                else
                {
                    for (int i = index + 1; i < mod; i++)
                    {
                        if (hash[i][1] % mod == index && hash[i][0] != newIndex && hash[i][2] == -1)
                        {
                            hash[i][2] = newIndex;
                        }
                    }

                }


                flag = 1;
                break;
            }
        }


        return flag;
    }
}


int search(int hash[][3], int mod, int target)
{
    int index = target % mod;
    int findex = 0, flag = 0, next = 0;
    for (int i = 0; i < mod; i++)
    {
        if (hash[i][1] % mod == index)
        {
            findex = i;
            break;
        }
    }

    if (hash[findex][1] == target)
    {
        flag = 1;
    }
    else
    {
        while (hash[findex][2] != -1)
        {
            next = hash[findex][2];
            if (hash[findex][1] == target)
            {
                flag = 1;
                break;
            }
            findex = next;
        }
    }
    return flag;
}
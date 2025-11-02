#include <stdio.h>


int main()
{
    int ch = 0;

    do
    {
        menu();
        printf("\nEnter the choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 0:
            printf("\nExiting...");
            break;
        default:
            printf("\nInvalid choice");
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


int createTable(int hash[][3], int mod)
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

    if(hash[index][1]== 0)//home place
    {
        hash[index][1] = key;
        flag = 1;
        return flag;
    }
    else
    {
        prev = index;
        while (hash[prev][2] != -1  && (hash[hash[prev][2]][1] % mod)== index)
        {
            prev = hash[prev][2];
        }

        for(int i = 1; i < mod; i++)
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
    }
}


int search(int hash[][3], int size, int key) {
    int index = key % size;
    int temp = index;
    int flag = 0;

    // If slot empty at base index → not found
    if (hash[temp][1] == 0)
        flag = 1;
    else
    {

    // Traverse through chain
    while (temp != -1) {
        if (hash[temp][1] == key)
            flag = 1;
        temp = hash[temp][2];
    }
    }
    return flag;
}

#include <stdio.h>

int menu(void);
void accept(int fa[], int fn);
void display(int fa[], int fn);
void linearSearch(int fa[], int fns, int fn);
void bubblesort(int fa[], int fn);
void binarySearch(int fa[], int fns, int fn);


void accept(int fa[], int fn)
{
   printf("Enter %d elements:\n", fn);
    for(int i = 0; i < fn; i++)
    {
        scanf("%d", &fa[i]);
    }
}


void display(int fa[], int fn)
{
    printf("Array elements: ");
    for(int i = 0; i < fn; i++)
    {
        printf("%d\t", fa[i]);
    }
    printf("\n");
}


void linearSearch(int fa[], int fns, int fn)
{
    int flag = 0;
    for(int i = 0; i < fn; i++)
    {
        if(fa[i] == fns)
        {
            printf("Element %d is found at index %d\n", fns, i);
            flag = 1;
        }
    }
    if(flag == 0)
       printf("Element %d is not found in the array.\n", fns);
}

//function for bubble sort
void bubblesort(int fa[], int fn)
{
    int temp=0;
   for(int i = 0; i < fn - 1; i++){
        for(int j = 0; j < fn - 1 - i; j++){
            if(fa[j] > fa[j + 1]){
                temp = fa[j];
                fa[j] = fa[j + 1];
                fa[j + 1] = temp;
            }
        }
    }
    printf("Sorted ");
    display(fa,fn);
}


//function for binary search
void binarySearch(int fa[], int fns, int fn)
{
    int low = 0;
    int high = fn - 1;
    int mid=0;
    int found = 0;
    
    while(low <= high)
    {
        mid = (low + high) / 2;
        if(fa[mid] == fns)
        {
            printf("Element %d found at index %d\n", fns, mid);
            found = 1;
            low = high + 1 ;
        }
        else if(fa[mid] < fns)
         low = mid + 1;
        else high = mid - 1;
        }

    if(found == 0)
    {
        printf("Element %d not found in the array.\n", fns);
    }
}



//printing menu
int menu(void)
{
 int choice=0;
 
 do
 {
   printf("\n\t menu operations");
   printf("\n\t 1.accept");
   printf("\n\t 2.display");
   printf("\n\t 3.linear search");
   printf("\n\t 4.bubble sort");
   printf("\n\t 5.binary search");
   printf("\n\t 0.Exit");
   printf("\n enter your choice=");
   scanf("%d",&choice);
 }while(choice<0 || choice>5);
 return choice;
 
}


//main function
int main()
{
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int a[n];
    int ns=0;
    int ch=0;
    
    do
    {
      ch = menu();
    
      switch(ch)
      {
        
        case 1:
            accept(a,n);
            break;
            
        case 2:
            display(a,n);
            break;

        case 3:
            printf("Enter the element you want to search: ");
            scanf("%d", &ns);
            linearSearch(a, ns, n);
            break;

        case 4 :
           bubblesort(a, n);
           break;

        case 5 :
           bubblesort(a, n);
           printf("Enter the element you want to search: ");
           scanf("%d", &ns);
           binarySearch(a,ns,n);
           break;

        case 0 :
           printf("\n\tThank you , visit again");
           break;

      }
    
    }while(ch!=0);

    return 0;
}

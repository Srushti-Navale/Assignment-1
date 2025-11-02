#include <stdio.h>
#define MAX 20

void createGraph(int adj[][MAX], int *n) ;
void primMST(int adj[][MAX], int n) ;

int main() 
{
    int adj[MAX][MAX], n = 0, ch;

    do 
    {
        printf("\nMENU");
        printf("\n1. Create Graph");
        printf("\n2. Find MST (using Prim's algorithm)");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch(ch) 
        {
            case 1:
                createGraph(adj, &n);
                break;

            case 2:
                if(n == 0)
                    printf("\nPlease create the graph first!\n");
                else
                    primMST(adj, n);
                break;

            case 3:
                printf("\nExiting...\n");
                break;

            default:
                printf("\nInvalid Choice! Try again.\n");
        }

    } while(ch != 3);

    return 0;
}

void createGraph(int adj[][MAX], int *n) 
{
    printf("\nEnter number of vertices: ");
    scanf("%d", n);

    printf("\nEnter adjacency matrix (0 for no edge):\n");
    for(int i = 0; i < *n; i++) 
    {
        for(int j = 0; j < *n; j++) 
        {
            scanf("%d", &adj[i][j]);
        }
    }

    printf("\nGraph Created Successfully!\n");
}

void primMST(int adj[][MAX], int n)
{
    int visited[MAX], cost = 0;

    for(int i = 0; i < n; i++)
        visited[i] = 0;

    visited[0] = 1;  // Start with vertex 0

    printf("\nEdges in MST:\n");

    for(int count = 0; count < n - 1; count++) 
    {
        int min = 999, u = -1, v = -1;

        for(int i = 0; i < n; i++)
     {
            if(visited[i] == 1) 
            {
                for(int j = 0; j < n; j++)
                 {
                    if(adj[i][j] != 0 && visited[j] == 0 && adj[i][j] < min) {
                        min = adj[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        visited[v] = 1;
        cost += min;
        printf("%d -> %d (Cost = %d)\n", u, v, min);
    }

    printf("\nTotal Minimum Cost of MST = %d\n", cost);
}



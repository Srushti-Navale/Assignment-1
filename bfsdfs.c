#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int menu();
void creategraph(int arr[][MAX], int vertex, int edges);
void bfs(int arr[][MAX], int vertex, int start, int visited[]);
void dfs(int arr[][MAX], int vertex, int start, int visited[]);

int main()
{
    int choice = 0;
    int vertex = 0;
    int edges = 0;
    int visited[MAX] = {0};

    printf("Enter number of vertex:");
    scanf("%d", &vertex);
    printf("Enter number of edges:");
    scanf("%d", &edges);
    // Initialize adjacency matrix with 0
    int arr[MAX][MAX] = {0};

    int start = 0;
    do
    {
        choice = menu();
        switch (choice)
        {

        case 1:
            creategraph(arr, vertex, edges);
            break;

        case 2:
            printf("Enter the starting point:");
            scanf("%d", &start);
            for (int i = 0; i < MAX; i++)
            {
                visited[i] = 0;
            }
            bfs(arr, vertex, start, visited);
            break;

        case 3:
            printf("Enter start vertex for DFS: ");
            scanf("%d", &start);
            for (int i = 0; i < MAX; i++)
            {
                visited[i] = 0;
            }
            dfs(arr, vertex, start, visited);
            break;

        case 0:
            printf("Exiting..Thank You Visit again !");
        }

    } while (choice != 0);
}

int menu()
{
    int ch = 0;
    do
    {
        printf("\n\tMenu Options:");
        printf("\n\t1]Create The Adjency matrix correspoding to the graph");
        printf("\n\t2]BFS Traversal");
        printf("\n\t3]DFS Traversal ");
        printf("\n\t0]Exit the Menu");
        printf("\n\tEnter Your choice ==> ");
        scanf("%d", &ch);

    } while (ch < 0 || ch > 3);
    return ch;
}

void creategraph(int arr[][MAX], int vertex, int edges)
{
    int u = 0;
    int v = 0;
    printf("Enter the edges between (u v):");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);
        arr[u][v] = 1;
        arr[v][u] = 1;
    }
    // display the adj matrix
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void bfs(int arr[][MAX], int vertex, int start, int visited[])
{

    int queue[MAX];
    int front = 0;
    int rear = 0;
    printf("BFS Traversal:");
    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) // i.e jab tak queue not empty
    {
        int root = queue[front++]; // aage ka remove karna hai
        printf("%d ", root);
        for (int i = 0; i < vertex; i++)
        {
            if (arr[root][i] == 1 && !visited[i])
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

void dfs(int arr[][MAX], int vertex, int start, int visited[])
{
    printf("%d ",start);
    visited[start]=1;//mark is 1 when printed

    for(int j=0;j<vertex;j++)
    {
        if(arr[start][j]==1 && !visited[j])
        {
            dfs(arr,vertex,j,visited);//pass new start
        }
    }

}
#include<stdio.h>
 

void creategraph( int adj[][100],int *n)
{
    printf("no of vertices in grapth :");
    scanf("%d", n);

    printf("enter the weight of edges in adj matrix (0 for no edge )\n");
    for(int i =0;i< *n ;i++)
    {
        for(int j=0;j<*n;j ++)
        {
            printf("%d-->%d :",i,j);
           scanf("%d" , &adj[i][j]);
        }
    }

    printf("\ngraph created");
}

void primmst(int adj[][100],int n)
{
    int visited[100],cost=0;

    for(int i=0;i<n;i++)
    {
        visited[i]=0;
    }

    visited[0]=1;
    printf("\nedges in mst :\n");

    for(int count=0;count < n-1; count++)
    {
      int min = 999;
      int u=-1,v=-1;
      for(int i=0;i<n;i++)
      {
        if(visited[i] == 1)
        {
            for(int j=0;j<n;j++)
            {
              if(  adj[i][j] !=0 && visited[j] == 0 && adj[i][j]<min )
              {
                min=adj[i][j];
                u=i;
                v=j;
              }
            }
        }
      }
      visited[v]==1;
      cost += min ;
      printf("%d->%d (cost = %d)\n",u,v,min);
    }
}


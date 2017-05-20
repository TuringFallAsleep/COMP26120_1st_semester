#include "graph.h"

int *distance; //distance from v to u
int *visited;
int n=0;

int* getInDegree(Graph *mygraph)
{
  int *indegree = malloc(sizeof(int)*(mygraph->MaxSize));
  for (int i = 1; i < mygraph->MaxSize; i++)
  {
    indegree[i] = 0;
  }
  for (int i = 1; i < mygraph->MaxSize; i++)
  {
    List* list = mygraph->table[i].outlist;
    if (!list)
    {
      continue;
    }
    while(list)
    {
      indegree[list->index]++;
      list = list->next;
    }
  }
  return indegree;
}


void heapInsert(int *distance, int *Q, int index)
{
  // printf("insert %d in Q[%d]\n", index,n);
  Q[n++] = index;
  int i = n;
  int temp;
  while(i>1 && distance[Q[i/2]+1]>distance[Q[i]+1])
  {
    temp = Q[i/2];
    Q[i/2] = Q[i];
    Q[i] = temp;
    i = i/2;
  }
  
}



int heapRemoveMin(int *Q,int *distance)
{
  // printf("in heapRemoveMin\n");
  int temp = Q[0];
  // printf("remove %d\n", temp);
  Q[0] = Q[n];
  // printf("Q[n] = Q[%d] = %d\n",n,Q[n]);
  n--;
  int i = 0;
  int child;

 
  while(i<n)
  {   

      if (2*i+2<n && distance[Q[2*i+2]+1] < distance[Q[i]+1] 
                  && distance[Q[2*i+1]+1] < distance[Q[i]+1])
        child = (distance[Q[2*i+2]+1] < distance[Q[2*i+1]+1]) ? 2*i+2 : 2*i+1;
      else if (2*i+2<n && distance[Q[2*i+2]+1] < distance[Q[i]+1])
        child = 2*i+2;
      else if (2*i+1<n && distance[Q[2*i+1]+1] < distance[Q[i]+1])
        child = 2*i+1; 
      else
        break;
    

    int t = Q[i];
    Q[i] = Q[child];
    Q[child] = t;
    i = child;
    // printf("i = %d, n = %d\n",i,n);    
  }
  return temp;
}

int* dijkastraShortestPaths(Graph* mygraph, int v){
  int u = v;
  n = 0;
  // printf("now source: v = %d\n", v);
  // int *distance; //distance from v to u
  distance = (int *)malloc(sizeof(int)*(mygraph->MaxSize+1));
  // int *visited;
  visited = (int *)malloc(sizeof(int)*(mygraph->MaxSize+1));
  for (int i = 0; i <= mygraph->MaxSize; i++)
  {
    distance[i] = mygraph->MaxSize;// use mygraph->MaxSize+1 to represent infinite (v to i)
    visited[i] = 0;
  }
  distance[v] = 0;




  int *Q; // a priority queue that store all vertices using distance[i] as key
  Q = (int *)malloc(sizeof(int)*mygraph->MaxSize);
  
  for (int i = 0; i < mygraph->MaxSize; ++i)
  {
    Q[i] = -1;
  }

  // Q[0] = v; // insert v
  // n++;

  int newVertex=0;
  int z = v;
  List *list;

  heapInsert(distance,Q,z);
  while(Q[0]!=-1 && n > 0){
    do{ 

      newVertex = heapRemoveMin(Q,distance); // --> get the first vertex
      // printf("newVertex = %d\n",newVertex );
      if (visited[newVertex]==0) // if not be visited, then visit it
      {
        visited[newVertex] = 1;
        u=newVertex; // visit u
        list = mygraph->table[u].outlist; // for the node u
        while(list) // --> get each vertex z adjacent to u such that z is in Q
        {
          z = list->index; // current neighbor z
          if (!visited[z] && distance[u] + 1 < distance[z])
          {
            distance[z] = distance[u] + 1;  
            heapInsert(distance,Q,z);            
          }
          list = list->next;
        }
      } 
    }while(Q[0]!=-1 && n>0);
    heapRemoveMin(Q,distance);
  }

  return distance;

}


int main(int argc,char *argv[])
{
  Graph mygraph;

  read_graph(&mygraph,argv[1]);
  // print_graph(&mygraph);
    
  int *nodeDistance[mygraph.MaxSize];

  double sumDistance = 0;
  int largest = 0;
  int num = 0;
  for (int i = 1; i < mygraph.MaxSize; i++)
  {
    nodeDistance[i] = dijkastraShortestPaths(&mygraph,i);
  }

  for (int i = 1; i < mygraph.MaxSize; i++)
  {
    for (int j = 1; j < mygraph.MaxSize; j++)
    {
      // printf("node %d to node %d has a distance %d.\n",i,j, nodeDistance[i][j] );
      // if (nodeDistance[i][j]>6 && nodeDistance[i][j]!=mygraph.MaxSize)
        // printf("node %d to node %d has a distance larger than 6.\n",i,j );
      if (nodeDistance[i][j]!=mygraph.MaxSize && nodeDistance[i][j]!=0)
      {
        sumDistance += nodeDistance[i][j];
        num++;
      }
      
      if (nodeDistance[i][j]>largest && nodeDistance[i][j]!=mygraph.MaxSize)
        largest = nodeDistance[i][j];
    }
  }

  double averageDistance = sumDistance/num;
  printf("Total distance is %f.\n", sumDistance);
  printf("Average distance is %f.\n", averageDistance);
  printf("Largest distance is %d\n", largest);
  

  return(0);
}

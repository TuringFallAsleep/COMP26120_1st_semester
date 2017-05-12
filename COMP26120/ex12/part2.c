#include "graph.h"

int *distance; //distance from v to u
int *visited;


int haveunvisitedNode(List* list, Graph* mygraph, int v){
  int max = 0;
  while(list){
    if (!visited[list->index] && distance[list->index] == mygraph->MaxSize)
      distance[list->index] = distance[v]+1;
    if(!visited[list->index] 
      && mygraph->table[list->index].outdegree 
         > mygraph->table[max].outdegree)
      max = list->index;
    list = list->next;
  }
  return max;
}


int* heuristicShortestPaths(Graph* mygraph, int v){
  distance = (int *)malloc(sizeof(int)*(mygraph->MaxSize+1));
  visited = (int *)malloc(sizeof(int)*(mygraph->MaxSize+1));
  for (int i = 0; i <= mygraph->MaxSize; i++)
  {
    distance[i] = mygraph->MaxSize;// use mygraph->MaxSize+1 to represent infinite (v to i)
    visited[i] = 0;
  }
  distance[v] = 0;
  visited[v] = 1;

  int maxO;

  while((maxO = haveunvisitedNode(mygraph->table[v].outlist, mygraph,v))) {
    visited[(v = maxO)] = 1;

  }
  return distance;

}


int main(int argc,char *argv[])
{
  Graph mygraph;

  read_graph(&mygraph,argv[1]);
    
  int *nodeDistance[mygraph.MaxSize];

  double sumDistance = 0;
  int largest = 0;
  int nopath = 0;
  int self = 0;
  for (int i = 1; i < mygraph.MaxSize; i++)
  {
    nodeDistance[i] = heuristicShortestPaths(&mygraph,i);
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
      }else{
        nopath++;
      }
      if (nodeDistance[i][j]==0){
        self++;
      }
      
      if (nodeDistance[i][j]>largest && nodeDistance[i][j]!=mygraph.MaxSize)
        largest = nodeDistance[i][j];
    }
  }

  double averageDistance = sumDistance/((mygraph.MaxSize-1)*(mygraph.MaxSize-2)-nopath-self);
  printf("Total distance is %f.\n", sumDistance);
  printf("Average distance is %f.\n", averageDistance);
  printf("Largest distance is %d\n", largest);
  

  return(0);
}

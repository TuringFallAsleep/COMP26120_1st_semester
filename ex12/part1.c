#include "graph.h"

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

int n=0;
void heapInsert(int distance, int *Q)
{
  // printf("in heapInsert\n");
  n++;
  Q[n] = distance;
  int i = n;
  int temp;
  while(i>1 && Q[i/2]>Q[i])
  {
    temp = Q[i/2];
    Q[i/2] = Q[i];
    Q[i] = temp;
    i = i/2;
  }
}

int heapRemoveMin(int *Q)
{
  printf("in heapRemoveMin\n");
  int temp = Q[1];
  int j;
  Q[1] = Q[n];
  n--;
  int i = 1;
  while(i<n)
  {
    if (2*i+1<=n)
    {
      if (Q[i]<=Q[2*i] && Q[i]<=Q[2*i+1])
        return temp;
      else
      {
        if (Q[2*i]<=Q[2*i+1])
          j = 2*i;
        else
          j = 2*i+1;
        int t = Q[i];
        Q[i] = Q[j];
        Q[j] = t;
        i = j;
      }
    }
    else
    {
      if (2*i<=n)
      {
        if (Q[i]>Q[2*i])
        {
          int t = Q[i];
          Q[i] = Q[2*i];
          Q[2*i] = t;
        }
        return temp;
      }
    }
  }
  return temp;
}

int* dijkastraShortestPaths(Graph* mygraph, int v){
  int u;
  int *distance; //distance from v to i
  distance = (int *)malloc(sizeof(int)*mygraph->MaxSize);
  for (int i = 1; i < mygraph->MaxSize; ++i)
  {
    distance[i] = -1;// use -1 to represent infinite (v to i)
    // printf("%d\n", i);
  }
  distance[v] = 0;
  printf("in dij 1\n"); 
  int *Q; // a priority queue that store all vertices using distance[i] as key
  Q = (int *)malloc(sizeof(int)*mygraph->MaxSize);
  for (int i = 1; i < mygraph->MaxSize; ++i)
  {
    Q[i] = distance[i];
  }
  // printf("in dij 2\n");
  while(Q[1]!=-1)
  {
    u = heapRemoveMin(Q); // pull a new vertex u into the cloud
    printf("%d\n", u);
  }

  // List *list = mygraph->table->outlist;
  // int weight=0;
  // while(list) // get each vertex z adjacent to u such that z is in Q
  // {
  //   int z = list->index;
  //   list = list->next;
  //   weight++;
  //   printf("distance[%d] = %d\n",u,distance[u] );
  //   if (distance[u]+ weight < distance[z])
  //   {
  //     distance[z] = distance[u] + weight;
  //     heapInsert(distance[z],Q);
  //   }
  // }
  // printf("in dij 3\n");
  return distance;

}





int main(int argc,char *argv[])
{
  Graph mygraph;

  read_graph(&mygraph,argv[1]);
  // print_graph(&mygraph);
  	

  /* you take it from here */
  int maxOutD = 0;
  int minOutD = mygraph.MaxSize;
  int maxInD = 0;
  int minInD = mygraph.MaxSize;
  int NoMaxOutD = 0;
  int NoMinOutD = 0;
  int NoMaxInD = 0;
  int NoMinInD = 0;
  // int *inDegree = (int *)malloc(sizeof(int)*(mygraph.MaxSize));
  int* inDegree = getInDegree(&mygraph);
   
  for (int i=1;i<mygraph.MaxSize;i++)
  {
  	if(mygraph.table[i].outdegree > maxOutD)
  	{
  		maxOutD = mygraph.table[i].outdegree;
  		NoMaxOutD = i;
  	}

    if(mygraph.table[i].outdegree < minOutD && mygraph.table[i].outdegree > 0)
    {
      minOutD = mygraph.table[i].outdegree;
      NoMinOutD = i;
    }
  		
  	if(inDegree[i]>maxInD)
  	{
  		maxInD = inDegree[i];
  		NoMaxInD = i;
  	}
  		
  	if (inDegree[i]<minInD && inDegree[i]>0)
  	{
  		minInD = inDegree[i];
  		NoMinInD = i;
  	}		
  }

  printf("Node %d with largest out-degree: %d\n", NoMaxOutD,maxOutD);
  printf("Node %d with smallest(non-zero) out-degree: %d\n", NoMinOutD,minOutD);
  printf("Node %d with largest in-degree is %d\n", NoMaxInD,maxInD);
  printf("Node %d with smallest(non-zero) in-degree is %d\n", NoMinInD,minInD);
  int *nodeDistance[mygraph.MaxSize];
  // for (int i = 1; i < mygraph.MaxSize; ++i)
  // {
  //   nodeDistance[i] = (int *)malloc(sizeof(int)*mygraph.MaxSize);
  // }
  double sumDistance = 0;
  int largest = 0;
  // for (int i = 1; i < mygraph.MaxSize; i++)
  // {
    // n = 0;
    nodeDistance[1] = dijkastraShortestPaths(&mygraph,1);
  // }

  // for (int i = 1; i < mygraph.MaxSize; ++i)
  // {
  //   for (int j = 1; j < mygraph.MaxSize; ++i)
  //   {
  //     if (nodeDistance[i][j]>6)
  //       printf("node %d to node %d has a distance larger than 6.\n",i,j );
  //     sumDistance += nodeDistance[i][j];
  //     if (nodeDistance[i][j]>largest)
  //       largest = nodeDistance[i][j];
  //   }
  // }

  // double averageDistance = sumDistance/mygraph.MaxSize;
  // printf("Total distance is %f.\n", sumDistance);
  // printf("Average distance is %f.\n", averageDistance);
  // printf("Largest distance is %d\n", largest);
  

  return(0);
}

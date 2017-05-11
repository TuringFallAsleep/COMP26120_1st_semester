#include "graph.h"

// typedef struct {
//   int index;
//   int distance;
// } Queue;


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
void heapInsert(int *distance, int *Q, int index)
{
  printf("in heapInsert %d\n", index);
  Q[n++] = index;
  int i = n;
  int temp;
  while(i>1 && distance[i/2]>distance[i])
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
  int j;
  printf("in remove %d\n", temp);
  Q[0] = Q[n];
  n--;
  int i = 1;
  while(i<n)
  {
    if (2*i+1<=n)
    {
      if ( distance[i]>0 && distance[i]<=distance[2*i] && distance[i]<=distance[2*i+1])
        return temp;
      else
      {
        if (distance[2*i]>0 && distance[2*i]<=distance[2*i+1])
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
        if (distance[2*i]>0 && distance[i]>distance[2*i])
        {
          int t = distance[i];
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
  int u = v;
  int *distance; //distance from v to u
  distance = (int *)malloc(sizeof(int)*mygraph->MaxSize);
  int *visited;
  visited = (int *)malloc(sizeof(int)*mygraph->MaxSize);
  for (int i = 0; i < mygraph->MaxSize; ++i)
  {
    distance[i] = mygraph->MaxSize;// use -1 to represent infinite (v to i)
    visited[i] = 0;
  }
  distance[v] = 0;



  int *Q; // a priority queue that store all vertices using distance[i] as key
  Q = (int *)malloc(sizeof(int)*mygraph->MaxSize);
  
  for (int i = 0; i < mygraph->MaxSize; ++i)
  {
    Q[i] = -1;
  }

  Q[0] = v;
  n++;

  int newVertex=0;



  while(Q[0]!=-1){
   newVertex = heapRemoveMin(Q,distance);
   if (visited[newVertex]==0)
   {
    visited[newVertex] = 1;
    // pull a new vertex u into the cloud
    printf("u = %d\n", newVertex);
    u=newVertex;
    }
      

    List *list = mygraph->table[u].outlist;
    while(list) // get each vertex z adjacent to u such that z is in Q
    {
      u = newVertex;
      int z = list->index;
      if (distance[u]+ 1 < distance[z])
      {
        distance[z] = distance[u] + 1;
        heapInsert(distance,Q,z);
        printf("distance[%d] = %d\n",z,distance[z]);
      }
      list = list->next;
    }
}
  

  if (n>0 && visited[u]==0)
  {
    visited[0] = 1;
    newVertex = heapRemoveMin(Q,distance); // pull a new vertex u into the cloud
    visited[newVertex] = 1;
    printf("u = %d\n", newVertex);
  }
  

  List *list = mygraph->table[u].outlist;
  while(list) // get each vertex z adjacent to u such that z is in Q
  {
    u = newVertex;
    int z = list->index;
    if (distance[u]+ 1 < distance[z])
    {
      distance[z] = distance[u] + 1;
      heapInsert(distance,Q,z);
      printf("distance[%d] = %d\n",u,distance[u]);
    }
    list = list->next;
  }
  // printf("list->index = %d\n",list->index);
  // for (int i = 0; i < mygraph->MaxSize; ++i)
  // {
  //   //printf("Q[%d] = %d\n",i,Q[i]);
  // }
  
  
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

  double sumDistance = 0;
  int largest = 0;
  for (int i = 1; i < mygraph.MaxSize; i++)
  {
    n = 0;
    nodeDistance[i] = dijkastraShortestPaths(&mygraph,1);
  }

  for (int i = 1; i < mygraph.MaxSize; i++)
  {
    for (int j = 1; j < mygraph.MaxSize; j++)
    {
      printf("node %d to node %d has a distance %d.\n",i,j, nodeDistance[i][j] );
      if (nodeDistance[i][j]>6 && nodeDistance[i][j]!=mygraph.MaxSize)
        printf("node %d to node %d has a distance larger than 6.\n",i,j );
      if (nodeDistance[i][j]!=mygraph.MaxSize)
      {
        sumDistance += nodeDistance[i][j];
      }
      
      if (nodeDistance[i][j]>largest && nodeDistance[i][j]!=mygraph.MaxSize)
        largest = nodeDistance[i][j];
    }
  }

  double averageDistance = sumDistance/(mygraph.MaxSize-1)/(mygraph.MaxSize-2);
  printf("Total distance is %f.\n", sumDistance);
  printf("Average distance is %f.\n", averageDistance);
  printf("Largest distance is %d\n", largest);
  

  return(0);
}

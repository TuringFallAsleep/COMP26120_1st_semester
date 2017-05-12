#include "graph.h"

// typedef struct {
//   int index;
//   int distance;
// } Queue;
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
  printf("insert %d\n", index);
  Q[n++] = index;
  int i = n;
  int temp;
  while(i>1 && distance[(int)i/2]>distance[i])
  {
    temp = Q[(int)i/2];
    Q[(int)i/2] = Q[i];
    Q[i] = temp;
    i = (int)i/2;
  }
}

int heapRemoveMin(int *Q,int *distance)
{
  // printf("in heapRemoveMin\n");
  int temp = Q[0];
  int j;
  printf("remove %d\n", temp);
  Q[0] = Q[n];
  // printf("Q[n] = Q[%d] = %d\n",n,Q[n]);
  n--;
  int i = 0;
  while(i<n)
  {
    if (2*i+1<=n) // this node has two internal children
    {
      if ( distance[i]>0 && distance[i]<=distance[2*i] && distance[i]<=distance[2*i+1])
        return temp;
      else
      {
        if (distance[2*i]>0 && distance[2*i]<=distance[2*i+1])
          j = 2*i;
        if (distance[2*i+1]>0 && distance[2*i]>distance[2*i+1])
          j = 2*i+1;
        int t = Q[i];
        Q[i] = Q[j];
        Q[j] = t;
        i = j;
      }
    }
    else // this node has zero or one internal child
    {
      if (2*i<=n) // has one internal node (the last one)
      {
        if (distance[2*i]>0 && distance[i]>distance[2*i])
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
  int u = v;
  n = 0;
  printf("now source: v = %d\n", v);
  // int *distance; //distance from v to u
  distance = (int *)malloc(sizeof(int)*mygraph->MaxSize);
  // int *visited;
  visited = (int *)malloc(sizeof(int)*mygraph->MaxSize);
  for (int i = 0; i < mygraph->MaxSize; i++)
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
  int noUse;
  List *list;

  heapInsert(distance,Q,z);
  while(Q[0]!=-1 && n > 0){
    do{ 

      // heapInsert(distance,Q,z); // --> insert new nodes  

      newVertex = heapRemoveMin(Q,distance); // --> get the first vertex
      printf("newVertex = %d\n",newVertex );
      if (visited[newVertex]==0) // if not be visited, then visit it
      {
        visited[newVertex] = 1;
        // pull a new vertex u into the cloud
        printf("current visiting u = %d\n", newVertex);
        u=newVertex; // visit u
      } 

      list = mygraph->table[u].outlist; // for the node u
      while(list) // --> get each vertex z adjacent to u such that z is in Q
      {
        z = list->index; // current neighbor z
        if (distance[u] + 1 < distance[z])
        {
          distance[z] = distance[u] + 1;
          if (visited[z]==0) // maybe no need 
          {
            heapInsert(distance,Q,z);
            printf("distance[%d] = %d\n",z,distance[z]);
          }else{
            printf("%d has been visited.1\n",z );
          }
        }else{
          printf("%d has been visited.2\n",z );
          noUse = heapRemoveMin(Q,distance);
        }
        list = list->next;
      }
      for (int i = 0; i < mygraph->MaxSize; ++i)
      {
        if(Q[i]!=-1)
          printf("Q[%d] = %d\n",i,Q[i]);
        // printf("distance[%d] = %d\n",i,distance[i]);
      } 
    }while(Q[0]!=-1 && n>0);
    noUse = heapRemoveMin(Q,distance);
  }

  
  for (int i = 0; i < mygraph->MaxSize; ++i)
  {
    // printf("Q[%d] = %d\n",i,Q[i]);
    printf("distance[%d] = %d\n",i,distance[i]);
  }

  // for (int i = 0; i < mygraph->MaxSize; ++i) // empty the queue
  // {
  //   Q[i] = -1;
  // }
  printf("This is noUse %d\n", noUse);
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
    nodeDistance[i] = dijkastraShortestPaths(&mygraph,i);
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

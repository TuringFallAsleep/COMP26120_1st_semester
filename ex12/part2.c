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

void heuristics(Graph *mygraph){
  List* current;
  int source;

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


  heuristics(&mygraph);

  return(0);
}
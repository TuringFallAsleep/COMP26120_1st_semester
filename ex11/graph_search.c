#include "graph.h"
#include <errno.h>
/* Good luck */





void enqueue(int *queue, int node){
	int i = 1;
	int insertPoint = 1;
	while(queue[i]!=0)
	{
		i++;
		insertPoint = i;
	}
	queue[insertPoint] = node;
}

int dequeue(int* queue,int MaxSize){
	int newQueue[MaxSize];
	int head = queue[1];
	for (int i = 0; i < MaxSize; ++i)
	{
		newQueue[i] = queue[i];
	}
	if (queue[1] == 0)
		return queue[1];
	for (int i = 1; i < MaxSize-1; ++i)
	{
		queue[i] = newQueue[i+1];
	}
	printf("Current node is %d\n", head);
	return head;
}


void BFS (Graph* mygraph, int sNode, int lNode)
{
	int queue[mygraph->MaxSize];//(List*)malloc(sizeof(List)*mygraph->MaxSize*mygraph->MaxSize);
	int set[mygraph->MaxSize];
	int root = sNode;
	int adjacent[mygraph->MaxSize][mygraph->MaxSize];
	int duplicate;
	int resultOutdegree = 0;
	int resultIndex = 1;
	for (int i = 1; i < mygraph->MaxSize; i++)
	{
		queue[i] = 0;
		set[i] = 0;
	}
	set[1] = root;
	enqueue(queue, set[1]);

	while (queue[1]!=0)
	{
		int current = dequeue(queue,mygraph->MaxSize);
		
		if (mygraph->table[current].outdegree == mygraph->table[lNode].outdegree)
		{
			printf("Node %d with smallest(non-zero) out-degree can reach the node %d with largest out-degree: %d.\n",
	 		 sNode,current,mygraph->table[current].outdegree);
			return;
		}
		else if (mygraph->table[current].outdegree > resultOutdegree)
		{
			resultOutdegree = mygraph->table[current].outdegree;
			resultIndex = current;
		}
		List *list = mygraph->table[current].outlist;
		for (int i = 1; i < mygraph->MaxSize; i++)
		{
			while(list)
			{
				adjacent[current][i] = list->index;
				i++;
				list = list->next;
			}
			adjacent[current][i] = 0;
			
		}
		int j = 1;
		while(adjacent[current][j] != 0)
		{
			// printf("in adjacent while loop\n");
			int insertPoint = 1;
			for (int i = 1; i < mygraph->MaxSize; i++)// if adjacent[current][j] is not in set[]
			{											//add adjacent[current][j] to set[]
				if (set[i] != 0)
				{
					insertPoint = i + 1;
				}
				else
					break;
				duplicate = 0;
				if (adjacent[current][j] == set[i])
				{
					duplicate = 1;
					break;
				}
			}
			if (!duplicate)
			{
				set[insertPoint] = adjacent[current][j];
				enqueue(queue,set[insertPoint]);
			}
			j++;
		}
	}
	printf("Node %d with smallest(non-zero) out-degree can reach the node %d with largest out-degree: %d.\n",
	 		 sNode,resultIndex,mygraph->table[resultIndex].outdegree);
}




void DFS (Graph* mygraph, int sNode, int lNode)
{
	return;
}
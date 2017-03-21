#include "graph.h"
#include <errno.h>
/* Good luck */



void queue_add_to_end(List *list)
{
	List *newQueue = (List*)malloc(sizeof(List));
	if (newQueue == NULL)
	{
		fprintf(stderr,"Unable to allocate memory for new node\n");
		exit(-1);
	}

	newQueue->index = list->index;
	newQueue->next = NULL;

	if (list->next == NULL)
	{
		list->next = newQueue;
		printf("Add at begining\n");
	}
	else
	{
		List *current = list;
		while(1)
		{
			if (current->next == NULL)
			{
				printf("Add later\n");
				current->next = newQueue;
				break;
			}
			current = current->next;
		}
	}


	return;
}


void BFS (Graph* mygraph, int sNode, int lNode)
{
	List *queue = NULL;//(List*)malloc(sizeof(List)*mygraph->MaxSize*mygraph->MaxSize);

	List *list = mygraph->table[sNode].outlist;
	queue = list;

	List *largest = mygraph->table[lNode].outlist;
	int maxOutD = mygraph->table[largest->index].outdegree;
	int currentOutD = 0;
	// int step = 0;
	int resultOutD = 0;
	// int resultNode = 0;
	int resultIndex = 0;
	if (mygraph->table[list->index].outdegree == 0)
	{
		printf("Out-degree is 0, error!\n");
		return;
	}

	while(queue)
	{
		currentOutD = mygraph->table[list->index].outdegree;
		if (currentOutD == maxOutD)
		{
			resultIndex = list->index;
			printf("Node %d with smallest(non-zero) out-degree can reach the node %d with largest out-degree: %d.\n",
			 sNode,resultIndex,currentOutD);
			return;
		}
		else
		{
			if (resultOutD < currentOutD)
			{
				resultOutD = currentOutD;
				resultIndex = list->index;
			}
			if (mygraph->table[list->index].outlist)
			{
				queue_add_to_end(mygraph->table[list->index].outlist);
			}
			queue = queue->next;
		}
	}
	printf("The largest out-degree of node which can be reached from the smallest(non-zero) out-degree of all the node is %d.\n",
			resultIndex);
	return;
}




void DFS (Graph* mygraph, int sNode, int lNode)
{
	return;
}
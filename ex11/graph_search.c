#include "graph.h"
#include <errno.h>
/* Good luck */



// void queue_add_to_end(int *head, List *list)
// {
// 	// List *newQueue = (List*)malloc(sizeof(List));
// 	// if (newQueue == NULL)
// 	// {
// 	// 	fprintf(stderr,"Unable to allocate memory for new node\n");
// 	// 	exit(-1);
// 	// }

// 	// newQueue->index = list->index;
// 	// newQueue->next = NULL;

// 	if (queue->next == NULL)
// 	{
// 		queue->next = list;
// 		printf("Add at begining\n");
// 	}
// 	else
// 	{
// 		List *current = queue;
// 		while(current)
// 		{
// 			if (current->next == NULL)
// 			{
// 				printf("Now visit: %d\n", current->index);
// 				current->next = list;
// 				return;
// 			}
// 			current = current->next;
// 		}
// 	}


// 	return;
// }

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
	for (int i = 0; i < MaxSize; ++i)
	{
		newQueue[i] = 0;
	}
	if (queue[1] == 0)
		return queue[1];
	for (int i = 1; i < MaxSize-1; ++i)
	{
		newQueue[i] = queue[i+1];
	}
	return newQueue[1];
}


void BFS (Graph* mygraph, int sNode, int lNode)
{
	int queue[mygraph->MaxSize];//(List*)malloc(sizeof(List)*mygraph->MaxSize*mygraph->MaxSize);
	int set[mygraph->MaxSize];
	int parent[mygraph->MaxSize];
	int root = mygraph->table[sNode].outlist->index;
	int adjacent[mygraph->MaxSize][mygraph->MaxSize];
	int duplicate;
	for (int i = 1; i < mygraph->MaxSize; i++)
	{
		queue[i] = 0;
		set[i] = 0;
		parent[i] = 0;
	}
	parent[root] = 0;
	set[1] = root;
	enqueue(queue, set[1]);

	while (queue[1]!=0)
	{
		int current = dequeue(queue,mygraph->MaxSize);
		if (mygraph->table[current].outlist->index == mygraph->table[lNode].outlist->index)
		{

			printf("Node %d with smallest(non-zero) out-degree can reach the node %d with largest out-degree: %d.\n",
	 		 sNode,current,mygraph->table[current].outdegree);
			return;
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
			set[insertPoint] = adjacent[current][j];
			parent[set[insertPoint]] = current;
			enqueue(queue,set[insertPoint]);
		}
	}

	// int head = list->index;
	
	// List *largest = mygraph->table[lNode].outlist;
	// int maxOutD = mygraph->table[largest->index].outdegree;
	// int currentOutD = 0;
	// // int step = 0;
	// int resultOutD = 0;
	// // int resultNode = 0;
	// int resultIndex = 0;
	// if (mygraph->table[root].outdegree == 0)
	// {
	// 	printf("Out-degree is 0, error!\n");
	// 	return;
	// }

	// //create queue
	// int i = 1;
	
	// while(i < mygraph->MaxSize)
	// {
	// 	// printf("In while i = %d\n",i);
	// 	int duplicate = 0;
	// 	if(i==1)
	// 		queue[i] = sNode;
	// 	 // printf("%d\n", queue[i]);
	// 	List *current;
	// 	if(mygraph->table[queue[i]].outlist)
	// 	{
	// 		current = mygraph->table[queue[i]].outlist;
	// 		printf("current index is %d\n", current->index);
	// 	}
	// 	// else
	// 	// {
	// 	// 	current = mygraph->table[child].outlist;
	// 	// 	printf("child is %d\n", child);
	// 	// }

	// 	int *q;
	// 	while (current)
	// 	{
	// 		// List *l = current->next;
	// 		// while (l)
	// 		// {
	// 		// 	i++;
	// 		// 	queue[i] = l->index;
	// 		// 	l = l->next;
	// 		// }
	// 		for (int j = 1; j < i; j++) // avoid insert a loop of the graph
	// 		{
	// 			// printf("in duplicate loop, i is %d\n", i);
	// 			if (current->index == queue[j])
	// 			{
	// 				duplicate = 1;
	// 				break;
	// 			}	
				
	// 			printf("duplicate is %d\n", duplicate);
	// 		}
	// 		if (!duplicate)
	// 		{
	// 			i++;
	// 			queue[i] = current->index;

	// 			printf("current node is %d i is %d\n", queue[i],i);

	// 		}
			
	// 		current = current->next;
	// 		// printf("Find next\n");	
	// 	}
	// 	q = queue;
	// 	int j = 1;
	// 	while(q[j])
	// 	{
	// 		printf("q is %d\n",q[j] );
	// 		List *c = mygraph->table[q[j]].outlist->next;
	// 		while(c)
	// 		{
	// 			i++;
	// 			queue[i] = c->index;
	// 			c = c->next;
	// 		}
	// 		j++;
	// 	}
	// 	// printf("end\n");
	// 	// break;

	// }

	// for (int i = 1; i < mygraph->MaxSize; i++)
	// {
	// 	if(queue[i]==0)
	// 	{
	// 		printf("\n");
	// 		return;
	// 	}
			
	// 	printf("%d, ", queue[i]);
	// }

	// return;


	// while(queue)
	// {
	// 	currentOutD = mygraph->table[*queue].outdegree;
	// 	if (currentOutD == maxOutD)
	// 	{
	// 		resultIndex = list->index;
	// 		printf("Node %d with smallest(non-zero) out-degree can reach the node %d with largest out-degree: %d.\n",
	// 		 sNode,resultIndex,currentOutD);
	// 		return;
	// 	}
	// 	else
	// 	{
	// 		if (resultOutD < currentOutD)
	// 		{
	// 			resultOutD = currentOutD;
	// 			resultIndex = *queue;
	// 			printf("current index: %d, with out-degree %d. \n",*queue, currentOutD);
	// 		}
	// 		if (list)
	// 		{
	// 			queue_add_to_end(queue,list);
	// 			if(list->next)
	// 				list = list->next;
	// 		}

	// 		pop(queue);
	// 		printf("Current head is: %d\n", *queue);
	// 	}
	// }
	// printf("The largest out-degree of node which can be reached from the smallest(non-zero) out-degree of all the node is %d.\n",
	// 		resultIndex);
	// return;
}




void DFS (Graph* mygraph, int sNode, int lNode)
{
	return;
}
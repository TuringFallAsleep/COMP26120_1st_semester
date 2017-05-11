#include "graph.h"
#include <errno.h>
/* Good luck */
int n=0;
void heapInsert(int distance, int *Q)
{
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

int* dij(Graph* mygraph, int v){
	int u;
	int *distance; //distance from v to i
	distance = (int *)malloc(sizeof(int)*mygraph->MaxSize);
	for (int i = 1; i < mygraph->MaxSize+1; ++i)
	{
		distance[i] = -1;// use -1 to represent infinite (v to i)
	}
	distance[v] = 0; 
	int *Q; // a priority queue that store all vertices using distance[i] as key
	Q = (int *)malloc(sizeof(int)*MaxSize);
	for (int i = 1; i < mygraph->MaxSize+1; ++i)
	{
		Q[i] = distance[i];
	}
	while(Q[1]!=-1)
	{
		u = heapRemoveMin(Q); // pull a new vertex u into the cloud
	}

	List list = graph->table->outlist;
	int weight=0;
	while(list) // get each vertex z adjacent to u such that z is in Q
	{
		int z = list->index;
		list = list->next;
		weight++;
		if (distance[u]+ weight < distance[z])
		{
			distance[z] = distance[u] + weight;
			heapInsert(distance[z],Q);
		}
	}
	return distance;

}
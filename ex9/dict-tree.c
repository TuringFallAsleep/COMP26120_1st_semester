#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct node *tree_ptr;
struct node 
{
  Key_Type word; // only data is the key itself
  // const char *word;
  tree_ptr left, right, parent;
  // add anything else that you need
  int count;
};

struct table 
{
  tree_ptr head; // points to the head of the tree
  // add anything else that you need
  tree_ptr current;
};

int count_insert = 0;
int count_find = 0;

tree_ptr talloc(void)//make a tree node, allocate space
{
	return (tree_ptr)malloc(sizeof(struct node));
}

Table initialize_table(/*ignore parameter*/) 
{
	Table t = (Table)malloc(sizeof(struct table));
	if (t == NULL) abort();
	t->head = NULL;
	printf("Table has been initialized.\n");
	return t;
}


tree_ptr insert_node(Key_Type element, tree_ptr p)
{
	int compare_value;
	if (p == NULL)
	{
		p = talloc();
		p->word = strdup(element);
		p->count = 1;
		p->left = p->right = NULL;
	}else if ((compare_value = strcmp(element, p->word)) == 0)
	{
		p->count++;
		// printf("%d\n", p->count);
	}
	else if (compare_value < 0)
		p->left = insert_node(element,p->left);
	else
		p->right = insert_node(element,p->right);
	return p;
}


Table insert(Key_Type element, Table t) 
{
	if (mode == 0)
	{
		count_insert++;
		t->head = insert_node(element, t->head);
		return t;
	}
	if (mode == 1)
	{
		count_insert++;
		t->head = insert_node(element, t->head);

		return t;
	}else
	{
		printf("Please choose mode!\n");
		return 0;
	}
	
}

Boolean find_wrong(Key_Type element, tree_ptr current)
{
	if (!element || !current)
		return FALSE;
	int compare_value = strcmp(element,current->word);
	if (compare_value == 0)
		return TRUE;
	else if (compare_value < 0)
		return find_wrong (element, current->left);
	else
		return find_wrong (element, current->right);
}


Boolean find(Key_Type element, Table t) // tree_node *dictionary, char *word
{
	count_find++;
	t->current = t->head;
	return find_wrong(element,t->current);
}

void print_tree(tree_ptr tree)
{
	if (tree != NULL)
	{
		print_tree(tree->left);
		printf("%d  %s\n",tree->count,tree->word);
		print_tree(tree->right);
	}else
	return;
}

void print_table(Table t) 
{
	print_tree(t->head);
}

int find_Height(tree_ptr isNode)
{
	if (!isNode)
	{
		return -1;
	}
	int leftH = find_Height(isNode->left);
	int rightH = find_Height(isNode->right);

	if (leftH > rightH)
	{
		return leftH + 1;
	}else
	{
		return rightH + 1; 
	}

}
void print_stats (Table t) 
{
	int height;
	height = find_Height(t->head);
	printf("Height of tree is %d.\n", height);
	printf("Insert time is %d.\n", count_insert);
	printf("Find time is %d.\n", count_find);
}


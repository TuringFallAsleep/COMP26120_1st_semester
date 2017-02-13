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
  Key_Type element; // only data is the key itself
  // const char *word;
  tree_ptr left, right;
  // add anything else that you need
  int count;
};

struct table 
{
  tree_ptr head; // points to the head of the tree
  // add anything else that you need
  tree_ptr current;
};

Table initialize_table(/*ignore parameter*/) 
{
	Table t = (Table)malloc(sizeof(Table));
	if (t ==NULL) abort();
	// printf("in initialize_table\n");
	return t;
}

Table insert(Key_Type element, Table t) 
{
	printf("in insert head\n");
	printf("first element is %s\n", element);
	if (t->head->element == NULL)
	{
		
		t->head->element = strdup(element);
		printf("head strdup\n");
		t->head->left = NULL;
		t->head->right = NULL;
		t->head->count = 1;
		t->current = t->head;
		printf("head of insert!!!!\n");
		return t;
	}
	printf("in insert\n");
	int compare_value = strcmp(element, t->current->element);
	if (compare_value == 0)
	{
		printf("compare_value == 0\n");
		return t;
	}

	if (compare_value < 0)
	{
		printf("compare_value < 0\n");
		if (t->current->left != NULL)
		{
			t->current = t->current->left;
			insert(element,t);
		}
		else
		{
			// tree_ptr *new_node = (tree_ptr *)malloc(sizeof(tree_ptr));
			Table new_t = (Table)malloc(sizeof(Table));
			new_t->head->element = strdup(element);
			new_t->head->left = NULL;
			new_t->head->right = NULL;
			t->current = t->current->left;
			t->current = t->head;
			printf("tail of insert!!!\n");
			return t;
		}
	}
	else
	{
		printf("compare_value > 0\n");
		if (t->current->right != NULL)
		{
			t->current = t->current->right;
			insert(element,t);
		}
		else
		{
			Table new_t = (Table)malloc(sizeof(Table));
			new_t->head->element = strdup(element);
			new_t->head->left = NULL;
			new_t->head->right = NULL;
			t->current = t->current->right;
			t->current = new_t->head;
			printf("tail of insert!!!\n");
			return t;
		}
	}
	return t;
}

Boolean find(Key_Type element, Table t) 
{
}

void print_table(Table t) 
{
	// if (t != NULL)
	// {
	// 	print_table(t->current->left);
	// 	printf("%s\n",t->current->element);
	// 	print_table(t->current->right);
	// }
	printf("%s!!!!!!!!!!!!!!!!!\n", t->head->element);
}

void print_stats (Table t) 
{
}
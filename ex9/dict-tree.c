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
};

struct table 
{
  tree_ptr head; // points to the head of the tree
  // add anything else that you need
  tree_ptr current;
};

Table initialize_table(/*ignore parameter*/) 
{
	// struct node *head = (struct node*)malloc(sizeof(struct node));
	tree_ptr *head = (tree_ptr*)malloc(sizeof(tree_ptr));
	head = NULL;
}

Table insert(Key_Type element, Table t) 
{
	if (t == NULL)
	{
		t->head->element = strdup(element);
		t->head->left = NULL;
		t->head->right = NULL;
		t->current = t->head;
		return t;
	}
	int compare_value = strcmp(element, t->current->element);
	if (compare_value == 0)
	{
		return t;
	}

	if (compare_value < 0)
	{
		if (t->current->left != NULL)
		{
			t->current = t->current->left;
			insert(element,t);
		}
		else
		{
			tree_ptr *new_node = (tree_ptr *)malloc(sizeof(tree_ptr));
			new_node->element = strdup(element);
			new_node->left = NULL;
			new_node->right = NULL;
			t->current->left = new_node;
			t->current = t->head;
			return t;
		}
	}
	else
	{
		if (t->current->right != NULL)
		{
			t->current = t->current->right;
			insert(element,t);
		}
		else
		{
			tree_ptr *new_node = (node *)malloc(sizeof(tree_ptr));
			new_node->element = strdup(element);
			new_node->left = NULL;
			new_node->right = NULL;
			t->current->right = new_node;
			t->current = t->head;
			return t;
		}
	}
}

Boolean find(Key_Type, Table) 
{
}

void print_table(Table) 
{
}

void print_stats (Table) 
{
}

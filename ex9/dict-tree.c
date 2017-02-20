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

tree_ptr talloc(void)//make a tree node, allocate space
{
	return (tree_ptr)malloc(sizeof(tree_ptr));
}

// Key_Type strdup1(char *s)
// {
// 	Key_Type p;
// 	p = (char *)malloc(strlen(s)+1); // +1 for '\0'
// 	if (p != NULL)
// 		strcpy(p,s);
// 	return p;
// }

Table initialize_table(/*ignore parameter*/) 
{
	Table t = (Table)malloc(sizeof(Table));
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
		// p->word = NULL;
		char *c = strdup(element);//if no this, word will get nothing, do not know why
		c = element;
		char *d = strdup(element);//if no this, word will get nothing, do not know why
		d = element;
		p->word = strdup(element);
		p->count = 1;
		p->left = p->right = NULL;

		// printf("insert word is %s\n", p->word);
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
	// printf("current element is %s\n", element);
	// if (t->head == NULL)
	// {
	// 	tree_ptr tree = talloc();
	// 	t->head = tree;
	// 	// char *c = strdup(element);//if no this, word will get nothing, do not know why
	// 	// c = element;// to eliminate warning.
	// 	// printf("%s\n", c);
	// 	tree->word = strdup(element);
	// 	tree->left = NULL;
	// 	tree->right = NULL;
	// 	t->current = t->head;
	// 	// printf("%s\n", t->current->word);
	// 	return t;
	// }
	char *c = strdup(element);//if no this, word will get nothing, do not know why
	c = element;// to eliminate warning.
	// printf("c is %s\n", c);
	t->head = insert_node(element, t->head);
	// printf("in insert\n");


	// int compare_value = strcmp(element, t->current->word);
	// if (compare_value == 0)
	// {
	// 	printf("compare_value == 0\n");
	// 	return t;
	// }

	// if (compare_value < 0)
	// {
	// 	printf("compare_value < 0\n");
	// 	if (t->current->left != NULL)
	// 	{
	// 		t->current = t->current->left;
	// 		insert(element,t);
	// 	}
	// 	else
	// 	{
	// 		tree_ptr new_node = talloc();
	// 		new_node->word = strdup(element);
	// 		printf("%s\n", new_node->word);
	// 		new_node->left = NULL;
	// 		new_node->right = NULL;
	// 		t->current = t->current->left;
	// 		t->current = new_node;
	// 		return t;
	// 	}
	// }
	// else
	// {
	// 	printf("compare_value > 0\n");
	// 	if (t->current->right != NULL)
	// 	{
	// 		t->current = t->current->right;
	// 		insert(element,t);
	// 	}
	// 	else
	// 	{
	// 		tree_ptr new_node = talloc();
	// 		new_node->word = strdup(element);
	// 		printf("%s\n", new_node->word);
	// 		new_node->left = NULL;
	// 		new_node->right = NULL;
	// 		t->current = t->current->right;
	// 		t->current = new_node;
	// 		return t;
	// 	}
	// }
	return t;
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
	// if (!tree)
	// 	return;
	// if (tree->left)
	// 	print_tree (tree->left);
	// printf("%d  %s\n",tree->count,tree->word);
	// if (tree->right)
	// 	print_tree (tree->right);
}

void print_table(Table t) 
{
	print_tree(t->head);
}

void print_tree_stats(tree_ptr tree)
{
	// if(tr)
}
void print_stats (Table t) 
{
	print_tree_stats(t->head);
}
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

// Rotate
tree_ptr rightRotate(tree_ptr z)
{
	tree_ptr y = z->left;
	tree_ptr T3 = y->right;

	y->right = z;
	z->left = T3;

	return y;
}

tree_ptr leftRotate(tree_ptr x)
{
	tree_ptr y = x->right;
	tree_ptr T2 = y->left;

	y->left = x;
	x->right = T2;

	return y;
}

int getBalance(tree_ptr p)
{
	if (p == NULL)
		return 0;
	return find_Height(p->left) - find_Height(p->right);
}




tree_ptr insert_node_BST(Key_Type element, tree_ptr p)
{
	count_insert++;
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
		p->left = insert_node_BST(element,p->left);
	else
		p->right = insert_node_BST(element,p->right);
	return p;
}

tree_ptr insert_node_AVL(Key_Type element, tree_ptr p)
{
	count_insert++;
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
		p->left = insert_node_AVL(element,p->left);
	else
		p->right = insert_node_AVL(element,p->right);
	

	int balance = getBalance(p);

	// left left case
	if (balance > 1 && ((compare_value = strcmp(element, p->left->word)) < 0))
		return rightRotate(p);
	// right right case
	if (balance < -1 && ((compare_value = strcmp(element, p->right->word)) > 0))
		return leftRotate(p);
	// left right case
	if (balance > 1 && ((compare_value = strcmp(element, p->left->word)) > 0))
	{
		p->left = leftRotate(p->left);
		return rightRotate(p);
	}
	// right left case
	if (balance < -1 && ((compare_value = strcmp(element, p->right->word)) < 0))
	{
		p->right = rightRotate(p->right);
		return leftRotate(p);
	}

	return p;
}


Table insert(Key_Type element, Table t) 
{
	if (mode == 0)
	{		
		t->head = insert_node_BST(element, t->head);
		return t;
	}
	if (mode == 1)
	{
		t->head = insert_node_AVL(element, t->head);
		return t;
	}else
	{
		printf("Please choose mode!\n");
		return 0;
	}
	
}

Boolean find_wrong(Key_Type element, tree_ptr current)
{
	count_find++;
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
}

void print_table(Table t) 
{
	print_tree(t->head);
}


void print_stats (Table t) 
{
	int height;
	height = find_Height(t->head);
	printf("Height of tree is %d.\n", height);
	printf("Insert time is %d.\n", count_insert);
	printf("Find time is %d.\n", count_find);
}


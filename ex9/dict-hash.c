#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct 
{ // hash-table entry
  Key_Type element; // only data is the key itself
  enum {empty, in_use, deleted} state;
} cell;

typedef unsigned int Table_size; // type for size-of or index-into hash table

struct table 
{
  cell *cells; Table_size table_size; // cell cells [table_size];
  Table_size num_entries; // number of cells in_use
  // add anything else that you need
  Table_size num_duplicate;
  Table_size num_collision;
};

int count_insert = 0;
int count_find = 0;

Table initialize_table (Table_size size) 
{
	Table_size i;
	Table t = (Table)malloc(sizeof(struct table));
	if (t == NULL) abort();
	t->cells = (cell*)calloc(size,sizeof(cell));
	for (i=0;i<size;i++)
	{
		t->cells[i].state = empty;
		t->cells[i].element = NULL;
	}
	t->num_entries = 0;
	t->num_collision = 0;
	t->num_duplicate = 0;
	t->table_size = size;
	// printf("Table has been initialized.\n");
	return t;
}

unsigned int hashCode(void *element, int len, Table t)
{
	Table_size i;
	unsigned char *p = element;
	unsigned int hash = 0;
	for (i=len; i>0; i--)
	{
		hash = p[i]*(37^(len-1))+hash;
	}
	return hash % t->table_size;//modify
}

cell insert_cell(Key_Type element)
{
	cell *c = (cell*)malloc(sizeof(cell));
	c->element = strdup(element);
	c->state = in_use;
	return *c;
}

Table_size find_a_next_nearest_prime_number(Table_size n)
{
	Table_size i;
	// Boolean isPrime = TRUE;

	while(1)
	{
		for(i=2; i<=n/2+1; i++)
    	{
        // condition for nonprime number
        	if(n%i==0)
        	{
           		// isPrime = FALSE;
           		break;
       		}
    	}
    	if (i > n/2)
    	{
    		// isPrime = TRUE;
    		break;
    	}
    	n++;
	}
    
    return n;
}

Table rehashing(Table old_table)
{
	// printf("Rehashing!!!\n");
	Table_size old_table_size = old_table->table_size;
	Table_size new_table_size = find_a_next_nearest_prime_number(2*old_table->table_size);
	// printf("New table size is %d\n", new_table_size);
	Table new_table = initialize_table(new_table_size);
	new_table->num_duplicate = old_table->num_duplicate;
	new_table->num_collision = old_table->num_collision;
	new_table->num_entries = old_table->num_entries;
	for (int i = 0; i < old_table_size; ++i)
	{
		if (old_table->cells[i].state == in_use)
		{
			unsigned int hash_code = hashCode(old_table->cells[i].element,strlen(old_table->cells[i].element),new_table);
			
			if (new_table->cells[hash_code].state == empty)//t->cells[t->table_size].element == NULL
			{	
				new_table->cells[hash_code] = insert_cell(old_table->cells[i].element);
			}else
			{
				Table_size j = 0;
				Table_size q = find_a_next_nearest_prime_number(new_table->table_size/2);
				Table_size h = 0;
				while(1)
				{
					new_table->num_collision++;
					if (mode == 0)
					{
						hash_code++;
						hash_code %= new_table->table_size;
					}
					if (mode == 1)
					{
						new_table->num_collision++;
   						j++;
						hash_code = hash_code + j*j;
						hash_code %= new_table->table_size;
					}
					if (mode == 2)
					{
						new_table->num_collision++;
   						j++;
   						h = q - (hash_code % q);
   						hash_code++;
						hash_code = hash_code + j*h;
						hash_code %= new_table->table_size;/* code */
					}
					



					if (new_table->cells[hash_code].state == empty)
					{
						new_table->cells[hash_code] = insert_cell(old_table->cells[i].element);
						break;
					}
					if (hash_code >= new_table->table_size)
					{
						new_table = rehashing(new_table);
						return new_table;
					}
				}
				
			}

			
			// printf("Rehashing. New hash code is %d, element is %s\n", hash_code, new_table->cells[hash_code].element);
		}
	}
	free(old_table);
	return new_table;
}

Table insert (Key_Type element, Table t) 
{
	t->num_entries++;
	unsigned int hash_code = hashCode(element,strlen(element),t);
	// printf("Current element is %s, with hash code %d\n", element, hash_code);
	if (mode == 0)
	{
		while(1)
		{
			if (t->cells[hash_code].state == empty && count_insert < t->table_size-1)//t->cells[t->table_size].element == NULL
			{
				count_insert++;
				
				// printf("count is %d\n", count_insert);

				t->cells[hash_code] = insert_cell(element);

				// printf("Insert element %s\n count_insert is %d\n", t->cells[hash_code].element,count_insert);
				return t;
			}
			if (t->cells[hash_code].state != empty && strcmp(element,t->cells[hash_code].element) == 0)// if element is already in hash table
					{
						t->num_duplicate++;
						return t;
					}
			// printf("count is %d\n", count_insert);
			if (count_insert >= t->table_size-1)// need rehashing   hash_code % t->table_size >= t->table_size-1
			{
				// printf("prepared for rehashing count_insert is %d\n", count_insert);
				t = rehashing(t);
				t = insert(element,t);
				t->num_entries--;
				return t;
			}
			t->num_collision++;
			hash_code++;
			hash_code %= t->table_size;	
			// printf("hash_code++ is %d\n",hash_code);	
		}
	}else if (mode == 1)
	{
		int j = 0;
		while(1)
		{
			if (t->cells[hash_code].state == empty && count_insert < (t->table_size/2))//t->cells[t->table_size].element == NULL
			{
				count_insert++;
				t->cells[hash_code] = insert_cell(element);
				return t;
			}
			if (t->cells[hash_code].state != empty && strcmp(element,t->cells[hash_code].element) == 0)// if element is already in hash table
					{
						t->num_duplicate++;
						return t;
					}
			if (count_insert >= (t->table_size/2))//need rehashing   hash_code % t->table_size >= t->table_size-1
			{
				t = rehashing(t);
				t = insert(element,t);
				t->num_entries--;
				return t;
			}
			t->num_collision++;
   			j++;
			hash_code = hash_code + j*j;
			hash_code %= t->table_size;
			// printf("new hash_code is %d\n",hash_code);	
		}
	}else if (mode == 2)
	{
		Table_size j = 0;
		Table_size q = find_a_next_nearest_prime_number(t->table_size/2);
		Table_size h = 0;
		while(1)
		{
			if (t->cells[hash_code].state == empty && (float)count_insert/((float)t->table_size) < 0.319)//t->cells[t->table_size].element == NULL
			{
				count_insert++;
				t->cells[hash_code] = insert_cell(element);
				return t;
			}
			if (t->cells[hash_code].state != empty && strcmp(element,t->cells[hash_code].element) == 0)// if element is already in hash table
					{
						t->num_duplicate++;
						return t;
					}
			if ((float)count_insert/((float)t->table_size) >= 0.319)//need rehashing   hash_code % t->table_size >= t->table_size-1
			{
				t = rehashing(t);
				t = insert(element,t);
				t->num_entries--;
				return t;
			}
			t->num_collision++;
   			j++;
   			h = q - (hash_code % q);
   			hash_code++;
			hash_code = hash_code + j*h;
			hash_code %= t->table_size;
			// printf("new hash_code is %d\n",hash_code);
		}
	}else
	{
		printf("Please choose mode!\n");
		return 0;
	}
}

Boolean find (Key_Type element, Table t) 
{
	unsigned int hash_code = hashCode(element,strlen(element),t);
		//move in array until an empty or deleted cell
	if (mode == 0)
	{
		if (t->cells[hash_code].state == in_use)
		{
			while(1)
			{
				count_find++;
				if (strcmp(element,t->cells[hash_code].element) == 0)
				{
					return TRUE;
				}else
				{
					hash_code++;
				}
				if (hash_code > t->table_size || t->cells[hash_code].state == empty )
				{
					return FALSE;
				}

			}
		}
	}
	if (mode == 1)
	{
		int j = 0;
		if (t->cells[hash_code].state == in_use)
		{
			while(1)
			{
				count_find++;
				if (strcmp(element,t->cells[hash_code].element) == 0)
				{
					return TRUE;
				}else
				{
					j++;
					hash_code = hash_code + j*j;
				}
				if (hash_code > t->table_size || t->cells[hash_code].state == empty )
				{
					return FALSE;
				}

			}
		}
	}
	if (mode == 2)
	{	
		Table_size j = 0;
		Table_size q = find_a_next_nearest_prime_number(t->table_size/2);
		Table_size h = 0;
		if (t->cells[hash_code].state == in_use)
		{
			while(1)
			{
				count_find++;
				if (strcmp(element,t->cells[hash_code].element) == 0)
				{
					return TRUE;
				}else
				{
					j++;
   					h = q - (hash_code % q);
   					hash_code++;
					hash_code = hash_code + j*h;
					hash_code %= t->table_size;
				}
				if (hash_code > t->table_size || t->cells[hash_code].state == empty )
				{
					return FALSE;
				}

			}
		}
	}
	return FALSE;
}

void print_table (Table t) 
{
	Table_size i;
	for(i = 0; i<t->table_size; i++) 
	{
      if(t->cells[i].element != NULL)
        printf("%s\n",t->cells[i].element);
      	
    }
}

void print_stats (Table t) 
{
	printf("Entry is %d\n", t->num_entries);
	printf("Collision is %d\n", t->num_collision);
	printf("Duplicate is %d\n", t->num_duplicate);
	printf("Insert time is %d.\n", count_insert);
	printf("Find time is %d.\n", count_find);
	printf("Hash table size is %d\n", t->table_size);
}

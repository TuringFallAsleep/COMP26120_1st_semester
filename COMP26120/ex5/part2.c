#include <stdio.h>
#include <stdlib.h>

/* these arrays are just used to give the parameters to 'insert',
 to create the 'people' array
 */

#define HOW_MANY 7
char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
    "Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};

/* declare your struct for a person here */
struct PERSON {
    char *name;
    int age;
    struct PERSON *next;
};



/*part2*/
static struct PERSON* insert_end(struct PERSON *list, char *name, int age){
    struct PERSON* ptr = (struct PERSON*)malloc(sizeof(struct PERSON));
    if(ptr == NULL) abort();
    struct PERSON* current;
    ptr->name = name;
    ptr->age = age;
    current = list;
    if(list == NULL){
        ptr->next = list;
        list = ptr;
        return list;
    }else{
        while (current->next != NULL){
            current = current->next;
        }
        ptr->next = current->next;
        current->next = ptr;
        current = ptr;
        return list;
    }
}

int main(int argc, char **argv)
{
    struct PERSON *people = NULL;
    
    for (int i=0; i < HOW_MANY; i++)
    {
        // people = insert_start (people, names[i], ages[i]);
        people = insert_end (people, names[i], ages[i]);
    }
    
    /* insert_start*/
    while (people != NULL){
        printf("%s, %d\n",people -> name, people -> age );
       free (people);
        people = people -> next;
    }
    
    
    return 0;
}

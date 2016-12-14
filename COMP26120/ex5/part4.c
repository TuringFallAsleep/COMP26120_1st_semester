#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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




/*part3*/
// static struct PERSON* compare_people(struct PERSON *one, struct PERSON *two){

// }
int compare_people_by_name(struct PERSON *one, struct PERSON *two){
    int judge = 0;
    judge = strcmp(one->name,two->name);
    return judge;
}
int compare_people_by_age(struct PERSON *one, struct PERSON *two){
    int judge = 0;
    judge = one->age - two->age;
    return judge;
}

static struct PERSON* insert_sorted(struct PERSON *list, char *name, int age,int (*compare_people)(struct PERSON*, struct PERSON*)){
    int judge1 = 0;
    int judge2 = 0;
    struct PERSON* ptr = (struct PERSON*)malloc(sizeof(struct PERSON));
    struct PERSON* current;
    current = list;
    if(ptr == NULL) abort();
    ptr->name = name;
    ptr->age = age;
    if(list != NULL){
        judge1  = compare_people(ptr,current);
    }
    if (list == NULL || judge1<0){
        ptr->next = list;
        list = ptr;
        return list;
    }
    if(list != NULL || judge1>0){
        while(current->next != NULL){
            judge1 = compare_people(ptr,current);
            judge2 = compare_people(ptr,current->next);
            if (judge1>=0 &&judge2<0){
                ptr->next = current->next;
                current->next = ptr;
                return list;
            }else{
                current = current->next;
            }
        }
        ptr->next = NULL;
        current->next = ptr;
        current = ptr;
        return list;
    }
    return list;
}

int main(int argc, char **argv)
{
    struct PERSON *people = NULL;
    
    for (int i=0; i < HOW_MANY; i++)
    {
        // people = insert_start (people, names[i], ages[i]);
        people = insert_sorted (people, names[i], ages[i],compare_people_by_name);
        // people = insert_sorted (people, names[i], ages[i],compare_people_by_age);
    }
    
    /* insert_start*/
    while (people != NULL){
        printf("%s, %d\n",people -> name, people -> age );
       free (people);
        people = people -> next;
    }
    
    
    return 0;
}
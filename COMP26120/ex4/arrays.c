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
};
// struct PERSON people[HOW_MANY];//part 1
struct PERSON *people[HOW_MANY];// part 2&3&4


/* part 1 */
// static void insert(struct PERSON people2[HOW_MANY], char *name, int age) 
// {
//   static int nextinsert = 0;
//   people2[nextinsert].name = name;
//   people2[nextinsert].age = age;
//   nextinsert++;

//   /* put name and age into the next free place in the array parameter here */
//   /* modify nextfreeplace here */
  
// }

/* part 2&3 */
// static void insert(struct PERSON *people2[HOW_MANY], char *name, int age){
//   static int nextinsert = 0;
//   people2[nextinsert] = (struct PERSON*)malloc(sizeof(struct PERSON));
//   people2[nextinsert]->name = name;
//   people2[nextinsert]->age = age;
//   nextinsert++;   
// }

/* part 4 */
static void insert(struct PERSON *people2[HOW_MANY], char *name, int age, insubmit-t *nextinsert){
  people2[*nextinsert] = (struct PERSON*)malloc(sizeof(struct PERSON));
  people2[*nextinsert]->name = name;
  people2[*nextinsert]->age = age;
  (*nextinsert)++;   
}

int main(int argc, char **argv) 
{
  /* part 1 */
  // for (int i=0; i< HOW_MANY; i++){
  //   insert (people, names[i], ages[i]);
  // }
  // for (int i=0; i< HOW_MANY; i++){
  //   printf("%s, %d\n",people[i].name, people[i].age );
  // }

  /* part 2&3 */
  // for (int i=0; i< HOW_MANY; i++){
  //   insert (people, names[i], ages[i]);
  // }
  // for (int i=0; i< HOW_MANY; i++){
  //   printf("%s, %d\n",people[i]->name, people[i]->age );
  // }

  /* part 4 */
  int nextinsert = 0;
  /* declare the people array here */

  for (int i=0; i < HOW_MANY; i++) 
  {
    insert (people, names[i], ages[i], &nextinsert);// It is good for threads
  }

  /* print the people array here*/
  for (int i=0; i< HOW_MANY; i++){
    printf("%s, %d\n",people[i]->name, people[i]->age );
    // printf("%p\n", people[i]);
  }

  /* part 3&4 */
  for (int i=0; i<HOW_MANY; i++){
    free(people[i]);
    // printf("%s, %d\n",people[i]->name, people[i]->age );
  }

  return 0;
}

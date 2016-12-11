// #include <stdio.h>
// #include <stdlib.h>
// /* these arrays are just used to give the parameters to 'insert',
//    to create the 'people' array 
// */

// #define HOW_MANY 7
// char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
// 		      "Harriet"};
// int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};

// /* declare your struct for a person here */
// struct PERSON {
//   char *name;
//   int age;
//   struct PERSON *next;
// };

// /*part1*/
// static struct PERSON* insert_start(struct PERSON *people2, char *name, int age){
//   struct PERSON* people_new = (struct PERSON*)malloc(sizeof(struct PERSON));
//   if (people_new == NULL) abort();
//   people_new -> name = name;
//   people_new -> age = age;
// /*set the new person's "next" link to point to the (start of the) current list*/
//   people_new -> next = people2;
// /*return the (start of the) new list i.e. a pointer to the new person*/
//   return(people_new);   
// }

// int main(int argc, char **argv) 
// {
//   struct PERSON *people = NULL;
  
//   for (int i=0; i < HOW_MANY; i++) 
//   {
//     people = insert_start (people, names[i], ages[i]);
//     // people = insert_end (people, names[i], ages[i]);

//   }

//   /* insert_start*/
// while (people != NULL){
//   printf("%s, %d\n",people -> name, people -> age );
//   free(people);
//   people = people -> next;
// }

//   return 0;
// }

// /*===============part2=============*/

// #include <stdio.h>
// #include <stdlib.h>

// /* these arrays are just used to give the parameters to 'insert',
//  to create the 'people' array
//  */

// #define HOW_MANY 7
// char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
//     "Harriet"};
// int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};

// /* declare your struct for a person here */
// struct PERSON {
//     char *name;
//     int age;
//     struct PERSON *next;
// };



// /*part2*/
// static struct PERSON* insert_end(struct PERSON *list, char *name, int age){
//     struct PERSON* ptr = (struct PERSON*)malloc(sizeof(struct PERSON));
//     if(ptr == NULL) abort();
//     struct PERSON* current;
//     ptr->name = name;
//     ptr->age = age;
//     current = list;
//     if(list == NULL){
//         ptr->next = list;
//         list = ptr;
//         return list;
//     }else{
//         while (current->next != NULL){
//             current = current->next;
//         }
//         ptr->next = current->next;
//         current->next = ptr;
//         current = ptr;
//         return list;
//     }
// }

// int main(int argc, char **argv)
// {
//     struct PERSON *people = NULL;
    
//     for (int i=0; i < HOW_MANY; i++)
//     {
//         // people = insert_start (people, names[i], ages[i]);
//         people = insert_end (people, names[i], ages[i]);
//     }
    
//     /* insert_start*/
//     while (people != NULL){
//         printf("%s, %d\n",people -> name, people -> age );
//        free (people);
//         people = people -> next;
//     }
    
    
//     return 0;
// }

// /*============part3=============*/

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// /* these arrays are just used to give the parameters to 'insert',
//  to create the 'people' array
//  */

// #define HOW_MANY 7
// char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
//     "Harriet"};
// int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};

// /* declare your struct for a person here */
// struct PERSON {
//     char *name;
//     int age;
//     struct PERSON *next;
// };

// /*part3*/
// int compare_people(struct PERSON *one, struct PERSON *two){
//     int judge = 0;
//     judge = strcmp(one->name,two->name);
//     return judge;
// }

// static struct PERSON* insert_sorted(struct PERSON *list, char *name, int age){
//     int judge1 = 0;
//     int judge2 = 0;
//     struct PERSON* ptr = (struct PERSON*)malloc(sizeof(struct PERSON));
//     struct PERSON* current;
//     current = list;
//     if(ptr == NULL) abort();
//     ptr->name = name;
//     ptr->age = age;
//     if(list != NULL){
//         judge1  = compare_people(ptr,current);
//     }
//     if (list == NULL || judge1<0){
//         ptr->next = list;
//         list = ptr;
//         return list;
//     }
//     if(list != NULL || judge1>0){
//         while(current->next != NULL){
//             judge1 = compare_people(ptr,current);
//             judge2 = compare_people(ptr,current->next);
//             if (judge1>0 &&judge2<0){
//                 ptr->next = current->next;
//                 current->next = ptr;
//                 return list;
//             }else{
//                 current = current->next;
//             }
//         }
//         ptr->next = NULL;
//         current->next = ptr;
//         current = ptr;
//         return list;
//     }
//     return list;
// }
// int main(int argc, char **argv)
// {
//     struct PERSON *people = NULL;   
//     for (int i=0; i < HOW_MANY; i++)
//     {
//         // people = insert_start (people, names[i], ages[i]);
//         people = insert_sorted (people, names[i], ages[i]);
//     }
//     /* insert_start*/
//     while (people != NULL){
//         printf("%s, %d\n",people -> name, people -> age );
//        free (people);
//         people = people -> next;
//     }    
//     return 0;
// }

// /*=========part4=========*/
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// /* these arrays are just used to give the parameters to 'insert',
//  to create the 'people' array
//  */

// #define HOW_MANY 7
// char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
//     "Harriet"};
// int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};

// /* declare your struct for a person here */
// struct PERSON {
//     char *name;
//     int age;
//     struct PERSON *next;
// };




// /*part4*/
// // static struct PERSON* compare_people(struct PERSON *one, struct PERSON *two){

// // }
// int compare_people_by_name(struct PERSON *one, struct PERSON *two){
//     int judge = 0;
//     judge = strcmp(one->name,two->name);
//     return judge;
// }
// int compare_people_by_age(struct PERSON *one, struct PERSON *two){
//     int judge = 0;
//     judge = one->age - two->age;
//     return judge;
// }

// static struct PERSON* insert_sorted(struct PERSON *list, char *name, int age,int (*compare_people)(struct PERSON*, struct PERSON*)){
//     int judge1 = 0;
//     int judge2 = 0;
//     struct PERSON* ptr = (struct PERSON*)malloc(sizeof(struct PERSON));
//     struct PERSON* current;
//     current = list;
//     if(ptr == NULL) abort();
//     ptr->name = name;
//     ptr->age = age;
//     if(list != NULL){
//         judge1  = compare_people(ptr,current);
//     }
//     if (list == NULL || judge1<0){
//         ptr->next = list;
//         list = ptr;
//         return list;
//     }
//     if(list != NULL || judge1>0){
//         while(current->next != NULL){
//             judge1 = compare_people(ptr,current);
//             judge2 = compare_people(ptr,current->next);
//             if (judge1>=0 &&judge2<0){
//                 ptr->next = current->next;
//                 current->next = ptr;
//                 return list;
//             }else{
//                 current = current->next;
//             }
//         }
//         ptr->next = NULL;
//         current->next = ptr;
//         current = ptr;
//         return list;
//     }
//     return list;
// }

// int main(int argc, char **argv)
// {
//     struct PERSON *people = NULL;
//     for (int i=0; i < HOW_MANY; i++)
//     {
//         // people = insert_start (people, names[i], ages[i]);
//         // people = insert_sorted (people, names[i], ages[i],compare_people_by_name);
//         people = insert_sorted (people, names[i], ages[i],compare_people_by_age);
//     }    
//     /* insert_start*/
//     while (people != NULL){
//         printf("%s, %d\n",people -> name, people -> age );
//        free (people);
//         people = people -> next;
//     }    
//     return 0;
// }

// /*=========part5============*/
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// /* these arrays are just used to give the parameters to 'insert',
//  to create the 'people' array
//  */

// #define HOW_MANY 7
// enum staff_or_student {staff, student, neither};
// enum staff_or_student identities[HOW_MANY] = {student,student,neither,neither,student,staff,student};

// char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
//     "Harriet"};
// int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};
// char *infor[HOW_MANY] =  {"Computer Science","Software Engineering","N/A","N/A","Artificial Intelligence","Kilburn 2.72","Human Computer Interaction"};



// /* declare your struct for a person here */
// struct PERSON {
//     char *name;
//     int age;
//     enum staff_or_student id;
//     union {
//         char *programme_name;
//         char *room_number;
//         char *no_infor;
//     }information;
//     struct PERSON *next;
// };



// int compare_people_by_name(struct PERSON *one, struct PERSON *two){
//     int judge = 0;
//     judge = strcmp(one->name, two->name);
//     return judge;
// }

// int compare_people_by_age(struct PERSON *one, struct PERSON *two){
//     int judge = 0;
//     judge = (one->age) - (two->age);
//     return judge;
// }

// static struct PERSON* insert_sorted(struct PERSON *list, char *name, int age, enum staff_or_student id, char *infor, int (*compare_people)(struct PERSON*, struct PERSON*)){
//     int judge1 = 0;
//     int judge2 = 0;
//     struct PERSON* ptr = (struct PERSON*)malloc(sizeof(struct PERSON));
//     struct PERSON* current;
//     current = list;
//     if (ptr == NULL) abort();
//     ptr->name = name;
//     ptr->age = age;
//     ptr->id = id;
//     if(id == staff){
//         ptr->information.room_number = infor;
//     }
//     if(id == student){
//         ptr->information.programme_name = infor;
//     }
//     if(id == neither){
//         ptr->information.no_infor = infor;
//     }
    
//     if(list != NULL){
//         judge1 = compare_people(ptr, current);
//     }
//     if(list == NULL || judge1<=0){
//         ptr->next = list;
//         list = ptr;
//         return list;
//     }
//     if(list != NULL || judge1 > 0){
//         while(current->next != NULL){
//             judge1 = (*compare_people)(ptr, current);
//             judge2 = (*compare_people)(ptr, current->next);
//             if(judge1>0 && judge2<=0){
//                 ptr->next = current->next;
//                 current->next = ptr;
//                 return list;
//             }else{
//                 current = current->next;
//             }
//         }
//         ptr->next = NULL;
//         current->next = ptr;
//         current = ptr;
//         return list;
// //        while (current->next != NULL) {
// //            current = current->next;
// //        }
// //        ptr->next = NULL;
// //        current->next = ptr;
// //        current = ptr;
// //        return list;
//     }
//     return list;
// }

// int main(int argc, char **argv)
// {
//     struct PERSON *people = NULL;
    
//     for (int i=0; i < HOW_MANY; i++)
//     {
//         // people = insert_start (people, names[i], ages[i]);
        
// //        people = insert_sorted (people, names[i], ages[i], compare_people_by_name);
//         people = insert_sorted (people, names[i], ages[i], identities[i], infor[i], compare_people_by_name);
// //        people = insert_sorted (people, names[i], ages[i], identities[i], infor[i], compare_people_by_age);
        
//     }
    
//     /* insert_start*/
//     while (people != NULL){
//         if(people->id == staff){
//             printf("%s, %d, staff, %s \n",people -> name, people -> age, people->information.room_number);
//         }
//         if(people->id == student){
//             printf("%s, %d, student, %s \n",people -> name, people -> age, people->information.programme_name);
//         }
//         if (people->id == neither) {
//             printf("%s, %d, neither, %s \n",people -> name, people -> age, people->information.no_infor);
//         }
        
//         free (people);
//         people = people -> next;
//     }
    
    
//     return 0;
// }

// /*========part6========*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* these arrays are just used to give the parameters to 'insert',
 to create the 'people' array
 */

#define HOW_MANY 7
enum staff_or_student {staff, student, neither};
enum staff_or_student identities[HOW_MANY] = {student,student,neither,neither,student,staff,student};

char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
    "Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};
char *infor[HOW_MANY] =  {"Computer Science","Software Engineering","N/A","N/A","Artificial Intelligence","Kilburn 2.72","Human Computer Interaction"};



/* declare your struct for a person here */
struct PERSON {
    char *name;
    int age;
    enum staff_or_student id;
    union {
        char *programme_name;
        char *room_number;
        char *no_infor;
    }information;
    struct PERSON *next;
};


int compare_people_by_name(struct PERSON *one, struct PERSON *two){
    int judge = 0;
    judge = strcmp(one->name, two->name);
    return judge;
}

int compare_people_by_age(struct PERSON *one, struct PERSON *two){
    int judge = 0;
    judge = (one->age) - (two->age);
    return judge;
}

static struct PERSON* insert_sorted(struct PERSON *list, char *name, int age, enum staff_or_student id, char *infor, int (*compare_people)(struct PERSON*, struct PERSON*)){
    int judge1 = 0;
    int judge2 = 0;
    struct PERSON* ptr = (struct PERSON*)malloc(sizeof(struct PERSON));
    if (ptr == NULL) abort();
//    struct PERSON* current;
//    current = list;
    ptr->name = name;
    ptr->age = age;
    ptr->id = id;
    if(id == staff){
        ptr->information.room_number = infor;
    }
    if(id == student){
        ptr->information.programme_name = infor;
    }
    if(id == neither){
        ptr->information.no_infor = infor;
    }
    struct PERSON** ptr2ptr = &list;
    
    if(list != NULL){
        judge1 = compare_people(ptr, *ptr2ptr);
    }
      if(list == NULL || judge1<=0){
        ptr->next = list;
        list = ptr;
        return list;
    }
    
    if(list != NULL || judge1 > 0){
        
        while(*ptr2ptr){
            if((*ptr2ptr)->next){
                judge1 = (*compare_people)(ptr, *ptr2ptr);
                judge2 = (*compare_people)(ptr, (*ptr2ptr)->next);
                if(judge1>0 && judge2<=0){
                    ptr->next = (*ptr2ptr)->next;
                    (*ptr2ptr)->next = ptr;
                    return list;
                }
            }else{
                ptr->next = NULL;
                (*ptr2ptr)->next = ptr;
                return list;
            }
            ptr2ptr = &(*ptr2ptr)->next;
        }
        ptr->next = *ptr2ptr;
        *ptr2ptr = ptr;
        return list;
    }
    ptr2ptr = &(*ptr2ptr)->next;
    return list;
}

int main(int argc, char **argv)
{
    struct PERSON *people = NULL;
    
    for (int i=0; i < HOW_MANY; i++)
    {
        // people = insert_start (people, names[i], ages[i]);
        
        //        people = insert_sorted (people, names[i], ages[i], compare_people_by_name);
        people = insert_sorted (people, names[i], ages[i], identities[i], infor[i], compare_people_by_name);
        //        people = insert_sorted (people, names[i], ages[i], identities[i], infor[i], compare_people_by_age);
        
    }
    
    /* insert_start*/
    while (people != NULL){
        if(people->id == staff){
            printf("%s, %d, staff, %s \n",people -> name, people -> age, people->information.room_number);
        }
        if(people->id == student){
            printf("%s, %d, student, %s \n",people -> name, people -> age, people->information.programme_name);
        }
        if (people->id == neither) {
            printf("%s, %d, neither, %s \n",people -> name, people -> age, people->information.no_infor);
        }
        
        free (people);
        people = people -> next;
    }    
    return 0;
}
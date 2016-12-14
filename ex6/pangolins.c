//
//  main.c
//  pangolin
//
//  Created by 杨博尹 on 2016/11/30.
//  Copyright © 2016年 UoM. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    char *objName; // a string declaration to hold an object-name (which may be NULL)
    char *question; // a string declaration to hold a question (which may be NULL)
    
    struct node *yes_ptr; // only NULL for objects
    struct node *no_ptr; // only NULL for objects
};

struct node rootNY[] = {{"pizza",NULL,NULL,NULL}};
struct node rootNN[] = {{NULL,"Can you dip it in your tea?",NULL,NULL}};
struct node rootYY[] = {{"pangolin",NULL,NULL,NULL}};
struct node rootYN[] = {{"cat",NULL,NULL,NULL}};
struct node rootN[] = {{NULL,"Is it flat, round, and edible?",rootNY,rootNN}};
struct node rootY[] = {{NULL,"Does it chase mice?",rootYY,rootYN}};
struct node root[] = {{NULL,"Does it have a tail?",rootY,rootN}};

int finish = 0;
char *y = "yes\n";
char *n = "no\n";
FILE *finput;
FILE *foutput;

int stricmp(const char* p1, const char* p2){
    while (*p1){
        char c1 = *p1;
        char c2 = *p2;
        if (c1 >= 'A' && c1 <= 'Z'){
            c1 += 'a' - 'A';
        }
        if (c2 >= 'A' && c2 <= 'Z'){
            c2 += 'a' - 'A';
        }
        if (c1 != c2){
            return c1 - c2;
        }
        p1++;
        p2++;
    }
    return *p1 - *p2;
}


void doFree(struct node *ptr){
    if (ptr!=NULL) {
        if (ptr->objName == NULL) {
            free(ptr->objName);
            free(ptr);
        }else{
            doFree(ptr->yes_ptr);
            doFree(ptr->no_ptr);
            free(ptr->question);
            free(ptr);
        }
    }
}


void treePrint(struct node *ptr){
    if (ptr == NULL){
        return;
    }
    else{
        if (ptr->yes_ptr!=NULL||ptr->no_ptr!=NULL){
            fprintf(foutput,"Object: [Nothing]\nQuestion: %s\n",ptr->question);
            //now print the yes and no subtrees:
            treePrint(ptr->yes_ptr);
            treePrint(ptr->no_ptr);
        }
        else{
            fprintf(foutput,"Object: %s\nQuestion: [Nothing]\n",ptr->objName);
        }
    }
}

struct node *treeRead(FILE *fileinput){
    char *input = (char*)malloc(sizeof(char)*100);
    fgets(input, 100, fileinput);
    if (input == NULL) // i.e. no input
        return NULL;
    else{
        struct node *ptr = (struct node *)malloc(sizeof(struct node));
        if(strncmp(input, "Question:",9) == 0){
            //fill ptr with the question from the input line
            ptr->question = input;
            ptr->objName = NULL;
            //now read the yes and no subtrees:
            ptr->yes_ptr = treeRead(fileinput);
            ptr->no_ptr = treeRead(fileinput);
        }
        else if(strncmp(input, "Object:",7) == 0){
            // the line started with "object:"
            //fill ptr with the object-name from the input line
            ptr->question = NULL;
            ptr->objName = input;
            ptr->yes_ptr = ptr->no_ptr = NULL;
        }
        free(input);
        return ptr;
    }
    
}



void askPrint(struct node *ptr){
    if(ptr->objName){
        printf("Is it a %s?\n>", ptr->objName);
    }else{
        printf("%s>", ptr->question);
    }
}

struct node* initialise(struct node *BiTreeNode){
    
    
    return BiTreeNode;
}

struct node* create(struct node *ptr){
//    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    char *object = (char*)malloc(sizeof(char)*50);
    char *question = (char*)malloc(sizeof(char)*100);
    char *yorn = (char*)malloc(sizeof(char)*10);
//    ptr->objName = CurrentNode->objName;
    printf("You win.\nWhat were you thinking of?\n>");
    fgets(object,50,stdin);
    printf("Please give me a question about %s, so I can tell the difference between %s and %s.\n>",object,object,ptr->objName);
    fgets(question,100,stdin);
    printf("What's the answer for %s?\n>",object);
    fgets(yorn, 10, stdin);
    while (stricmp(yorn, y) && stricmp(yorn, n)) {
        printf("Wrong enter, please enter again!\n");
        fgets(yorn, 10, stdin);
    }
    ptr->question = question;
    
    if (stricmp(yorn,y)==0) {
        struct node *tempN = (struct node*)malloc(sizeof(struct node));
        struct node *tempY = (struct node*)malloc(sizeof(struct node));
        
        tempN->objName = ptr->objName;
        ptr->objName = NULL;
        ptr->no_ptr = tempN;
        tempY->objName = object;
        ptr->yes_ptr = tempY;
    }
    if (stricmp(yorn, n)==0) {
        struct node *tempN = (struct node*)malloc(sizeof(struct node));
        struct node *tempY = (struct node*)malloc(sizeof(struct node));
        tempN->objName = ptr->objName;
        ptr->objName = NULL;
        ptr->yes_ptr = tempN;
        tempY->objName = object;
        ptr->no_ptr = tempY;
    }
    
//    CurrentNode = ptr;
    return ptr;
}

struct node* play(struct node *currentNode){
    char *yorn = (char*)malloc(sizeof(char)*10);
    finish = 0;
    if (currentNode->objName==NULL || currentNode->question==NULL) {
        askPrint(currentNode);
    }
    
    if (currentNode->question) {// a question
        
        fgets(yorn, 10, stdin);
        while (stricmp(yorn, y) && stricmp(yorn, n)) {
            printf("Wrong enter, please enter again!\n");
            fgets(yorn, 10, stdin);
        }
        if (stricmp(yorn, y)==0) {
            currentNode = currentNode->yes_ptr;
            currentNode = play(currentNode);
        }
        if (stricmp(yorn, n)==0) {
            currentNode = currentNode->no_ptr;
            currentNode = play(currentNode);
        }
    }else{                      // an object
            fgets(yorn, 10, stdin);
            while (stricmp(yorn, y) && stricmp(yorn, n)) {
                printf("Wrong enter, please enter again!\n");
                fgets(yorn, 10, stdin);
            }
            if (stricmp(yorn,y)==0) {
                printf("Thank you.\n");
            }
            if (stricmp(yorn, n)==0) {
                currentNode = create(currentNode);
            }
    }
    return currentNode;
}


int main(int argc, const char * argv[]) {
//    treePrint(root);//part1
    char *yorn = (char*)malloc(sizeof(char)*10);
    if(argc!=2){
        printf("Please enter the right number of files.\n");
    }
    // finput = fopen(argv[1],"r");
    struct node* BTree = (struct node*)malloc(sizeof(struct node));
    if (BTree==NULL) abort();

    BTree->objName = "pangolin";
    BTree->yes_ptr = BTree->no_ptr = NULL;
            

    // BTree = treeRead(finput);
    foutput = fopen(argv[1], "w");

    

    
    
    printf("Think about something.\n");
    while (!finish) {
        
        
        play(BTree);
            printf("Do you want to play it again?\n>");
            fgets(yorn, 10, stdin);
            while (stricmp(yorn, y) && stricmp(yorn, n)) {
                printf("Wrong enter, please enter again!\n");
                scanf("%s",yorn);
            }
            if(stricmp(yorn,y)==0){
                finish = 0;
            }
            if(stricmp(yorn, n)==0){
                finish = 1;
            }
    }
    
    
    
    printf("Thank you.");
    doFree(BTree);
    treePrint(BTree);
    // fclose(finput);
    fclose(foutput);
    return 0;
}


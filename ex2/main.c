//
//  main.c
//  Comp26120Ex2
//
//  Created by 杨博尹 on 2016/10/12.
//  Copyright © 2016年 Boyin. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, const char * argv[]) {

    char f1[200];
    char f2[200];
    FILE* fstream;
    FILE* fstream2;
    printf("please input a path of the file you want read\n");
    scanf("%s",f1);
    fstream = fopen(f1, "r");
    printf("please input a path of the file you want write\n");
    scanf("%s",f2);
    fstream2 = fopen(f2, "w");
    
    
    
    assert(fstream);
    assert(fstream2);
    if (!fstream){
        perror("open file input failed!\n");
        return EXIT_FAILURE;
    }
    
    int c; //not char, required to handle EOF
    int upper=0, lower=0, total=0;
    while ((c = fgetc(fstream))!=EOF){
        if (c=='\n'){
            printf("\n");
            break;
        }
        total++;
        if (!isalpha(c)){
            fwrite(&c, 1, 1, fstream2);
        }else{
            if (isupper(c)){
                upper++;
            }else{
                lower++;
            }
            c=isupper(c)?c+32:c-32;
            
            fwrite(&c, 1, 1, fstream2);
        }
        
        putchar(c);
    }
    if (ferror(fstream))
        puts("I/O error when reading");
    else if(feof(fstream))
        puts("End of file reached successfully");
    
    printf("Read %i characters in total, %i converted to upper-case, %i to lower-case\n", total,upper, lower);
    
    fclose(fstream);
    fclose(fstream2);
    return 0;
}

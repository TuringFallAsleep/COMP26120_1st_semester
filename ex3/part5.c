#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int readFile (char fileName[]);

int main(int argc, const char *argv[]){
	char name[100];
	strcpy(name,"input");
	readFile (name);
	return 0;
}

int readFile (char fileName[100]){
	FILE* fstream;
	int diff=300;
	int num = 3;
	int count[diff][num];
	int ch;
	int k=0;
	for(int i=0;i<diff;i++)
		for(int j=0;j<num;j++)
			count[i][j] = 0;
	fstream = fopen("input","r");
	if (!fstream){
		printf("read file failed\n");
		return 0;
	}
	while ((ch = getc(fstream))!=EOF){
		count[ch][0] = ch;
		count[ch][1]++;
	}
	for (int i=0;i<diff;i++){
		if(count[i][1]!=0){
			printf("%d instances of character Ox%x (%c)\n",count[i][1],count[i][0],count[i][0]);
			k++;
		}
	}
	fclose(fstream);
	printf("There are %d different characters.\n", k);
	return 0;
}

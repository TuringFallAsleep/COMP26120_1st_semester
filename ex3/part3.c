#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	int i;
	int longth = 0;
	int longest = 0;
	int index;
	if (argc-1 == 0){
		printf("No parameters\n");
		return 0;
	}
	for (i=1; i<argc; i++){
		longth = strlen(argv[i]);
		if (longest < longth){
			longest = longth;
			index = i;
		}
	}
	for (i=index+1; i<argc; i++){
		if (longest == strlen(argv[i])){
			printf("There not only one longest parameters\n");
			printf("The longest parameter is number %d that is: %s\n",i, argv[i]);
		}
	}
	printf("The longest parameter is number %d that is: %s\n",index, argv[index]);
	return 0;
}
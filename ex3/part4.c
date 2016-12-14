#include <stdio.h>
#include <stdlib.h>
#include <string.h>
float c2f (float c);
float f2c (float f);

int main(int argc, char *argv[]){
	if (argc-1 == 0){
		printf("No inputs\n");
		return 0;
	}
	if (argc-1 > 2){
		printf("Too much inputs\n");
		return 0;
	}
	float temperature;
	char Type[100];
	char Tem[100];
	char Temp[100];

	char type[5];
	strcpy(Type,argv[1]);
	strcpy(Tem,argv[2]);
	sscanf(Type,"%s",type);
	sscanf(Tem,"%s", Temp);
	temperature = atof(Temp); //char 2 float

	if (strcmp(type,"-f")==0){
		f2c(temperature);
		printf("show -f\n");

	}
	if (strcmp(type,"-c")==0){
		c2f(temperature);
	}
	return 0;
}

float c2f (float c){
	float f;
	if (c < -273.15){
		printf("This temperature is lower than absolute zero\n");
		return 0;
	}
	f = 9*c/5 +32;
	printf("%6.2f°C = %6.2f°F\n",c,f);
	return 0;
}

float f2c (float f){
	float c;
	c = (f-32)*5/9;
	if (c < -273.15){
		printf("This temperature is lower than absolute zero\n");
		return 0;
	}
	printf("%6.2f°F = %6.2f°C\n",f,c);
	return 0;
}
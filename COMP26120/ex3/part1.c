#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int largest(int array[], int length);
int main(){
	int a[] = {21,23,'z',10,90,1,87};
	// int a[] = {21,23,1,10,90,-4,87};
	// int a[1];
	int i = 0;
	int l = sizeof(a)/sizeof(a[0]);
	for (int j=0; j<l; j++){
		if(a[j]>='a'&&a[j]<='z'){
			printf("\nElements in array are not all integers, please check the array again.\n");
			return 0;
		}
	}
	printf("\nAll elements in array is integers\n");
	i=largest(a,l);
	printf("\nThe largest element in this array is %d\n", a[i]);
	return 0;	
}

int largest(int array[], int length){
	int index;
	int temp;
	temp = array[0];
	for (int i=0; i<length; i++){
		if (array[i]>temp){
			temp = array[i];
			index = i;
		}
	}
	return index;
}


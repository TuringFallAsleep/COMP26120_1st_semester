#include <stdio.h>
void chessBoard (int size[100][100],int l, int w);

enum boardColour {Black, White} colour;

int main(){
	int width;
	int longth;
	printf("\nPlz enter the width of the chess board: ");
	scanf("%d",&width);
	if(width<=0){
		printf("\nPlz enter a positive number: ");
		scanf("%d",&width);
	}
	printf("\nPlz enter the longth of the chess board: ");
	scanf("%d",&longth);
	if(longth<=0){
		printf("\nPlz enter a positive number:");
		scanf("%d",&longth);
	}
	int a[longth][width];
	chessBoard(a,longth,width);
	return 0;
}

void chessBoard (int size[100][100],int l, int w){
	int i = 0;
	int j = 0;
	printf("longth=%d width=%d\n0=Black 1=White\n", l,w);
	for (i=0; i<l; i=i+2){
		for (j=0; j<w; j=j+2)
			size[i][j] = Black;
		for (j=1; j<w; j=j+2)
			size[i][j] = White;
	}
	for (i=1; i<l; i=i+2){
		for (j=0; j<w; j=j+2)
			size[i][j] = White;
		for (j=1; j<w; j=j+2)
			size[i][j] = Black;
	}
	for (i=0; i<l; i++){
		for (j=0; j<w; j++){
			printf("%d", size[i][j]);
		}
		printf("\n");
	}
}
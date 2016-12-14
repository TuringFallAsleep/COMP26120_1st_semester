#include <stdlib.h>
#include <stdio.h>
#include <math.h>

FILE *fp;

typedef struct book
{
  double rating;
  double price;
  double relevance;
  int ID;
} B;

B *list;

void mySort(B *currentList, int n, int(*compar)(const void *a, const void *b));


int read_file(char *infile, int N)
{
  int c;
  if((fp=fopen(infile, "rb")))
    {
      fscanf(fp, "%*s\t%*s\t%*s\t%*s\n");
      c=0;
      while((!feof(fp))&&(c<N))
  {
    fscanf(fp, "%lf\t%lf\t%lf\t%d\n", &list[c].rating,  &list[c].price, &list[c].relevance, &list[c].ID);   
    c++;
  }
      fclose(fp);      
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",infile);
      exit(-1);
    }
  return(c);
}

int comp_on_rating(const void *a, const void *b)
{
  if ((*(B *)a).rating < (*(B *)b).rating)
  {  
     return -1;
  }
    else 
  {
    if ((*(B *)a).rating > (*(B *)b).rating)
    {
      return 1;
    }
      else
    {
      return 0;
    }
  }  
}

int comp_on_relev(const void *a, const void *b)
{
 
  if ((*(B *)a).relevance < (*(B *)b).relevance)
  {  
     return -1;
  }
     else 
  {
     if ((*(B *)a).relevance > (*(B *)b).relevance)
     { 
       return 1;
     }
       else
     {
       return 0;
     }
  }  
}

int comp_on_price(const void *a, const void *b)
{
 
  if ((*(B *)a).price < (*(B *)b).price)
  { 
     return 1;
  }
     else 
  {
     if ((*(B *)a).price > (*(B *)b).price)
     {
       return -1;
     }
       else
     {
       return 0;
     }
  }  
}

void user_interface(int N)
{

  // For Part 1 this function calls the sort function to sort on Price only

  int(*ptrComp)(const void *, const void *) = comp_on_price;
  mySort(list,N, ptrComp); //How to set the arguments?
  

  // For Part 2 this function
  // (1) asks the user if they would like to sort their search results
  // (2) asks for the most important field (or key), the next most etc
  // (3) calls your sort function
  

}

// L is the left part of the list, R is the right part of the list.
// leftCount is number of element in L;
// rightCOunt is number of element in R.
void myMerge(B *currentList, B *L, int leftCount, B *R, int rightCount, int(*compar)(const void *a, const void *b)){
  int i,j,k;
  // i - to mark the index of left list (L)
  // j - to mark the index of left list (R)
  // k - to mark the index of left list (A)
  i=j=k=0;

  while (i<leftCount && j<rightCount){
    if(compar(&L[i],&R[j])==1) currentList[k++] = L[i++];
    else currentList[k++] = R[j++];
  }

  while (i < leftCount) currentList[k++] = L[i++];
  while (j < rightCount) currentList[k++] = R[j++];

}

void mySort(B *currentList, int n, int(*compar)(const void *a, const void *b)){
  int mid,i;
  B *L,*R;
  if(n < 2) return;
  mid = n/2; // find the mid index

  // create left and right subarrays
  // mid elements (from index 0 to mid-1) should be the left part of the sub-list
  // (n-mid) elements (form mid to n-1) should be the right part of the sub-list
  L = (B *)malloc(mid*sizeof(B));
  R = (B *)malloc((n-mid)*sizeof(B));

  for(i=0;i<mid;i++) L[i] = currentList[i];
  for(i=mid;i<n;i++) R[i-mid] = currentList[i];


  mySort(L,mid,compar);
  mySort(R,n-mid,compar);
  myMerge(currentList,L,mid,R,n-mid,compar);
  free(L);
  free(R);
}
 

void print_results(int N)
{
    int i;
    if((fp=fopen("top20.txt","w")))
    {
      for(i=N-1;i>=N-20;i--)
      {  
    printf("%g %g %g %d\n", list[i].rating, list[i].price, list[i].relevance, list[i].ID);
    fprintf(fp, "%g %g %g %d\n", list[i].rating, list[i].price, list[i].relevance, list[i].ID);
    
      }
      fclose(fp);
    }
      else
    {
      fprintf(stderr,"Trouble opening output file top20.txt\n");
      exit(-1);
    }

}


int main(int argc, char *argv[])
{
  int N;

  if(argc!=3)
    {
      fprintf(stderr, "./exec <input_size> <filename>\n");
      exit(-1);
    }

  N=atoi(argv[1]);

  list = (B *)malloc(N*sizeof(B));
  
  N=read_file(argv[2], N);
  
  user_interface(N);
  
  print_results(N);

  free(list);

  return(0);
}
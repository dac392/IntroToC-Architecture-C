#include <stdio.h>
#include <stdlib.h>

void swap(int *me, int *meAsWell){
	int temp = *me;
	*me = *meAsWell;
	*meAsWell = temp;
}
void printA(int arr[], int size){
	for(int i = 0; i < size; i++){
		printf("%d\t", arr[i]);
	}
	printf("\n");
}
int partition(int arr[], int start, int end){
	int pivot = arr[end];
	int partitionIndex = start;
	for(int i = start; i < end; i++){
		if(arr[i] <= pivot &&(arr[i]%2 ==0 )){
			swap(&arr[i], &arr[partitionIndex]);
			partitionIndex++;
		}else if(arr[i]>= pivot && (arr[i]%2 != 0)){
			swap(&arr[i], &arr[partitionIndex]);
			partitionIndex++;
		}
	}
	swap(&arr[partitionIndex], &arr[end]);
	return partitionIndex;
}
void evenSort(int eve[], int start, int end){

	if(start < end){
		int partitionIndex = partition(eve,start,end);
		evenSort(eve,start,partitionIndex-1);
		evenSort(eve,partitionIndex+1,end);
	}
}

void split(int master[], int masterSize, int eve[], int evenSize, int od[], int oddSize){
	
	int eveptr = 0;
	int odptr = 0;
	for(int i = 0; i < masterSize; i++){
		if(master[i]%2 ==0){
			eve[eveptr] = master[i];
			eveptr++;
		}else{
			od[odptr] = master[i];
			odptr++;
		}
	}
	// printf("Even array before sort: ");
	// printA(eve,evenSize);
	evenSort(eve,0,evenSize-1);
	// printf("Even array after sorting: ");
	// printA(eve, evenSize);
	// printf("Odd array: ");
	// printA(od,oddSize);
	evenSort(od,0,oddSize -1);
	// printf("Odd array after sorting: ");
	// printA(od,oddSize);

	for(int i = 0; i < evenSize; i++){
		master[i] = eve[i];
	}
	for(int i = 0; i < oddSize; i++){
		master[evenSize+i] = od[i];
	}
	free(eve);
	free(od);
}
int main(int argc, char* argv[]){
	FILE* fp = fopen(argv[1], "r");
	int n;
	int evenSize = 0;
	int oddSize = 0;
	fscanf(fp,"%d",&n);
	printf("Number of items = %d\n", n);
	int* master= malloc(sizeof(int)*n);
	int temp;
	for(int i = 0; i < n; i++){
		fscanf(fp,"%d", &temp);
		if(temp%2 ==0){
			evenSize++;
		}else{
			oddSize++;
		}
		master[i] = temp;
	}
	int*evenA = malloc(sizeof(int)*evenSize);
	int*oddA = malloc(sizeof(int)*oddSize);
	split(master,n, evenA, evenSize, oddA,oddSize);
	printf("sorted array: ");
	printA(master, n);
	free(master);
	return 0;
}

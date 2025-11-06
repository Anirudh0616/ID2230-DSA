#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void sorterandmerger(int a[],int l, int m, int r){
	int L[m-l+1];
	int R[r-m];
	for(int i = l;i<m+1;i++){
		L[i-l] = a[i];
	}
	for(int j = m+1;j<r+1;j++){
		R[j-m-1] = a[j];
	}
	int i,j,k;
	// Using while loop here might be better; 
	for(i=0,j=0,k=l;k<r+1;k++){
		if(i<m-l+1 && j<r-m){
			if(L[i] <= R[j]){
				a[k] = L[i++];
			} else {
				a[k] = R[j++];
			}
		} else {
			break;
		}
	}
	while(i<m-l+1)a[k++] = L[i++];
	while(j<r-m)a[k++] = R[j++];
}

void divider(int a[],int l, int r){
	if(l<r){
		int m = l +(r-l)/2;
		divider(a,l,m);
		divider(a,m+1,r);
		sorterandmerger(a,l,m,r);
	}
}



int main(){
	int A[6] = {100,4,15,9,10,6};
	int n = 6;
	for(int i = 0;i<6;i++){
		printf("%d ",A[i]);
	}
	divider(A,0,5);
	printf("\nSorted\n");
	for(int i = 0;i<6;i++){
		printf("%d ",A[i]);
	}
	printf("\n");
	return 0;
}

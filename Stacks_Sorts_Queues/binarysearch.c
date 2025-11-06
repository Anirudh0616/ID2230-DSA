#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int found = 0;

int binarySearch(int*A,int low,int high,int target){
	if(low>high) return found;
	int mid = low + (high - low )/2;
	if(A[mid]==target){
		found++;
		binarySearch(A,mid+1,high,target);
		binarySearch(A,low,mid-1,target);
	} 
	if(A[mid]<target) return binarySearch(A,mid+1,high,target);
	if(A[mid]>target) return binarySearch(A,low,mid-1,target);
	return found;
}

int binarySearchRotated(int*A,int low,int high, int target){
	if(low>high) return 0;
	int mid = low + (high-low)/2;
	if(A[mid] == target) return A[mid];
	if(A[low]<=target && target<A[mid]){
		return binarySearchRotated(A,low,mid-1,target);
	} else {
		return binarySearchRotated(A,mid+1, high, target);
	}
	return 0;
}


int main(){
	//          0 1 2  3  4  5 6 7
	int A[7] = {8,9,16,32,1,2,4};

	int x = binarySearchRotated(A,0,7,1);

	if(x) printf("Found! %d\n",x);
	else printf("Not Found!\n");

	return 0;
}

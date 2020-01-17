#include<stdio.h>
#include<string.h>
int A[100],T[100];
void merge_sort(int* A, int x, int y, int* T) {
	if (y-x > 1) {
		int m = x + (y-x)/2;
		int p = x, q = m, i = x;
		merge_sort(A, x, m, T);
		merge_sort(A, m, y, T);
		while(p < m || q < y) {
			if (q >= y || (p < m && A[p] <= A[q])) T[i++] = A[p++];
			
			else T[i++] = A[q++];
		}
		for (i = x; i < y; i++) A[i] = T[i];
	}
}
int main() {
	int n;
	scanf("%d",&n);
	for(int i = 0;i < n;i ++) scanf("%d",&A[i]);//,T[i] = A[i];
	merge_sort(A, 0, n, T);
	for(int i = 0;i < n;i ++) printf("%d ",A[i]);
	return 0;
}

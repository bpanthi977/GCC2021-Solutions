#include <bits/stdc++.h>
#include <cstdlib>
int N;
int K;
int D;
int maxMin;
using namespace std;

int* table;
int *rowMax;
int *boxMax;
int *nRowMax; //next rowMax
int *nBoxMax; //next BoxMax

inline int Table(int s, int e) {
  return table[s*N+e];
}

void initTable (int n, int* arr, int d, int m){
  table = (int *)calloc(n * n, sizeof(int));
  int p=0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++, p++) {
      if (j<i) continue;
      if (i == j) {
	table[p] = -arr[i];
      } else {
	table[p] += table[p-1] + ((j-i > d)? 0: (m-1) * arr[j]);
      }
    }
  }

  int* memory = (int*) calloc(4*n, sizeof(int));
  rowMax = memory;
  boxMax = memory+N;
  nRowMax = memory + 2 * N;
  nBoxMax = memory + 3 * N;
  for (int i = 0; i < n ; i++) {
    rowMax [i] = Table(i,N-1);
  }
  boxMax[N-1] = rowMax[N-1];
  for (int i = n-2; i > -1; i--){
    boxMax[i] = max (boxMax[i+1], rowMax [i]);
  }
}

int solve(int k) {
  // k = for which we have rowMax & boxMax table
  int rem = K-k;  
  if (rem == 0) {
    return boxMax[0];
  }

  // generated max tables of k+1;
  int imax = N-k;
  for (int i=0; i<imax; i++) {
    int jlim = min(imax+1, i + D + 2);
    int max = maxMin;
    for (int j=i+1; j<jlim; j++) {
      int v = Table(i,j-1) + ((j>i+D) ? boxMax[j] : rowMax[j]);
      if (v > max)
	max = v;
    }
    nRowMax[i] = max;
  }
  nBoxMax[imax-1] = nRowMax[imax-1];
  for (int i = imax-2; i > -1;i--){
    nBoxMax[i] = max(nBoxMax[i+1], nRowMax[i]);
  }
  int* tmp = rowMax;
  rowMax = nRowMax; nRowMax = tmp;
  tmp = boxMax; boxMax = nBoxMax; nBoxMax = tmp;
  return solve(k+1);
}

int calculateMaximizedReturns(int n, int k, int d, int m, int* arr) {
  initTable(n, arr, d, m);
  int val= solve(1);
  return val;
}

int main() {
  // N = 5;
  // K = 3;
  // D = 2;
  // int m = 11;
  // int arr[] = {1,2,3,4,2};
  int m;
  cin >> N; cin >> K; cin >> D; cin >> m;
  int *arr = (int *)malloc(N * sizeof(int));
  for (int i =0; i<N; i++) cin >> arr[i];
  
  int sum=0;
  for (int i=0; i<N; i++) sum+= arr[i];
  maxMin = -sum;
  int result = sum + calculateMaximizedReturns(N, K, D, m, arr);

  cout << result;

  return 0;
}

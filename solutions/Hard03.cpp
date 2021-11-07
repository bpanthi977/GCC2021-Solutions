#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>

int B, C;
int infinity;
int* table;
int *runningSum;
int *sortedCols;

inline int I(int b, int c){
  // indexes into tables (b is banker, c is client)
  return b*C+c;
}

inline int SC(int b, int c) {
  // indexs into sorted cols table
  return c*B*2 + b*2;
}

void sortPairs(int* arr, int n){
  // sort pairs of integers (with first int as key); total n pairs
  using namespace std;
  int min, mini;
  for (int i = 0; i < 2 * n; i += 2) {
    min = arr[i];
    mini = i;
    for (int j=i; j<2*n; j+=2) {
      if (arr[j]< min) {
	min = arr[j];
	mini = j;
      }
    }
    if (mini != i) {
      // swaping values 
      arr[mini] = arr[i];
      arr[i] = min;
      int tmp = arr[i+1];
      arr[i+1] = arr[mini+1];
      arr[mini+1] = tmp;
    }
  }
}

int UpperBound(int n, int *iRows) { // ignoredRows
  int min = infinity;
  if (n==0) return 0;
  for (int i = 0; i < B; i++){
    if (iRows[i]  == 0) {
      if (runningSum[I(i,n-1)] < min) {
	min = runningSum[I(i,n-1)];
      }
    }
  }
  return min;
}

int LowerBound(int n, int *iRows) {
  if (n==0) return 0;
  int sum = 0;
  for (int j=0; j<n; j++){
    int min=infinity;
    for (int i=0; i<B; i++){
      if (iRows[sortedCols[SC(i,j)+1]] == 0) {
        min = sortedCols[SC(i, j)];
	break;
      }
    }
    sum+=min;
  }
  return sum;  
}


int U; // Lowest upper bound 

int boundAndBranch(int n, int *iRows, int currentRow, int UBCarry) {
  int min = U;
  for (int i=0; i<B; i++){
    if (iRows[i] == 0 || i == currentRow) {
      int s = 0;
      iRows[i] = 1;
      for (int k = n - 1; k >= 0; k--) {
        s += table[I(i, k)];
        int uu = UpperBound(k, iRows) + s + UBCarry;
	U = std::min(U, uu);
      }
      if (i != currentRow)
        iRows[i] = 0;
    }
  }
  
  for (int i = 0; i < B; i++) {
    if (iRows[i] == 0 || i == currentRow) {
      int l=infinity;
      int s = 0;
      iRows[i] = 1;
      for (int k = n - 1; k >= 0; k--) {
	s += table[I(i,k)];
        l = std::min(l, LowerBound(k, iRows) + s + UBCarry);
      }

      if (l < U){ // branch
	iRows[i] = 1;
	min = std::min(min, boundAndBranch(n - 1, iRows, i, UBCarry + table[I(i,n-1)]));
      } else if (l == U) {
	min = std::min(min, l);
      }
      if (i!=currentRow) iRows[i] = 0;
    }
  }
  return min;
}

int main() {
  using namespace std;
  cin >> C >> B;
  table = (int *)malloc(C * B * sizeof(int));
  runningSum = (int *)malloc(C * B * sizeof(int));
  sortedCols = (int *)malloc(C*B*2*sizeof(int));
  infinity = 0; 
  for (int i = 0; i < B; i++) {
    for (int j = 0; j < C; j++) {
      cin >> table[I(i,j)];
      runningSum[I(i, j)] =
	(j == 0) ? table[I(i, j)] : table[I(i, j)] + runningSum[I(i, j - 1)];
      sortedCols[SC(i,j)] = table[I(i,j)];
      sortedCols[SC(i, j) + 1] = i;
      infinity += table[I(i,j)];
    }
  }
  // sort cols
  for (int j=0; j<C;j++){
    sortPairs(sortedCols + SC(0,j), B);
  }
  // initial UpperBound
  int *ignoredRows =
    (int *)calloc(B+1, sizeof(int))+1; // all zero. no banker ignored
  U = UpperBound(C, ignoredRows);
  int min = boundAndBranch(C, ignoredRows, -1, 0);
  printf("%d\n", min);
  return 1;
}

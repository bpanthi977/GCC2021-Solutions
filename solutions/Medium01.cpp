#include <iostream> 

int totalPairs(int n, int* a){
  int* LM = (int*)malloc(n*sizeof(int));
  int* RM = (int*)malloc(n*sizeof(int));

  int max = 0;
  for (int i=0; i<n; i++){
    if (a[i] > max) {
      max = a[i];
    }
    LM[i] = max;
  }

  max = 0;
  for (int i=n-1; i>-1; i--){
    if (a[i] > max){
      max = a[i];
    }
    RM[i] = max;
  }

  int count=0;
  for (int i=0; i<n; i++){
    if (i>1){
      if (a[i-1] < a[i] && LM[i-2] > a[i]){
	count++;
      }
    }
    if (i<n-2){
      if (a[i+1] < a[i] && RM[i+2] > a[i]) {
	count++;
      }
    }
  }
  count+= n-1; // adjdacent sticks
  return count;
}


int main() {
  int values[] = {2,80,7,8,3,5};
  int n = sizeof(values) / sizeof(int);
  printf("%d\n", totalPairs(n, values));
  return 0;
}

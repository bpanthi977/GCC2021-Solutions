#include <stdio.h>
#include <cstdlib>
#include <algorithm>

int findMin(int n, int *array){
  int min = *array;
  int pos = 0;
  for (int i = 1; i < n; i++) {
    array++;
    if ((*array < min || min == -1) && *array != -1) {
      pos = i;
      min = *array;
    }
  }
  return pos;  
}

int securitiesBuying(int z, int n, int *security_value)
{
  int count = 0;
  int total = 0;  
  int p, x;

  for (int i = 0; i < n; i++) {
    p = findMin(n, security_value);
    x = (z - total) / security_value[p];
    if (x < 1) {
      return count;
    }
    x = std::min(x, p + 1);

    count+= x;
    total+= x * security_value[p];
    security_value[p] = -1;
  }
  
    return count; 
}

int main(){
  int security_value[] = {10,7,19};
  int z = 45;
  int n = 3;
  printf("%d", securitiesBuying(z, n, security_value));
}

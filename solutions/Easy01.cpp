#include <stdio.h>

int solution(int n){
    int q = 2 * (n / 3); 
    if (n % 3 != 0) q++;
    return q;
}

int main () {
  printf("%d\n",solution(1));
  return 0;
}

#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

int cumulative(int *a, int n, int limit) {
  int prev = 0, i;
  for (i=0; i<n; i++) {
    a[i] = a[i] + prev;
    prev = a[i];
    if (a[i] > limit)
      break;
  }
  return i;
}

int position (int limit, int *arr, int n) {
  if (n == 0 || *arr > limit)
    return 0;
  int mid = n/2;
  if (arr[mid] > limit) {
    return position(limit, arr, mid);
  } else if (arr[mid] == limit) {
    for (; mid < n; mid++) {
      if (arr[mid] > limit)
	break;
    }
    return mid;
  } else if (n == 1 && mid == 0) {
    return 1;
  } else {
    return 1 + mid + position(limit, arr+mid+1, n - mid - 1);
  }
}


int *a, *b;
int n, m;
int search0(int limit, int x1, int y1, int x3, int y3, int maxima) {
  // branch and bound
  if (x1 == x3+1) {
    return maxima;
  }
  int x2 = x3 + (x1 - x3) / 2;
  int y2 = position(limit - a[x2-1], b, m);
  maxima = std::max(maxima, x2 + y2);
  maxima = search0(limit, x1, y1, x2, y2, maxima);
  maxima = search0(limit, x2, y2, x3, y3, maxima);
  return maxima;
}

int search(int limit) {
  // convert to cumulative
  n = cumulative(a, n, limit);
  m = cumulative(b, m, limit);

  if (n == 0 || m ==0 || a[0] >= limit || b[0] >= limit) {
    return std::max(position(limit, a, n), position(limit, b, m));
  }
  int x1 = n, y1 = position(limit - a[n-1], b, m);
  int y2 = m, x2 = position(limit - b[m - 1], a, n);
  if (x1 == x2) {
    return std::max(x1+y1, x2+y2);
  } else {
    return search0(limit, x1,y1,x2,y2, std::max(x1+y1, x2+y2));
  }
}

int main (){
  // int aa[] = {4, 2,4,6,1};
  // int bb[] = {2,1,8,5};

  int aa[] = {12, 21, 102};
  int bb[] = {167, 244, 377, 56, 235, 269, 23};
  int limit = 3696;
  n = sizeof(aa) / sizeof(int);
  m = sizeof(bb) / sizeof(int);
  a = aa; b = bb;

  printf("%d" ,search(limit));
}

#include <string>
#include <iostream>

using namespace std;

struct r1 {
  int i;
  int len; 
};

r1 nextIsland(int n, const char* str) {
  int len = 0;
  int i;
  for (i = 0; i < n; i++) {
    char c = *str; str++;
    if (c == '0') {
      len ++;
    }
    if (c == '1' && len != 0) {
      break;
    }

  }
  return r1{i, len};
}

int max(int a, int b) { return (a < b) ? b : a; }

int secondBig(int a, int b, int c, int d) {
  if (a > b && a >c && a > d) {
    return max(max(b,c),d);
  } else if ( b > a && b > c && b>d) {
    return max(a,max(c,d));
  } else if (c > a && c > b && c >d) {
    return max(a, max(b, d));
  }
  return max(max(a,b), c);
}

string solution(int len, const char* str){
  int lo = 0, le = 0, pos = 0;
  int second = 0;

  while (pos<len) {
    r1 res = nextIsland(len, str);
    if (res.len % 2 == 0) {
      second = secondBig(le, lo, res.len, second);
      le = max(le, res.len);
    } else {
      second = secondBig(le, lo, res.len, second);
      lo = max(lo, res.len);
    }
    pos += res.i;
    str = str + res.i;
  }
  if (lo > le && lo/2 >= second)
    return "A";
  return "B";
}

int main() {
  string problem = "10001001";
  string answer = solution(problem.length(), problem.c_str());
  cout << answer << endl;	
}

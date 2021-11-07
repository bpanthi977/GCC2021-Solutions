#include <iostream>
#include <unordered_map>
#include <set>

int N, R, gMin, gMax, max1, max2, max3;
int *depart;
int *gid;
int *realId; 
int gCount = 0;
typedef struct {
  int id;
  int d1, d2, d3, total;
} group;
group *groups;

int findRoot(int id) {
  int id2 = realId[id];
  if (id2 == id)
    return id;
  else {
    return realId[id] = findRoot(id2);
  }
}

void addMember(int id, int e) {
  group *g = &(groups[id]);
  int d = depart[e];
  if ((g->d1 == max1 && d == 1) || (g->d2 == max2 && d == 2) || (g->d3 == max3 && d == 3)){
    return;
  }
  if (g->d1 + g->d2 + g->d3 == gMax)
    return;

  g->d1 += (d == 1);
  g->d2 += (d == 2);
  g->d3 += (d == 3);
  g->total++;
  gid[e] = id;
}

void newGroup(int e1, int e2) {
  gCount++;
  realId[gCount] = gCount;
  gid[e1] = gCount;
  int d = depart[e1];
  groups[gCount] = group{gCount, (d == 1), (d == 2), (d == 3), 1};
  addMember(gCount, e2);
}

void Union(int id1, int id2){
  if (id1 == id2)
    return;
  group *g1 = &groups[id1], *g2 = &groups[id2];
  if (g1->d1 + g2->d1 > max1 || g1->d2 + g2->d2 > max2 || g1->d3 + g2->d3 > max3 || g1->total + g2->total > gMax)
    return;
  g1->d1 += g2->d1;
  g1->d2 += g2->d2;
  g1->d3 += g2->d3;
  g1->total += g2->total;
  g2 = NULL;
  realId[id2] = id1;
}

void request(int e1, int e2){
  int gid1 = gid[e1], gid2 = gid[e2];
  if (gid1 == 0 && gid2 == 0) {
    newGroup(e1,e2);
  } else if (gid1 == 0 && gid2 != 0) {
    addMember(findRoot(gid2), e1);
  } else if (gid2 == 0 && gid1 != 0) {
    addMember(findRoot(gid1), e2);    
  } else {
    Union(findRoot(gid1), findRoot(gid2));
  }
}


int main() {
  using namespace std;
  cin >> N >> R >> gMin >> gMax >> max1 >> max2 >> max3;

  unordered_map<string, int> employeeId;
  unordered_map<int, string> names; 
  depart = (int *)malloc(N * sizeof(int));
  gid = (int *)malloc(N * sizeof(int)) - 1;
  realId = (int *)malloc(N * sizeof(int)) - 1;
  groups = (group *) malloc(((N<R)? N : R) * sizeof(group)) -1;
  for (int i=0; i<N; i++){
    string name;
    int dep; 
    cin >> name >> dep;
    employeeId[name] = i;
    names[i] = name;
    depart[i] = dep;
  }

  for (int i=0; i<R; i++){
    string name1, name2;
    cin >> name1 >> name2;
    request(employeeId[name1], employeeId[name2]);
  }

  int max = 0;
  for (int i=1; i<= gCount; i++){
    group *g = &(groups[i]);
    if (g != NULL && g->total > max) {
      max = g->total;
    } 
  }

  if (max < gMin){
    printf("no groups\n");
    return 1;
  }

  set<string> finalNames;
  for (int i = 0; i < N; i++) {
    if (gid[i] != 0) {  
      int id = findRoot(gid[i]);
      group *g = &(groups[id]);
      if (g->total == max) {
	finalNames.insert(names[i]);
      }
    }
  }

  for (auto name : finalNames){
    cout << name << endl;
  }
  
  return 1; 
}

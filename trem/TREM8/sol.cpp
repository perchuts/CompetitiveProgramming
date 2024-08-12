#line 1 "playground_A.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
template<class T> inline bool chmax(T& a, const T& b) {if (a<b) {a=b; return true;} return false;}
template<class T> inline bool chmin(T& a, const T& b) {if (b<a) {a=b; return true;} return false;}
const int INTINF = 1000001000;
const int INTMAX = 2147483647;
const ll LLMAX = 9223372036854775807;
const ll LLINF = 1000000000000000000;

#line 1 "/home/samejima/CompetitiveProgramming/library/graph/graph_template.hpp"



#line 5 "/home/samejima/CompetitiveProgramming/library/graph/graph_template.hpp"
template <typename T>
struct Edge {
  int from; int to;
  T cost;

  Edge(int _from, int _to, T _cost) : from(_from), to(_to), cost(_cost) {}

  // unweighted
  Edge(int _from, int _to) : from(_from), to(_to), cost(T(1)) {}

};


template <typename T>
struct Graph : vector<vector<Edge<T>>> {

  using vector<vector<Edge<T>>>::vector; // inherit constructors

  void add_edge(int i, Edge<T> e) {
    (*this)[i].push_back(e);
  }

  // weighted
  void add_edge(int _from, int _to, T _cost) {
    (*this)[_from].push_back(Edge(_from, _to, _cost));
  }

  // unweighted
  void add_edge(int _from, int _to) {
    (*this)[_from].push_back(Edge(_from, _to, T(1)));
  }

};


#line 13 "playground_A.cpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N; cin >> N;
  Graph<int> graph(N);
  for(int i=0; i<N; i++) {
    int c; cin >> c;
    for(int j=0; j<c; j++) {
      int pij; cin >> pij;
      pij--;
      graph.add_edge(i,pij);
    }
  }

  vector<int>ans;
  vector<bool> visited(N, false);

  auto dfs = [&] (auto self, int v) -> void {
    visited[v] = true;
    for (Edge e : graph[v]) {
      if (visited[e.to] == false) self(self, e.to);
    }

    ans.push_back(v);
    return;
  };

  dfs(dfs, 0);

  for (int a : ans ) {
    if (a != 0)  cout << a + 1 << " ";
  } cout << endl;

}

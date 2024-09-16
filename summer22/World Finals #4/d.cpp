#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int t, n, p;
set<ll> s;
int pp[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

void solve(int i, int x, ll v) {
  s.insert(v);
  if (x < pp[i]) return;
  solve(i, x-pp[i], (v*pp[i])%p);
  solve(i+1, x, v);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> t; while (t--) {
    cin >> n >> p;
    s.clear();
    solve(0, n, 1);
    cout << s.size() << '\n';
  }//s
}
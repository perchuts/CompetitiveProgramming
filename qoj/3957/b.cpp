#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

const int N = 1e5 + 3;

vector<int> graph[N];
int parent[N], depth[N];

int32_t main() {_
      int n, k;
      cin >> n >> k;
      for(int i = 2; i <= n; ++i){
            int x;
            cin >> x;
            graph[x].pb(i);
            parent[i] = x;
      }

      vector<int> rem(n+1, k);

      int ans = 0;
      vector<int> v;

      function<void(int)> dfs = [&](int u){
            for(int v: graph[u]){
                  dfs(v);
                  rem[u] = min(rem[u], rem[v]-1);
            }
            if(rem[u] == 1 || u == 1){
                  ++ans;
                  v.pb(u);
                  rem[u] = k+1;
            }
      };

      dfs(1);
      cout << ans << endl;
      for(int x: v) cout << x << " ";
      cout << endl;
}

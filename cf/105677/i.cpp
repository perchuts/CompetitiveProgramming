#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
    int n; cin >> n;
    vector<vector<int>> gr(n);
    vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
        cin >> deg[i];
        for (int j = 0; j < deg[i]; ++j) {
            int u; cin >> u;
            --u;
            gr[u].pb(i);
        }
    }
    queue<int> q;
    vector<int> dp(n);
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 0) q.push(i), dp[i] = 1;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : gr[u]) {
            deg[v]--;
            dp[v] = max(dp[v], dp[u]+1);
            if (deg[v] == 0) q.push(v);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (dp[i] == n) {
            cout << 1 << endl;
            exit(0);
        }
    }
    cout << 0 << endl;
}

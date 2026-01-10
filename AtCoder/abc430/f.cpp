#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<vector<vector<int>>> g(2, vector<vector<int>>(n));
    for (int i = 0; i < n-1; ++i) {
        if (s[i] == 'L') {
            g[0][i+1].pb(i);
            g[1][i].pb(i+1);
        } else { 
            g[1][i+1].pb(i);
            g[0][i].pb(i+1);
        }
    }
    vector<vector<int>> see(2, vector<int>(n));
    for (int t = 0; t < 2; ++t) {
        vector<int> deg(n);
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            deg[i] = sz(g[t^1][i]);
            if (deg[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            for (auto v : g[t][u]) {
                deg[v]--;
                see[t][v] += see[t][u] + 1;
                if (deg[v] == 0) q.push(v);
            }
        }
    }
    vector<int> ans(n+1);
    for (int i = 0; i < n; ++i) {
        ans[see[0][i]]++;
        ans[n-see[1][i]]--;
    }
    cout << ans[0] << " ";
    for (int i = 1; i < n; ++i) {
        ans[i] += ans[i-1];
        cout << ans[i] << " ";
    }
    cout << endl;
    // for each i, count the number of distinct nodes can appear as i-th nodes in any topological sort of this graph

}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

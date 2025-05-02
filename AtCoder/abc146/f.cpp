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

void solve(){
    int n, m; cin >> n >> m;
    vector<int> valid(n+1);
    for (int i = 0; i <= n; ++i) {
        char c; cin >> c;
        valid[i] = c - '0';
        valid[i] ^= 1;
    }
    queue<int> q;
    vector<int> dist(n+1, inf);
    q.push(n), dist[n] = 0;
    vector<int> caras;
    vector<vector<int>> onde(n+1);
    onde[0].pb(n);
    for (int i = 0; i < n; ++i) if (valid[i]) caras.pb(i);
    while (!q.empty()) {
        int i = q.front(); q.pop();
        while (!caras.empty() and i-m <= caras.back()) {
            int k = caras.back(); caras.pop_back();
            dist[k] = dist[i]+1;
            onde[dist[k]].pb(k);
            q.push(k);
        }
    }
    if (dist[0] == inf) {
        cout << -1 << endl;
        exit(0);
    }
    int cur = 0, want = dist[0]-1;
    while (cur != n) {
        int prox = inf;
        for (auto x : onde[want]) {
            if (x > cur) ckmin(prox, x);
        }
        cout << prox - cur << ' ';
        want--, cur = prox;
    }
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

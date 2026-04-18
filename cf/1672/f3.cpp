#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x, --x;
    for (auto& x : b) cin >> x, --x;
    vector<int> freq(n);
    for (int i = 0; i < n; ++i) freq[a[i]]++;
    int mx = *max_element(all(freq));
    if (mx * 2 > n) {
        bool ok = 1;
        for (int i = 0; i < n; ++i) {
            ok &= (freq[a[i]] == mx or freq[b[i]] == mx);
        }
        cout << (ok ? "AC" : "WA") << endl;
        return;
    }
    int forb = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] == b[i]) {
            cout << "WA" << endl;
            return;
        }
        if (freq[a[i]] == mx) forb = a[i];
    }
    vector<vector<int>> g(n);
    vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
        if (a[i] == forb or b[i] == forb) continue;
        g[b[i]].pb(a[i]);
        deg[a[i]]++;
    }
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 0) q.push(i);
    }
    int foi = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        foi++;
        for (auto v : g[u]) {
            deg[v]--;
            if (deg[v] == 0) q.push(v);
        }
    }
    cout << (foi == n ? "AC" : "WA") << endl;
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


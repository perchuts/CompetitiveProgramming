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
    int n, m; cin >> n >> m;
    vector<int> p(n+m), vis(n+m);
    for (auto& x : p) cin >> x, --x;
    vector<vector<int>> cycles;
    for (int i = 0; i < n+m; ++i) {
        if (vis[i]) continue;
        int j = i;
        vector<int> cyc;
        while (!vis[j]) cyc.pb(j), vis[j] = true, j = p[j];
        cycles.pb(cyc);
    }
    int cost = 0, t1 = 0, t2 = 0;
    for (auto x : cycles) {
        if (sz(x) == 1) continue;
        cost += sz(x) - 1;
        int t = 0;
        for (auto y : x) {
            if (y < n) t |= 1;
            else t |= 2;
        }
        if (t == 1) t1++;
        if (t == 2) t2++;
    }
    
    cout << cost + 2*max(t1,t2) << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

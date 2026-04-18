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
    vector<int> pos(n);
    for (auto& x : pos) cin >> x;
    int m, k; cin >> m >> k;
    vector<int> a(m);
    for (auto& x : a) cin >> x, --x;
    vector<int> p(n); iota(all(p), 0);
    auto ans = p;
    // p[i]-p[i-1]
    // operacao no i swappa i+1 com o i
    for (auto x : a) swap(p[x], p[x+1]);
    while (k) {
        if (k & 1) {
            vector<int> nans(n);
            for (int i = 0; i < n; ++i) nans[i] = p[ans[i]];
            ans = nans;
        }
        vector<int> np(n);
        for (int i = 0; i < n; ++i) np[i] = p[p[i]];
        p = np, k /= 2;
    }
    int cur = pos[0];
    cout << pos[0] << ".0" << endl;
    for (int i = 1; i < n; ++i) {
        cur += pos[ans[i]] - pos[ans[i]-1];
        cout << cur << ".0" << endl;
    }
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

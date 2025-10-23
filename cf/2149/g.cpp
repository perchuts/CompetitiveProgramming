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
    int n, q; cin >> n >> q;
    vector<int> a(n), vals;
    for (auto& x : a) cin >> x, vals.pb(x);
    sort(all(vals)), vals.erase(unique(all(vals)), end(vals));
    int m = sz(vals);
    vector<vector<int>> freq(m);
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        x = lower_bound(all(vals), x) - begin(vals);
        a[i] = x;
        freq[x].pb(i);
    }
    int tries = 50;
    auto contar = [&] (int l, int r, int k) { return upper_bound(all(freq[k]), r) - lower_bound(all(freq[k]), l); };
    vector<int> nice(n);
    while (q--) {
        int l, r; cin >> l >> r;
        --l, --r;
        vector<int> ans;
        for (int j = 0; j < tries; ++j) {
            int k = a[rnd(l, r)];
            if (contar(l, r, k) * 3 > r-l+1 and nice[k] == 0) {
                nice[k] = 1; 
                ans.pb(k);
            }
        }
        if (ans.empty()) cout << -1 << endl;
        else {
            sort(all(ans));
            for (auto x : ans) {
                cout << vals[x] << ' ';
                nice[x] = 0;
            }
            cout << endl;
        }
    }
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

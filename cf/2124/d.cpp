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
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> b = a;
    sort(all(b));
    auto tentar = [&] (int tam) {
        if (tam == 0) return true;
        vector<int> c, ids;
        for (int i = 0; i < n; ++i) {
            if (a[i] < b[tam-1]) c.pb(a[i]), ids.pb(i);
        }
        for (int j = 0; j < sz(c); ++j) {
            if (c[j] != c[sz(c)-1-j]) return false;
        }
        vector<int> qtds;
        int cur = 0, qt = 0;
        for (int i = 0; i < n; ++i) {
            if (cur != sz(ids) and i == ids[cur]) {
                qtds.pb(qt);
                qt = 0;
                cur++;
            }
            if (a[i] == b[tam-1]) qt++;
        }
        qtds.pb(qt);
		int tot = 0;
        for (int i = 0; i < (1+sz(qtds))/2; ++i) {
            if (i == sz(qtds)-1-i) tot += qtds[i];
            else tot += 2*min(qtds[i], qtds[sz(qtds)-1-i]);
        }
        return (tot + sz(c) >= tam);
    };
    cout << (tentar(k) or tentar(k-1) ? "YES" : "NO") << endl;
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

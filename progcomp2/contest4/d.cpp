#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i]; 
    // vou ter uma permutacao 0...n-1.
    vector<int> mx(n+5), qt(n+5);
    for (int i = 1; i <= n; ++i) mx[a[i]] = 1, qt[a[i]]++;
    int mex = 0;
    auto upd = [&] () {
        while (mx[mex]) mex++;
    };
    upd();
    vector<int> ops;
    while (mex != n) {
        for (int i = 1; i <= n; ++i) {
            if (a[i] > mex or qt[a[i]] > 1) {
                ops.pb(i);
                qt[a[i]]--;
                mx[a[i]] = (qt[a[i]] != 0);
                qt[mex]++;
                mx[mex] = 1;
                a[i] = mex;
                upd();
                break;
            }
        }
    }
    //
    while (true) {
        bool ok = true;
        for (int i = 1; i < n; ++i) ok &= (a[i] <= a[i+1]);
        if (ok) break;
        vector<int> onde(n+1);
        for (int i = 1; i <= n; ++i) onde[a[i]] = i;
        auto prox = a;
        // 0 1 2 3 4
        // 3 1 2 0 4
        for (int i = n; ; --i) {
            if (a[i] != i-1) {
                int cur = i;
                do {
                    ops.pb(cur);
                    int prox = a[cur]+1;
                    a[cur] = cur-1, cur = prox;
                } while (cur != i);
                ops.pb(cur);
                break;
            }
        }
    }
    cout << sz(ops) << endl;
    for (auto x : ops) cout << x << ' ';
    cout << endl;
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

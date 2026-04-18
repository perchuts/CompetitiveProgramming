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
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    bool ok = 1;
    vector<int> comp(n); iota(all(comp), 0);
    for (int i = 0; i < n-k; ++i) {
        if (a[i] == a[i+k]) {
            // estou forcando b[i] == b[i+k]
            comp[i+k] = comp[i];
        } else {
            ok &= (b[i] == -1 or a[i] == b[i]);
            ok &= (b[i+k] == -1 or a[i+k] == b[i+k]);
            if (b[i] == -1) b[i] = a[i];
            if (b[i+k] == -1) b[i+k] = a[i+k];
        }
    }
    vector<int> val(n, -1);
    for (int i = 0; i < n; ++i) {
        if (b[i] != -1) {
            if (val[comp[i]] == -1) {
                val[comp[i]] = b[i];
            } else if (val[comp[i]] != b[i]) {
                cout << "NO" << endl;
                return;
            }
        }
    }
    for (int i = 0; i < n; ++i) b[i] = val[comp[i]];
    vector<int> occ(n+1);
    for (int i = 0; i < k; ++i) occ[a[i]]++;
    for (int i = 0; i < k; ++i) {
        if (b[i] != -1) {
            ok &= (occ[b[i]] != 0);
            occ[b[i]]--;
        }
    }
    cout << (ok ? "YES" : "NO") << endl;
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

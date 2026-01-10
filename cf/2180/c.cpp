#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

int solve(int n, int k) {
    if (k&1) {
        for (int i = 0; i < k; ++i) cout << n << ' ';
        cout << endl;
        return 0;
    }
    vector<int> atv;
    vector<int> pode(30, 1), qt(30);
    for (int i = 29; ~i; --i) if (n >> i & 1) atv.pb(i), pode[i] = 0;
    vector<int> ans(k, n);
    for (int i = 0; i < sz(atv); ++i) {
        ans[min(i, k-1)] -= (1 << atv[i]);
    }
    for (int i = 0; i < min(sz(atv), k); ++i) {
        for (int j = atv[i]-1; j >= 0; --j) qt[j]++;
    }
    for (int i = 0; i < 30; ++i) {
        if ((n >> i & 1)) continue;
        for (int j = 1; j < qt[i]; j += 2) {
            ans[j] += (1 << i);
            ans[j-1] += (1 << i);
        }
    }
    int s = 0;
    for (auto x : ans) cout << x << " ";    
    cout << endl;
    return s;
}

int brute(int n, int k) {
    int ss = -1;
    vector<int> ans;
    for (int a = 0; a <= n; ++a) {
        for (int b = a; b <= n; ++b) {
            for (int c = b; c <= n; ++c){ 
                for (int d = c; d <= n; ++d){ 
                    if ((a^b^c^d) == n and ckmax(ss, a+b+c+d)) {
                        ans = {a, b, c, d};
                    }
                }
            }
        }
    }
    cout << "brute: ";
    for (auto x : ans) cout << bitset<7>(x) << ' ';
    cout << endl;
    return ss;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        solve(n, k);
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 63), k = 4;
        int my = solve(n, k), ans = brute(n, k);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << k << endl;
            cout << "n = " << bitset<7>(n) << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

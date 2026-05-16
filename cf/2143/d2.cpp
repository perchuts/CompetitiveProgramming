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

inline void add(int& x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

struct Bit {
    vector<int> bit;
    int n;
    Bit (int n_) {
        n = n_;
        bit.resize(n_+1);
    }
    void insert(int x, int k) {
        while (x <= n) add(bit[x], k), x += x & (-x);
    }
    int query(int x) {
        int ans = 0;
        while (x) add(ans, bit[x]), x -= x & (-x);
        return ans;
    }
    int Q(int l, int r) {
        return (query(r) - query(l-1) + mod) % mod;
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> dp(n+1);
    int ans = 1;
    vector<Bit> bits(n+1, Bit(n));
    for (int i = 1; i <= n; ++i) {
        dp[i] = 1;
        for (int j = 1; j < i; ++j) if (a[j-1] <= a[i-1]) add(dp[i], dp[j]);
        add(ans, dp[i]);
        for (int j = 1; j < i; ++j) {
            if (a[i-1] == a[j-1]) continue;
            int eu = 0;
            if (a[i-1] < a[j-1]) {
                eu = dp[j];
                add(eu, bits[j].Q(1, a[i-1]));
            } else {
                add(eu, bits[j].Q(a[j-1]+1, a[i-1]));
            }
            bits[j].insert(a[i-1], eu);
            bits[i].insert(a[j-1], eu);
            add(ans, eu);
        }
    }
    cout << ans << endl;
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

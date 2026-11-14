#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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

int solve(int n, int s, int k, vector<int> a) {
    const int lim = 100000;
    bitset<200005> dp;
    dp[0] = 1;
    while (s != 0) {
        bitset<200005> ndp;
        if (n & 1) {
            bitset<200005> aux;
            for (auto x : a) aux ^= (dp<<x);
            dp = aux;
        } 
        for (int j = 0; j <= 2*lim; ++j) {
            if ((j & 1) == (s & 1)) ndp[j/2] = dp[j];
        }
        swap(dp, ndp);
        s /= 2;
        n /= 2;
    }
    return dp[0];
}

int brute(int n, int s, int k, vector<int> a) {
    map<ii, int> dp;
    auto solve = [&] (auto&& self, int N, int S) -> int {
        if (dp.count({N, S})) return dp[{N, S}];
        if (N == 0) return S == 0;
        if (N & 1) {
            for (int i = 0; i < k and a[i] <= S; ++i) {
                if ((S - a[i]) % 2 == 0) dp[{N, S}] ^= self(self, N/2, (S - a[i])/2);
            }
        } else {
            if (S % 2 == 0) dp[{N, S}] = self(self, N/2, S/2);
        }
        return dp[{N, S}];
    };
    return solve(solve, n, s);
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, s, k; cin >> n >> s >> k;
        vector<int> a(k);
        for (auto& x : a) cin >> x;
        cout << solve(n, s, k, a) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 10), s = rnd(1, 10), k = 2;
        vector<int> a(k);
        a[0] = 0;
        a[1] = rnd(1, s);
        int my = solve(n, s, k, a), ans = brute(n, s, k, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << s << " " << k << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

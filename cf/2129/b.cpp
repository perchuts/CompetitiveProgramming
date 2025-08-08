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

void solve() {
    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x, --x;
    vector<int> maior(n), pos(n);
    for (int i = 0; i < n; ++i) {
        pos[p[i]] = i;
        for (int j = i + 1; j < n; ++j) {
            maior[p[i]] += (p[j] > p[i]);
        }
    }
    vector<int> dp(n+1, inf);
    dp[0] = 0;
    for (int aa = n-1; ~aa; --aa) {
        vector<int> ndp(n+1, inf);
        int antes = n-1-aa-maior[aa];
        int i = pos[aa];
        for (int j = 0; j <= n; ++j) {
            ndp[j] = dp[j] + antes;
            if (j != 0) ckmin(ndp[j], dp[j-1] + maior[aa]);
        }
        swap(dp, ndp);
    }
    int ans = inf;
    for (int i = 0; i <= n; ++i) ckmin(ans, dp[i]);
    cout << ans << endl;
}

iii brute(int n, vector<int> p) {
    int ans = inf;
    int m = 0;
    int comps = inf;
    for (int i = 0; i < (1 << n); ++i) {
        vector<int> np(n);
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) np[j] = 2*n-2-p[j];
            else np[j] = p[j];
        }
        int invs = 0;
        for (int a = 0; a < n; ++a) {
            for (int b = a + 1; b < n; ++b) {
                invs += (np[a] > np[b]);
            }
        }
        int myc = 0, lst = 0;
        for (int j = 0; j < n; ++j) {
            int eu = (i >> j & 1);
            if (lst == 0 and eu == 1) myc++;
            lst = eu;
        }
        if (ckmin(ans, invs)) m = i, comps = myc;
        else if (ans == invs and ckmin(comps, myc)) m = i;
    }
    return {ans, m, comps};
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (t <= 100) {
        //int my = solve(), ans = brute();
        int n = rnd(1, 8);
        vector<int> p(n); iota(all(p), 0); shuffle(all(p), rng);
        auto [best, mask, cc] = brute(n, p);
        t++;
        if (cc <= 1) continue;
        cout << n << endl;
        for (auto x : p) cout << x + 1 << ' ';
        cout << endl;
        cout << "opt: " << best << ' ' << bitset<20>(mask) << endl;
        //if (my != ans) {
        //    cout << "Wrong answer on test " << t << endl;
        //    cout << "Your output: " << my << endl;
        //    cout << "Answer: " << ans << endl;
        //    exit(0);
        //}
        //cout << "Accepted on test " << t++ << endl;
        t++;
    }
#endif
}

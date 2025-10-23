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

int solve(int n, int k, vector<int> v) {
    vector<int> dp(n), cnt(n);
    int pL = 0, pR = 0, tot = 0;
    auto add = [&] (int x) { tot += cnt[v[x]]; cnt[v[x]]++; };
    auto rem = [&] (int x) { cnt[v[x]]--; tot -= cnt[v[x]]; };
    for (int i = n-1; ~i; --i) add(i), dp[i] = tot;
    for (int i = 0; i < n; ++i) cnt[i] = 0; tot = 0;
    for (int turn = 0; turn < k-1; ++turn) {
        queue<array<int, 4>> q;
        vector<int> ndp(n, 1e18);
        q.push({0, n-1, 0, n-1});
        while (!q.empty()) {
            queue<array<int, 4>> nq;
            while (!q.empty()) {
                auto arr = q.front(); q.pop();
                int l = arr[0], r = arr[1], ox = arr[2], oy = arr[3], md = (l+r)/2, opt = -1;
                while (pL < md) rem(pL++);
                while (md < pL) add(--pL);
                while (pR <= ox) add(pR++);
                while (pR > ox+1) rem(--pR);
                while (true) {
                    if (ckmin(ndp[md], (pR == n ? 0 : dp[pR]) + tot)) opt = pR-1;
                    if (pR <= oy) add(pR++);
                    else break;
                }
                assert(opt != -1);
                if (l <= md-1) nq.push({l, md-1, ox, opt});
                if (md+1 <= r) nq.push({md+1, r, opt, oy});
            }
            swap(q, nq);
        }
        swap(dp, ndp);
    }
    return dp[0];
}

int brute(int n, int k, vector<int> v) {
    vector<vector<int>> dp(n+1, vector<int>(k+1, 1e18));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        vector<int> cnt(n);
        cnt[v[i-1]]++;
        int tot = 0;
        for (int w = i-1; ~w; --w) {
            for (int j = 1; j <= k; ++j) {
                ckmin(dp[i][j], dp[w][j-1]+tot);
            }
            if (w) tot += cnt[v[w-1]], cnt[v[w-1]]++;
        }
    }
    int ans = 1e18;
    for (int i = 1; i <= k; ++i) ckmin(ans, dp[n][i]);
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for (auto& x : v) cin >> x, --x;
    cout << solve(n, k, v) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 100), k = rnd(1, 100);
        vector<int> v(n);
        for (auto& x : v) x = rnd(0, n-1);
        int my = solve(n, k, v), ans = brute(n, k, v);
        
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << k << endl;
            for (auto x : v) cout << x + 1 << ' ';
            cout << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

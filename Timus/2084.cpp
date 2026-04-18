#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 1e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
int dp[201][101][201];
iii rec[201][101][201];
pair<int, vector<int>> solve(int x, int n, vector<int> a, vector<int> b) {
    //    int tot = 0;
    //    for (int i = 0; i < n; ++i) {
    //      X = max(0, X - a[p[i]]);
    //      tot += max(0, b[p[i]] - X);
    //    }
    //    useless: b[p[i]] <= X
    //    useless go to beginning
    //    must exploit X <= 200
    //    uma vez fixado quem vai morrer, vou simplesmente pegar do maior pro menor
    vector<int> p(n); iota(all(p), 0);
    sort(all(p), [&] (int xy, int y) { return a[xy] > a[y]; });
    // dp[idx][valor_do_x][falta_pra_completar_0]
    for (int i = 0; i <= x+100; ++i) for (int j = 0; j <= x; ++j) dp[0][j][i] = -inf;
    for (int i = 0; i <= x+100; ++i) dp[0][max(0, x-i)][i] = 0;
    // tem que ser push forward
    for (int i = 1; i <= n; ++i) {
        int id = p[i-1];
        for (int j = 0; j <= x; ++j) for (int k = 0; k <= x+100; ++k) dp[i][j][k] = -inf;
        for (int j = 0; j <= x; ++j) {
            for (int k = 0; k <= x+100; ++k) {
                // olhe para esse ponto.

                if (k >= a[id] and ckmax(dp[i][j][k-a[id]], dp[i-1][j][k])) rec[i][j][k-a[id]] = {j, k, 0};

                if (ckmax(dp[i][max(0, j-a[id])][k], dp[i-1][j][k] + max(0, b[id]-max(0, j-a[id])))) rec[i][max(0, j-a[id])][k] = {j, k, 1};

            }
        }
    }
    int ans = -1;
    int s1, s2;
    for (int i = 0; i <= x; ++i) if (ckmax(ans, dp[n][i][0])) s1 = i, s2 = 0;
    vector<int> v1, v;
    for (int i = n; i >= 1; --i) {
        auto [ns1, ns2, tipo] = rec[i][s1][s2];
        if (tipo) v1.pb(p[i-1]);
        else v.pb(p[i-1]);
        s1 = ns1, s2 = ns2;
    }
    reverse(all(v1));
    for (auto y : v1) v.pb(y);
    return make_pair(ans, v);
}

int brute2(int x, int n, vector<int> a, vector<int> b) {
    int ans = 0;
    for (int i = 0; i < (1 << n); ++i) {
        vector<int> v;
        int xx = x;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) v.pb(j);
            else xx = max(0, xx - a[j]);
        }
        sort(all(v), [&] (int xy, int y) { return a[xy] > a[y]; });
        int cur = 0;
        for (auto j : v) {
            xx = max(0, xx - a[j]);
            cur += max(0, b[j] - xx);
        }
        ckmax(ans, cur);
    }
    return ans;
}

int brute(int x, int n, vector<int> a, vector<int> b) {
    vector<int> p(n); iota(all(p), 0); 
    int ans = 0;
    do { 
        int cur = 0, xx = x;
        for (auto i : p) xx = max(0, xx - a[i]), cur += max(0, b[i] - xx);
        ckmax(ans, cur);
    } while (next_permutation(all(p)));
    return ans;
}
int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int x, n; cin >> x >> n;
    vector<int> a(n), b(n);
    for (auto& y : a) cin >> y;
    for (auto& y : b) cin >> y;
    auto [val, v] = solve(x, n, a, b);
    cout << val << endl;
    for (auto y : v) cout << y + 1 << " ";
    cout << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 20), x = rnd(1, 50);
        vector<int> a(n), b(n);
        for (auto& y : a) y = rnd(0, x);
        for (auto& y : b) y = rnd(0, 2*x);
        auto [my, my_v] = solve(x, n, a, b);
        int ans = brute2(x, n, a, b);
        int xx = x, cur = 0;
        for (auto i : my_v) {
            xx = max(0, xx - a[i]);
            cur += max(0, b[i] - xx);
        }
        if (my != ans or my != cur) {
            cout << "Wrong answer on test " << t << endl;
            cout << x << " " << n << endl;
            for (auto y : a) cout << y << " ";
            cout << endl;
            for (auto y : b) cout << y << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "order: ";
            for (auto y : my_v) cout << y + 1 << " ";
            cout << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

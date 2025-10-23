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

vector<int> solve(int n, int q, vector<int> qu) {
    int N = n;
    vector<ii> chain = {{1, 0}};
    vector<int> tam = {n};
    int T = 1;
    for (auto& x : qu) {
        if (x == tam.back()) continue;
        if (x < tam.back()) {
            while (T > 1 and x < tam[T-2]) tam.pop_back(), chain.pop_back(), T--;
            if (x == tam[T-1]) continue;
            if (T == 1) n = tam[T-1] = x; 
            else chain.back() = {x / tam[T-2], x % tam[T-2]}, tam.back() = x;
        } else {
            chain.pb({x/tam[T-1], x % tam[T-1]});
            tam.pb(x);
            T++;
        }
    }
    vector<int> ans(N+1), adds, tams = {n};
    vector<vector<ii>> g = {{pair(-1, n)}};
    for (int i = 1; i <= n; ++i) ans[i] = 1;
    auto flush = [&] (int multi = 0) {
        for (auto x : adds) {
            vector<ii> edges;
            edges.pb({sz(g)-1, 1});
            tams.pb(tams.back()+x);
            while (x > n) {
                int i = upper_bound(all(tams), x) - begin(tams) - 1;
                edges.pb({i, x/tams[i]});
                x %= tams[i];
            }
            if (x) edges.pb({-1, x});
            g.pb(edges);
        }
        if (multi) {
            tams.pb(multi*tams.back()), g.pb({{sz(g)-1, multi}});
        }
        int m = sz(g);
        vector<int> dp(m), nans(N+1); dp[m-1] = 1;
        for (int i = m-1; ~i; --i) {
            for (auto [j, w] : g[i]) {
                if (j == -1) nans[w] += dp[i];
                else dp[j] += dp[i] * w;
            }
        }
        for (int i = n-1; i; --i) nans[i] += nans[i+1];
        swap(nans, ans);
        adds.clear();
    };
    for (int i = 1; i < sz(chain); ++i) {
        auto [ki, ri] = chain[i];
        if (ki > 1) flush(ki), adds.pb(ri), flush();
        else adds.pb(ri);
    }
    flush();
    return ans;
}

vector<int> brute(int n, int q, vector<int> qu) {
    vector<int> cur(n); iota(all(cur), 1);
    for (auto x : qu) {
        vector<int> nq;
        for (int i = 0; i < x; ++i) nq.pb(cur[i%sz(cur)]);
        swap(nq, cur);
    }
    vector<int> freq(n+1);
    for (auto x : cur) freq[x]++;
    return freq;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, q; cin >> n >> q;
    vector<int> qu(q);
    for (auto& x : qu) cin >> x;
    auto ans = solve(n, q, qu);
    for (int i = 1; i <= n; ++i) cout << ans[i] << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 30), q = rnd(1, 200);
        vector<int> qu(q);
        for (auto& x : qu) x = rnd(1, 300);
        auto my = solve(n, q, qu);
        auto ans = brute(n, q, qu);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << q << endl;
            for (auto x : qu) cout << x << ' ';
            cout << endl;
            cout << "Your output: ";
            for (int i = 1; i <= n; ++i) cout << my[i] << ' ';
            cout << endl;
            cout << "Answer: ";
            for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

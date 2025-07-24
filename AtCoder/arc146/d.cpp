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

int solve(int n, int m, int k, vector<array<int, 4>> a) {
    vector<int> ans(n, 1), ptr(n);
    vector<vector<iii>> conds(n);
    for (int i = 0; i < k; ++i) a.push_back({a[i][0], a[i][1]-1, a[i][2], a[i][3]-1});
    for (auto arr : a) conds[arr[0]].pb({arr[1], arr[2], arr[3]}), conds[arr[2]].pb({arr[3], arr[0], arr[1]});
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        sort(all(conds[i]));
        if (!conds[i].empty() and get<0>(conds[i][0]) == 0) q.push(i);
    }
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        while (ptr[u] != sz(conds[u])) {
            auto [lixo, v, vv] = conds[u][ptr[u]];
            if (lixo >= ans[u]) break;
            ptr[u]++;
            if (ckmax(ans[v], vv+1)) q.push(v);
        }
    }
    if (*max_element(all(ans)) > m) return -1;
    return accumulate(all(ans), 0LL);
}

int brute(int n, int m, int k, vector<array<int, 4>> a) {
    vector<int> pot(k+1, 1);
    for (int i = 1; i <= k; ++i) pot[i] = 3 * pot[i-1];
    int ans = 1e18;
    for (int msk = 0; msk < pot[k]; ++msk) {
        vector<ii> r(n, make_pair(1, m));
        for (int i = 0; i < k; ++i) {
            int s = (msk/pot[i])%3;
            if (s == 0) {
                ckmin(r[a[i][0]].second, a[i][1]-1);
                ckmin(r[a[i][2]].second, a[i][3]-1);
            } else if (s == 1) {
                ckmin(r[a[i][0]].second, a[i][1]);
                ckmin(r[a[i][2]].second, a[i][3]);
                ckmax(r[a[i][0]].first, a[i][1]);
                ckmax(r[a[i][2]].first, a[i][3]);
            } else {
                ckmax(r[a[i][0]].first, a[i][1]+1);
                ckmax(r[a[i][2]].first, a[i][3]+1);
            }
        }
        int tot = 0;
        for (auto [lx, rx] : r) {
            if (lx > rx) { tot = 1e18; break; }
            tot += lx;
        }
        ckmin(ans, tot);
    }
    if (ans == 1e18) ans = -1;
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, m, k; cin >> n >> m >> k;
    vector<array<int, 4>> a(k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < 4; ++j) cin >> a[i][j];
        a[i][0]--, a[i][2]--;
    }
    cout << solve(n, m, k, a) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 7), m = rnd(1, 10), k = rnd(1, 8);
        vector<array<int, 4>> a(k);
        for (int i = 0; i < k; ++i) {
            a[i][0] = rnd(0, n-1), a[i][2] = rnd(0, n-1);
            a[i][1] = rnd(1, m), a[i][3] = rnd(1, m);
        }
        int my = solve(n, m, k, a), ans = brute(n, m, k, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << ' ' << k << endl;
            for (int i = 0; i < k; ++i) {
                cout << a[i][0]+1 << " " << a[i][1] << " " << a[i][2]+1 << " " <<  a[i][3] << endl;
            }
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

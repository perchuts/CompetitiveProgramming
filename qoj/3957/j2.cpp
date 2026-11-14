#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

const int N = 1000000;
vector<vector<array<int, 2>>> v(N+1);
int solve(int n, vector<iii> z) {


    for (auto [a, b, c] : z) v[c].pb({a, b});

    array<vector<vector<int>>, 2> p;
    int zz = 0;
    for (int i = 1; i <= N; ++i) {
        if (v[i].empty()) continue;
        vector<int> eu;
        priority_queue<int> pq;
        int S = 0;
        for (auto [x, y] : v[i]) S += x, pq.push(y-x);
        int t1 = v[i].size(), t2 = 0;
        eu.pb(S);
        while (!pq.empty()) {
            int x = pq.top(); pq.pop();
            if (t1-1 > t2) x += i;
            if (t1 <= t2) x -= i;
            t1--, t2++;
            S += x;
            eu.pb(S);
        }
        zz += v[i].size();
        p[v[i].size()&1].pb(eu);
    }
    assert(zz == 2*n);
    auto mult = [&] (vector<int> a, vector<int> b) {
        int ta = a.size(), tb = b.size();
        vector<int> c(ta+tb-1);
        for (int i = 2; i < ta; ++i) assert(a[i-1] - a[i-2] >= a[i] - a[i-1]);
        for (int i = 2; i < tb; ++i) assert(b[i-1] - b[i-2] >= b[i] - b[i-1]);
        c[0] = a[0] + b[0];
        int p1 = 1, p2 = 1;
        for (int i = ta-1; i; --i) a[i] -= a[i-1];
        for (int i = tb-1; i; --i) b[i] -= b[i-1];
        for (int i = 1; i < ta+tb-1; ++i) {
            c[i] = c[i-1];
            if (p1 == ta) c[i] += b[p2++];
            else if (p2 == tb) c[i] += a[p1++];
            else {
                if (a[p1] > b[p2]) c[i] += a[p1++];
                else c[i] += b[p2++];
            }
        }
        return c;
    };
    priority_queue<pair<int, vector<int>>> pq;
    for (int i = 0; i < p[1].size(); i += 2) {
        auto c = mult(p[1][i], p[1][i+1]);
        pq.push({-c.size(), c});
    }
    for (auto pol : p[0]) {
        pq.push({-pol.size(), pol});
    }
    while (pq.size() != 1) { 
        auto [t1, x] = pq.top(); pq.pop();
        auto [t2, y] = pq.top(); pq.pop();
        auto Z = mult(x, y);
        pq.push({-Z.size(), Z});
    }
    auto P = pq.top().second;
    int t = P.size();
    for (auto [a, b, c] : z) v[c].clear();
    return P[t/2];
}

int brute(int n, vector<iii> z) {
    vector<int> dp(1);
    int shift = 0;
    

    for (auto [a, b, c] : z) v[c].pb({a, b});

    for (int i = 1; i <= N; ++i) {
        if (v[i].empty()) continue;
        priority_queue<int> pq;
        int S = 0;
        for (auto [x, y] : v[i]) S += x, pq.push(y-x);
        int t1 = v[i].size(), t2 = 0;
        int shift2 = v[i].size();
        vector<int> eu(2*shift2+1, -inf);
        eu[0] = S;
        while (!pq.empty()) {
            int x = pq.top(); pq.pop();
            if (t1-1 > t2) x += i;
            if (t1 <= t2) x -= i;
            t1--, t2++;
            S += x;
            eu[t2-t1+shift2] = S;
        }
        vector<int> ndp(eu.size() + dp.size() - 1, -2*inf);
        for (int j = -shift; j <= shift; ++j) {
            for (int k = -shift2; k <= shift2; ++k) {
                ckmax(ndp[j+k+shift+shift2], dp[j+shift] + eu[k+shift2]);
            }
        }
        swap(dp, ndp);
        shift += shift2;
    }
    for (auto [a, b, c] : z) v[c].clear();
    return dp[shift];
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<iii> z(2*n);
    for (auto& [a, b, c] : z) cin >> a >> b >> c;
    cout << solve(n, z) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 25);
        vector<iii> z(2*n);
        for (auto& [a, b, c] : z) a = rnd(1, 10), b = rnd(1, 10), c = rnd(1, min(2*n, 3LL));
        int my = solve(n, z), ans = brute(n, z);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto [a, b, c] : z) cout << a << " " << b << " " << c << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

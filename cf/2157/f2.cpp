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
vector<int> edge;
vector<ii> solve(int n) {
    int tot = 0;
    edge.resize(n);
    for (int i = 0; i < n; ++i) edge[i] = 0;
    vector<int> deg(n+1);
    deg[n] = inf;
    const int lim = 10;
    for (int i = 1; i < n; ++i) {
        int p = i & (-i);
        p = min(p, (1LL << lim));
        edge[i] = min(n - i, p);
        tot += edge[i];
    }
    vector<ii> ans;
    for (int turn = 0; turn < lim; ++turn) {
        for (int i = n-1; i >= 1; --i) {
            if ((i & (-i)) == (1 << turn)) ans.pb({i, edge[i]});
        }
    }
    for (int i = 1; (i << (lim)) < n; ++i) ans.pb({(i << (lim)), edge[(i << (lim))]});
    int penalty = 0;
    for (int i = 1; i < sz(ans); ++i) {
        int z = (ans[i].first > ans[i-1].first);
        penalty += z;
        tot += 1000 * z;
    }
    cout << penalty << ' ';
    cout << tot << endl;
    return ans;
}

bool checker(int n, vector<ii> ans) {
    vector<int> onde(n);
    for (int i = 0; i < n; ++i) onde[ans[i].first] = i;
    return true;
    for (int i = 1; i < n; ++i) {
        int coins = 1000000, lvl = i, lst = inf;
        for (auto [x, y] : ans) {
            if (x <= lst) coins -= y;
            else coins -= y - 1000;
            if (x == lvl) lvl += y;
        }
        if (lvl < n) {
            cout << "L sup: " << i << endl;
            cout << bitset<15>(lvl) << endl;
            int cur = i;
            return false;
        } else {
            cout << "OK " << i << endl;
        }
    }
    cout << "W inf " << endl;
    return true;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    auto ans = solve(n);
    checker(n, ans);
    //cout << sz(ans) << endl;
    //for (auto [x, y] : ans) cout << x << ' ' << y << endl;
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

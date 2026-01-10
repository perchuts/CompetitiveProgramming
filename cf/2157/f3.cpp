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
    vector<int> deg(n+1);
    deg[n] = inf;
    int t = 500;
    for (int i = 1; i < n; ++i) {
        if (i % t == 0) {
            edge[i] = t;
        }
        else edge[i] = 1;
        tot += edge[i];
    }
    vector<int> dep(n);
    vector<vector<int>> caras(n);
    int mx = 0;
    for (int i = 1; i < n; ++i) {
        if (i + edge[i] < n) ckmax(dep[i + edge[i]], dep[i] + 1);
        caras[dep[i]].pb(i);
        ckmax(mx, dep[i]);
    }
    vector<ii> ans;
    for (int i = 0; i < n; ++i) {
        reverse(all(caras[i]));
        for (auto j : caras[i]) ans.pb({j, edge[j]});
    }
    int bad = 0;
    for (int i = 1; i < sz(ans); ++i) {
        int penis = (ans[i].first > ans[i-1].first ? 1000 : 0);
        tot += penis, bad += penis/1000;
    }
    cout << tot << ' ' << mx << ' ' << bad << endl;
    exit(0);
    return ans;
}

bool checker(int n, vector<ii> ans) {
    vector<int> onde(n);
    for (int i = 0; i < n; ++i) onde[ans[i].first] = i;
    for (int i = 1; i < 250000; ++i) {
        int coins = 1000000, lvl = i, lst = inf;
        for (auto [x, y] : ans) {
            if (x <= lst) coins -= y;
            else coins -= y - 1000;
            if (x == lvl) lvl += y;
        }
        if (lvl < n) {
            int cur = i;
            cout << "L sup: " << i << endl;
            cout << lvl << endl;
            for (int j = 0; j < 20; ++j) {
                cout << cur << ' ';
                cur += edge[cur];
            }
            exit(0);
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
    cout << sz(ans) << endl;
    for (auto [x, y] : ans) cout << x << ' ' << y << endl;
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


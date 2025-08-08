#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int long long
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

vector<array<int, 2>> kernelize(int n, vector<int> a) {
    vector<array<int, 2>> b;
    sort(all(a));
    int lst = 0;
    for (int l = 0, r = 0; l != n; l = r) {
        while (r != n and a[l] == a[r]) r++;
        b.pb({a[l]-lst, r-l}), lst = a[l];
    }
    return b;
}

bool solve(int n, vector<int> a) {
    auto c = kernelize(n, a);
    int sa = 0, sb = 0, m = sz(c), best = 0;
    for (int i = 0; i < m; ++i) sb += c[i][1];
    for (int i = 0; i < m; ++i) {
        sa += c[i][0];
        ckmax(best, min(sb, sa));
        sb -= c[i][1];
    }
    sa = sb = 0;
    for (int i = 0; i < m; ++i) sb += c[i][1];
    for (int i = 0; i < m; ++i) {
        sa += c[i][0];
        int win = (sa + sb) % 2;
        if (best == min(sa, sb) and win) return true;
        sb -= c[i][1];
    }
    return false;
}
bool brute(int n, vector<int> a) {
    map<vector<int>, bool> win;
    auto go = [&] (auto&& self, vector<int> cur) -> bool {
        if (win.count(cur)) return win[cur];
        auto mee = cur;
        int mx = 0, id = -1;
        for (int i = 0; i < n; ++i) {
            if (ckmax(mx, cur[i])) id = i;
        }
        if (mx == 0) return win[cur] = 1;
        cur[id] = 0;
        win[mee] |= !(self(self, cur));
        cur[id] = mx;
        for (int i = 0; i < n; ++i) cur[i] = max(0LL, cur[i]-1);
        win[mee] |= !(self(self, cur));
        return win[mee];
    };
    return go(go, a);
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << (solve(n, a) ? "First" : "Second") << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 10);
        int mx = 10;
        vector<int> a(n);
        for (auto& x : a) x = rnd(1, mx);
        int my = solve(n, a), ans = brute(n, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            cout << "Your output: " << (my ? "First" : "Second") << endl;
            cout << "Answer: " << (ans ? "First" : "Second") << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

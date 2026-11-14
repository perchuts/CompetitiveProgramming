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
vector<int> p;
vector<pair<int, vector<int>>> penis;
void solve() {
    int n, d; cin >> n >> d;
    int opt = 1, ans = 1;
    for (auto [val, divs] : penis) {
        if (val % d == 0) continue;
        if (val > n) continue;
        int qt = 1;
        for (auto x : divs) qt *= (x+1);
        if (ckmax(opt, qt)) ans = val;
    }
    cout << ans << endl;
}

int32_t main() {_
    int N = 700;
    vector<int> mark(N);
    for (int i = 2; i < N; ++i) {
        if (mark[i]) continue;
        p.pb(i);
        for (int j = i * i; j < N; j += i) mark[j] = 1;
    }
    const int LIM = 1e18;
    vector<int> factors(sz(p));
    vector<vector<int>> pw(sz(p));
    for (int i = 0; i < sz(p); ++i) {
        pw[i].pb(1);
        while (true) {
            int x = pw[i].back();
            if (x > LIM / p[i]) break;
            pw[i].pb(x * p[i]);
        }
    }
    auto go = [&] (auto&& self, int i, int cur, int val, int flag) -> void {
        if (i == sz(p)) return;
        penis.pb({cur, factors});
        ckmin(val, sz(pw[i]) - 1);
        for (int j = 1; j <= val and cur <= LIM/pw[i][j]; ++j) factors[i] = j, self(self, i+1, cur*pw[i][j], j, flag);
        if (flag == 0) {
            for (int j = val+1; j < sz(pw[i]) and cur <= LIM/pw[i][j]; ++j) factors[i] = j, self(self, i+1, cur*pw[i][j], j, 1);
            factors[i] = 0;
            self(self, i+1, cur, sz(pw[i+1])-1, 1);
        }
        factors[i] = 0;
    };
    go(go, 0, 1, 59, 0);
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
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

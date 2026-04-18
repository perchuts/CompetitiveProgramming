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

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<ii> v;
    int cnt = 1;
    for (int i = 1; i < n; ++i) {
        if (s[i] != s[i-1]) v.pb({cnt, s[i-1] == 'u'}), cnt = 1;
        else cnt++;
    }
    v.pb({cnt, s.back() == 'u'});
    int ans = 0, prdp = 0, can = 0;
    for (int i = sz(v)-2; i >= 0; --i) {
        auto [cnt, tipo] = v[i];
        if (tipo == 0) continue;
        if (i == 0) break;
        if (v[i-1].first < v[i].first or v[i+1].first < v[i].first) { can = 0, prdp = 0; continue; }
        int ndp = 3*cnt;
        if (can and v[i].first+v[i+2].first == v[i+1].first) ndp = 3*cnt+prdp;
        ckmax(ans, ndp);
        prdp = ndp, can = 1;
    }
    cout << ans << endl;
}

int32_t main() {_
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

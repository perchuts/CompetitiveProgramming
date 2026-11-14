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
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> ord(n); iota(all(ord), 0), sort(all(ord), [&] (int x, int y) { if (a[x] == a[y]) return x < y; return a[x] > a[y]; });
    set<int> foi;
    vector<int> cnt(n+1);
    for (int l = 0, r = 0; r != n; l = r) {
        while (r != n and a[ord[l]] == a[ord[r]]) ++r;
        for (int i = l+1; i < r; ++i) {
            auto it = foi.lower_bound(ord[i-1]);
            if (it != end(foi) and (*it) <= ord[i]) {}
            else cnt[ord[i-1]]++, cnt[ord[i]+1]--;
        }
        for (int i = l; i < r; ++i) foi.insert(ord[i]);
    }
    int lp = n, rp = -1, c = 0;
    for (int i = 0; i < n; ++i) {
        c += cnt[i];
        if (!c) ckmin(lp, i), rp = i;
    }
    if (lp == n) {
        cout << 0 << endl;
        return;
    }
    if (lp == rp) {
        cout << 1 << endl;
        cout << lp+1 << " " << (lp ? a[lp-1] : a[lp+1]) << endl;
        return;
    }
    int lb = 0, id = -1;
    for (int i = lp; i <= rp; ++i) if (ckmax(lb, a[i])) id = i;
    for (int i = lp; ~i; --i) {
        if (a[i] >= lb) {
            cout << 1 << endl;
            cout << rp+1 << " " << a[i] << endl;
            return;
        }
    }
    for (int i = rp; i < n; ++i) {
        if (a[i] >= lb) {
            cout << 1 << endl;
            cout << lp+1 << " " << a[i] << endl;
            return;
        }
    }
    set<int> nice;
    int mx = 0;
    for (int i = id-1; ~i; --i) { 
        ckmax(mx, a[i]);
        if (i <= lp and mx == a[i]) nice.insert(mx);
    }
    mx = 0;
    for (int i = id+1; i < n; ++i) {
        ckmax(mx, a[i]);
        if (rp <= i and nice.find(mx) != end(nice) and mx == a[i]) {
            cout << 1 << endl;
            cout << id+1 << " " << mx << endl;
            return;
        }
    }
    cout << 2 << endl;
    cout << 1 << " " << 1000000000 << endl;
    cout << n << " " << 1000000000 << endl;
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

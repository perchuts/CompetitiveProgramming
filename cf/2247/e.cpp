#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define gato

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
    int n, k; cin >> n >> k;
    // (n + 1) * n / 2
    if (k % 2 or k < 2 * (n - 1) or (n * n - (n & 1)) / 2 < k) {
        cout << -1 << endl;
        return;
    }
    vector<int> can, onde(n);
    for (int i = 0; i < n; i += 2) can.pb(i);
    reverse(all(can));
    for (int i = 1; i < n; i += 2) can.pb(i);
    auto build = [&] (int x) {
        vector<int> np;
        for (auto y : can) if (y > x) np.pb(y);
        for (int i = 0; i <= x; ++i) np.pb(i);
        return np;
    };
    auto get = [&] (vector<int> np) {
        for (int i = 0; i < n; ++i) onde[np[i]] = i;
        int tot = 0;
        for (int i = 0; i < n; ++i) tot += abs(onde[i] - onde[(i+1)%n]);
        return tot;
    };
    int l = 0, r = n-1, opt = -1;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (get(build(md)) >= k) opt = md, l = md+1;
        else r = md-1;
    }
    auto p = build(opt);
    if (opt != n-1) {
        int pos = -1;
        for (int i = 0; i < n; ++i) if (p[i] == opt+1) pos = i;
        l = pos, r = n-1;
        int opt2 = pos;
        while (l <= r) { 
            int md = l + (r-l+1)/2;
            auto p2 = p;
            for (int i = pos+1; i <= md; ++i) swap(p2[i], p2[i-1]);
            if (get(p2) >= k) opt2 = md, l = md+1;
            else r = md-1;
        }
        for (int i = pos+1; i <= opt2; ++i) swap(p[i], p[i-1]);
    }
    for (int i = 0; i < n-1; ++i) cout << p[i]+1 << " " << p[i+1]+1 << endl;
}

int32_t main() {_
    int t;  cin >> t;
    while (t--) {
        solve();
    }
}

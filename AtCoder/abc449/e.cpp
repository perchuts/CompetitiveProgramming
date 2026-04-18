#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
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
    int n, m; cin >> n >> m;
    vector<int> a(n+1), freq(m+1), f2(n+1);
    vector<vector<int>> vals(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        freq[a[i]]++;
    }
    for (int i = 1; i <= m; ++i) f2[freq[i]]++, vals[freq[i]].pb(i);
    int need = n, ps = 0;
    vector<int> pts = {n+1};
    for (int i = 0; i < n; ++i) {
        ps += f2[i];
        need += ps;
        pts.pb(need+1);
    }
    int q; cin >> q;
    vector<int> qu(q);
    for (auto& x : qu) cin >> x;
    vector<int> ord(q); iota(all(ord), 0), sort(all(ord), [&] (int x, int y) {
        return qu[x] < qu[y];
    });
    vector<int> ans(q);
    ord_set<int> exist;
    int foi = 0;
    //for (auto x : pts) cout << x << " ";
    //cout << endl;
    for (auto i : ord) {
        int val = qu[i];
        if (val <= n) {
            ans[i] = a[val];
            continue;
        }
        int j = upper_bound(all(pts), val) - begin(pts) - 1;
        while (foi <= j) {
            for (auto k : vals[foi]) exist.insert(k);
            foi++;
        }
        int d = val - pts[j];
        d %= m;
        ans[i] = *exist.find_by_order(d);
        //cout << "query = " << val << ": " << j << " " << d << " ans = " << ans[i] << endl;
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
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

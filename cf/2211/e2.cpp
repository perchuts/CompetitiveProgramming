#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n; cin >> n;
    // 1 indexed
    vector<vector<int>> g(n+1);
    vector<int> a(n+1), par(n+1), ans(n+1), tag(n+1);
    vector<vector<ii>> tr(n+1);
    vector<vector<ii>> changes(n+1);
    for (int i = n; i >= 1; --i) {
        cin >> a[i];
        int k; cin >> k;
        g[i].resize(k);
        ans[i] = 1;
        for (auto& x : g[i]) cin >> x, par[x] = i, ans[i] += ans[x];
        if (k == 0) {
            tr[i] = { {a[i], i} };
            changes[i] = { {i, a[i]} };
            tag[i] = a[i];
            cout << ans[i] << endl;
            continue;
        }
        sort(all(g[i]), [&] (int x, int y) { return sz(g[x]) > sz(g[y]); });
        swap(tr[g[i][0]], tr[i]);
        tag[i] = gcd(a[i], tag[g[i][0]]);
        bool ok = 0;
        for (int j = 1; j < sz(g[i]); ++j) {
            for (auto [x, w] : tr[g[i][j]]) {
                if (w != g[i][j]) x = gcd(x, tag[g[i][j]]);
                x = gcd(x, a[i]);
                if (x != 1) {
                    ok = 1; tr[i].pb({x, i});
                }
            }
        }
        reverse(all(changes[i]));
        changes[i].push_back({i, a[i]});
        int id = sz(changes[i])-1;
        vector<ii> nc;
        for (auto& [x, y] : changes[i]) y = gcd(y, a[i]);
        for (int l = 0, r = 0; l != sz(changes[i]); l = r) {
            while (r != sz(changes[i]) and changes[i][r].second == changes[i][l].second) r++;
            nc.pb(changes[i][r-1]);
        }
        swap(nc, changes[i]);
        for (auto [x, y] : changes[i]) cout << x << " " << y << endl;
        if (!ok) {
            while (!tr[i].empty()) {
                auto [x, w] = tr[i].back();
                // where am i
                int j = lower_bound(all(changes[i]), pair(w, -1LL)) - begin(changes[i]) - 1;
                if (j >= 0 and gcd(x, changes[i][j].second) == 1) tr[i].pop_back();
                if (x == 1) tr[i].pop_back();
                else {
                    ok = 1;
                    break;
                }
            }
        }
        //cout << "tr[" << i << "]: " << endl;
        //for (auto [x, y] : tr[i]) cout << x << " " << y << endl;
        //cout << "tag = " << tag[i] << endl;
        if (!ok) tr[i] = { {a[i], i} }, changes[i] = { {i, a[i]} }, tag[i] = a[i];
        else ans[i]--;
        cout << ans[i] << endl;
    }
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

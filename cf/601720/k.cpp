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

void solve(){
    int n, m; cin >> n >> m;
    const int lim = 16;
    if (n <= lim) {
        vector<vector<int>> restr(n, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            int u, v; cin >> u >> v;
            --u, --v;
            restr[u][v] = restr[v][u] = 1;
        }
        vector<vector<int>> dp((1<<n), vector<int>(n));
        for (int i = 1; i < (1 << n); ++i) {
            for (int j = 0; j < n; ++j) {
                if (i >> j & 1) {
                    if (__builtin_popcount(i) == 1) {
                        dp[i][j] = 1;
                        continue;
                    }
                    for (int lst = 0; lst < n; ++lst) {
                        if (lst == j) continue;
                        if (i >> lst & 1) if (restr[j][lst] == 0) dp[i][j] |= dp[i-(1<<j)][lst];
                    }
                }
            }
        }
        int cur = -1;
        for (int i = 0; i < n; ++i) if (dp.back()[i]) cur = i;
        if (cur == -1) {
            cout << -1 << endl;
            exit(0);
        }
        int state = (1 << n) - 1;
        cout << cur + 1 << ' ';
        state -= (1 << cur);
        while (state) {
            int choice = -1;
            for (int i = 0; i < n; ++i) {
                if (state >> i & 1) {
                    if (restr[i][cur] == 0 and dp[state][i]) choice = i;
                }
            }
            assert(choice != -1);
            cur = choice;
            cout << cur + 1 << ' ';
            state -= (1 << cur);
        }
        cout << endl;
        exit(0);
    }
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> ans(n);
    iota(all(ans), 0);
    auto check = [&] (int i, int j) {
        assert(abs(i-j) == 1);
        bool ok = 1;
        for (auto x : g[ans[i]]) ok &= (x != ans[j]);
        return ok;
    };
    auto try_swap = [&] (int i, int j) {
        swap(ans[i], ans[j]);
        bool ok = 1;
        if (j) ok &= check(j, j-1);
        if (i) ok &= check(i, i-1);
        if (j != n-1) ok &= check(j, j+1);
        if (i != n-1) ok &= check(i, i+1);
        swap(ans[i], ans[j]);
        return ok;
    };
    for (int i = 0; i < n-1; ++i) {
        if (!check(i, i+1)) {
            bool foi = 0;
            for (int j = 0; j < n; ++j) {
                if (j == i or j == i+1) continue;
                if (try_swap(i, j)) {
                    foi = true;
                    swap(ans[i], ans[j]);
                    break;
                }
                if (try_swap(i+1, j)) {
                    foi = true;
                    swap(ans[i+1], ans[j]);
                    break;
                }
            }
            assert(foi);
        }
    }
    for (auto x : ans) cout << x+1 << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

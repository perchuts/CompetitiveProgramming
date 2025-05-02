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
    int n; cin >> n;
    vector<int> dp(n+1);
    vector<int> tr(n+1);
    vector<int> tipo(n+1), nice(n+1);
    vector<string> use(n+1);
    for (int i = 1; i <= n; ++i) {
        dp[i] = 2 + dp[i-1];
        tr[i] = 1;
        for (int j = 2; j < i; ++j) {
            if (ckmin(dp[i], dp[j] + dp[i-j] + 1)) tr[i] = j, tipo[i] = 0;
            if (i % j == 0 and ckmin(dp[i], dp[j] + dp[i/j] + 1 + (nice[j] or tipo[j]?0:2)+(nice[i/j] or tipo[i/j]?0:2))) {
                tr[i] = j, tipo[i] = 1;
            }
        }
        string xx = to_string(i);
        bool ok = true;
        for (auto x : xx) ok &= (x == '1');
        if (ok) {
            nice[i] = true;
            assert(sz(xx) <= dp[i]);
            dp[i] = sz(xx);
            tr[i] = i;
            use[i] = xx;
            continue;
        }
    }
    auto build = [&] (auto&& self, int u) -> string {
        if (!use[u].empty()) return use[u];
        if (tipo[u]) {
            if (!nice[tr[u]] and !tipo[tr[u]]) use[u] = "(";
            use[u] += self(self, tr[u]);
            if (!nice[tr[u]] and !tipo[tr[u]]) use[u] += ")*";
            else use[u] += "*";
            if (!nice[u/tr[u]] and !tipo[u/tr[u]]) use[u] += "(";
            use[u] += self(self, u/tr[u]);
            if (!nice[u/tr[u]] and !tipo[u/tr[u]]) use[u] += ")";
        } else {
            use[u] = self(self, tr[u]);
            use[u] += "+";
            use[u] += self(self, u-tr[u]);
        }
        return use[u];
    };
    cout << build(build, n) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

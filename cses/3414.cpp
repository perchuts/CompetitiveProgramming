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
    int n, k; cin >> n >> k;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    vector<vector<int>> eqc(n+1, vector<int>(n+1));
    vector<int> ans(k);
    for (int i = 1; i <= n; ++i) {
        vector<iii> caras;
        for (int j = 1; j <= n; ++j) {
            if (i == 1 or grid[i-1][j-1] != grid[i-2][j-1]) eqc[i][j] = 1;
            else eqc[i][j] = 1 + eqc[i-1][j];
            if (j != 1 and grid[i-1][j-2] != grid[i-1][j-1]) caras.clear();
            int tot = 1, mydp = 0;
            while (!caras.empty()) {
                auto [val, q, dp] = caras.back();
                if (val >= eqc[i][j]) {
                    tot += q;
                    caras.pop_back();
                } else {
                    mydp = dp;
                    break;
                }
            }
            mydp += tot * eqc[i][j];
            ans[grid[i-1][j-1]-'A'] += mydp;
            caras.pb({eqc[i][j], tot, mydp});
        }
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

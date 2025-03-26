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
    int n, c; cin >> n >> c;
    vector<ii> op(n);
    for (auto& [x, y] : op) cin >> x >> y;
    vector<vector<vector<int>>> out(n, vector<vector<int>>(30, vector<int>(2)));
    auto do_op = [] (int a, int b, int op) {
        if (op == 1) return (a&b);
        if (op == 2) return (a|b);
        return (a^b);
    };
    for (int i = 0; i < n; ++i) {
        auto [y, x] = op[i];
        for (int b = 0; b < 30; ++b) {
            for (int j = 0; j < 2; ++j) {
                int eu = (i == 0 ? j : out[i-1][b][j]);
                out[i][b][j] = do_op(eu, x >> b & 1, y);
            }
         }
    }
    int cur = c;
    for (int i = 0; i < n; ++i) {
        int nxt = 0;
        for (int b = 0; b < 30; ++b) {
            int eu = cur >> b & 1;
            if (out[i][b][eu]) nxt += (1 << b);
        }
        cur = nxt;
        cout << cur << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

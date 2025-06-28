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
    vector<int> a(n+1), b(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    set<int> pos;
    for (int i = 1; i <= n; ++i) if (b[i] != 1) pos.insert(i);
    vector<int> bit(n+1);
    auto insert = [&] (int x, int k) { while (x <= n) bit[x] += k, x += x & (-x); };
    auto query = [&] (int x) {
        int ans = 0;
        while (x) ans += bit[x], x -= x & (-x);
        return ans;
    };
    auto Query = [&] (int l, int r) { return (r >= l ? query(r) - query(l-1) : 0); };
    for (int i = 1; i <= n; ++i) insert(i, a[i]);
    int q; cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int i, x; cin >> i >> x;
            insert(i, x-a[i]);
            a[i] = x;
        } else if (op == 2) {
            int i, x; cin >> i >> x;
            if (b[i] > 1) pos.erase(i);
            b[i] = x;
            if (b[i] > 1) pos.insert(i);
        } else {
            int l, r; cin >> l >> r; 
            vector<vector<int>> dp(2, vector<int>(65));
            int ptr = l-1, turn = 1;
            auto it = pos.lower_bound(l);
            while (it != end(pos) and (*it) <= r) {
                int w = (*it), fodase = Query(ptr+1, w-1);
                for (int i = 0; i <= turn; ++i) {
                    dp[turn&1][i] = dp[(turn&1)^1][i] + fodase + a[w];
                    if (i) ckmax(dp[turn&1][i], (dp[(turn&1)^1][i-1] + fodase) * b[w]);
                }
                ptr = w; it = next(it), turn++;
            }
            int resto = Query(ptr+1, r), ans = 0;
            for (int i = 0; i <= turn; ++i) ckmax(ans, dp[(turn&1)^1][i] + resto);
            cout << ans << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

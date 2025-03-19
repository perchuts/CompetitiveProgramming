#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
    int n, q;
    ll xl = 0; cin >> n >> q;
    const int loser = 330;
    map<ii, bool> mp;
    map<ii, int> resp;
    vector<vector<int>> g(n+1);
    vector<int> big;
    for (int i = 0; i < q; ++i) {
        ll A, B, C; cin >> A >> B >> C;
        ll a = 1 + (((A * (1+xl)) % mod) % 2);
        ll b = 1 + (((B * (1+xl)) % mod) % n);
        ll c = 1 + (((C * (1+xl)) % mod) % n);
        if (a == 1) {
            g[b].pb(c);
            g[c].pb(b);
            auto add = [&] (int x) {
                big.pb(x);
                for (auto y : g[x]) {
                    for (auto z : g[y]) if (z != x and sz(g[z]) > loser) resp[{x, z}] = resp[{z, x}] = y;
                }
            };
            for (auto x : big) {
                if (sz(g[b]) > loser and mp.count({c, x})) resp[{b, x}] = resp[{x, b}] = c;
                if (sz(g[c]) > loser and mp.count({b, x})) resp[{c, x}] = resp[{x, c}] = b;
            }
            if (sz(g[b]) == loser+1) add(b);
            if (sz(g[c]) == loser+1) add(c);
            mp[{b, c}] = mp[{c, b}] = 1;
        } else {
            int ans = 0;
            if (sz(g[b]) <= loser) {
                for (auto z : g[b]) if (mp.count({z, c})) ans = z;
            } else if (sz(g[c]) <= loser) {
                for (auto z : g[c]) if (mp.count({z, b})) ans = z;
            } else if (resp.count({b, c})) ans = resp[{b, c}];
            cout << ans << endl;
            xl = ans;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

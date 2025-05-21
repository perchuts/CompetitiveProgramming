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
    int n, q; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<vector<iii>> queries(n);
    cin >> q;
    vector<int> ans(q);
    for (int i = 0; i < q; ++i) {
        int l, r, x; cin >> l >> r >> x;
        queries[l-1].pb({x, r-1, i});
    }
    // base inteira, quem mudou
    deque<vector<int>> bases;
    deque<int> ini;
    vector<int> pot(n+1, 1);
    for (int i = 1; i <= n; ++i) pot[i] = (pot[i-1] * 2) % mod;
    for (int i = n-1; ~i; --i) {
        int l = 0, r = sz(bases)-1, use = sz(bases);
        while (l <= r) {
            int j = l + (r-l+1)/2, ok = 1, cur = a[i];
            for (int k = 0; k < 60; ++k) {
                if (cur >> k & 1) {
                    if (bases[j][k] != 0) cur ^= bases[j][k];
                    else { ok = 0; break; }
                }
            }
            if (ok) r = j-1, use = j;
            else l = j+1;
        }
        if (use != sz(bases)) bases.erase(begin(bases)+use), ini.erase(begin(ini)+use);
        int j = 0, cur = a[i];
        for (int k = 0; k < 60 and j < use; ++k) {
            if (cur >> k & 1) {
                while (j < use and bases[j][k] == 0) bases[j++][k] = cur;
                if (j != use) cur ^= bases[j][k];
            }
        }
        vector<int> base(60);
        for (int k = 0; k < 60; ++k) {
            if (a[i] >> k & 1) { base[k] = a[i]; break; }
        }
        bases.push_front(base);
        ini.push_front(i);
        for (auto [x, j, id] : queries[i]) {
            int z = 0;
            for (int k = 0; k < sz(ini); ++k) {
                if (ini[k] <= j) z = k;
                else break;
            }
            int tt = 0;
            for (int k = 0; k < 60; ++k) tt += (bases[z][k] != 0);
            for (int k = 0; k < 60; ++k) {
                if (x >> k & 1) {
                    if (bases[z][k] == 0) break;
                    x ^= bases[z][k];
                }
            }
            if (x == 0) ans[id] = pot[j-i+1-tt];
        }
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}


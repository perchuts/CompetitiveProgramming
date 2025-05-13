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
    vector<int> c(n);
    for (auto& x : c) cin >> x;
    vector<vector<int>> list(n);
    for (int i = 0; i < m; ++i) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int x; cin >> x; --x;
            list[x].pb(i);
        }
    }
    vector<int> pot(n+1, 1);
    for (int i = 1; i <= n; ++i) pot[i] = 3 * pot[i-1];
    int ans = 1e18;
    vector<int> times(n);
    vector<int> qnt(m);
    for (int i = 1; i < pot[n]; ++i) {
        for (int j = 0; j < n; ++j) times[j] = (i/pot[j])%3;
        for (int j = 0; j < m; ++j) qnt[j] = 0;
        int cur = 0;
        for (int j = 0; j < n; ++j) {
            cur += times[j] * c[j];
            for (auto x : list[j]) qnt[x] += times[j];
        }
        if ((*min_element(all(qnt))) >= 2) ckmin(ans, cur);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

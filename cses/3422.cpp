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
    if (n == 2) {
        cout << "IMPOSSIBLE" << endl;
        exit(0);
    }

    vector<int> a(n), b(n), oa(n), ob(n);
    for (auto& x : a) cin >> x, --x;
    for (auto& x : b) cin >> x, --x;
    for (int i = 0; i < n; ++i) oa[a[i]] = i, ob[b[i]] = i;
    vector<int> vis(n);
    vector<vector<int>> cycles;
    vector<vector<int>> tam2;
    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;
        int cur = i;
        vector<int> cyc;
        while (!vis[cur]) {
            vis[cur] = true;
            cyc.pb(cur);
            cur = ob[a[cur]];
        }
        if (sz(cyc) > 2) cycles.pb(cyc);
        else tam2.pb(cyc);
    }
    // consigo fazer todo mundo se matar aqui, exceto os caras com tamanho 2!!
    vector<int> ord;
    if (sz(tam2) != 1) {
        for (auto x : tam2) ord.pb(x[0]);
        for (auto x : cycles) for (auto y : x) ord.pb(y);
        for (auto x : tam2) ord.pb(x[1]);
    } else {
        ord.pb(tam2[0][0]);
        ord.pb(cycles[0][0]);
        ord.pb(tam2[0][1]);
        for (int i = 1; i < sz(cycles[0]); ++i) ord.pb(cycles[0][i]);
        for (int i = 1; i < sz(cycles); ++i) {
            for (auto x : cycles[i]) ord.pb(x);
        }
    }
    vector<int> p(n);
    for (int i = 0; i < n; ++i) p[ord[i]] = a[ord[(i+1)%n]];
    for (auto x : p) cout << x + 1 << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

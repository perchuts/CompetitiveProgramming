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
    vector<int> a(n);
    for (auto& x : a) cin >> x, --x;
    int q; cin >> q;
    int block = sqrt(n);
    vector<vector<iii>> sexo(n/block+1);
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r; --l, --r;
        sexo[l/block].pb({r, l, i});
    }
    vector<int> par(n), ans(q);
    for (int i = 0; i * block < n; ++i) {
        sort(all(sexo[i]));
        int lx = i*block, rx = i*block, cur = 0;
        for (int j = 0; j < n; ++j) par[j] = 0;
        for (auto [r, l, idx] : sexo[i]) {
            while (rx <= r) cur -= par[a[rx]], par[a[rx]] ^= 1, cur += par[a[rx]], rx++;
            while (l < lx) lx--, cur -= par[a[lx]], par[a[lx]] ^= 1, cur += par[a[lx]];
            while (lx < l) cur -= par[a[lx]], par[a[lx]] ^= 1, cur += par[a[lx]], lx++;
            ans[idx] = (r-l+1-cur)/2;
        }
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

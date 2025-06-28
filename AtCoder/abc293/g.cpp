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
    int n, q; cin >> n >> q;
    vector<int> a(n), ans(q);
    int block = sqrt(n);
    vector<vector<iii>> qu(n/block+1);
    for (auto& x : a) cin >> x;
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r;
        --l, --r;
        qu[l/block].pb({r, l, i});
    }
    vector<int> qt(maxn);
    int lx = 0, rx = 0, cur = 0;
    for (int st = 0; st * block < n; ++st) {
        sort(all(qu[st]));
        for (auto [r, l, idx] : qu[st]) {
            while (rx <= r) cur += qt[a[rx]] * (qt[a[rx]]-1) / 2, qt[a[rx]]++, rx++;
            while (r+1 < rx) rx--, qt[a[rx]]--, cur -= qt[a[rx]] * (qt[a[rx]]-1) / 2;
            while (l < lx) lx--, cur += qt[a[lx]] * (qt[a[lx]]-1) / 2, qt[a[lx]]++;
            while (lx < l) qt[a[lx]]--, cur -= qt[a[lx]] * (qt[a[lx]]-1) / 2, lx++;
            ans[idx] = cur;
        }
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

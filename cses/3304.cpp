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
    vector<int> h(n);
    for (auto& x : h) cin >> x;
    vector<int> seta(n+1);
    seta[n] = n;
    vector<ii> st = {{n, inf}};
    for (int i = n-1; ~i; --i) {
        while (st.back().second <= h[i]) st.pop_back();
        seta[i] = st.back().first;
        st.pb({i, h[i]});
    }
    vector<vector<int>> bl(18, vector<int>(n+1));
    bl[0] = seta;
    for (int i = 1; i < 18; ++i) {
        for (int j = 0; j < n; ++j) bl[i][j] = bl[i-1][bl[i-1][j]];
        bl[i][n] = n;
    }
    while (q--) {
        int l, r; cin >> l >> r;
        --l, --r;
        int ans = 1;
        for (int k = 17; ~k; --k) {
            if (bl[k][l] <= r) ans += (1 << k), l = bl[k][l];
        }
        cout << ans << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

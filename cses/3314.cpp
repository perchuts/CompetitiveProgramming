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
    for (auto& x : a) cin >> x;
    vector<ii> st;
    st.pb({-1, inf});
    vector<int> li(n), ri(n);
    for (int i = 0; i < n; ++i) {
        while (st.back().second < a[i]) st.pop_back();
        li[i] = st.back().first+1;
        st.pb({i, a[i]});
    }
    st.clear();
    st.pb({n, inf});
    for (int i = n-1; ~i; --i) {
        while (st.back().second < a[i]) st.pop_back();
        ri[i] = st.back().first-1;
        st.pb({i, a[i]});
    }
    vector<int> ord(n); iota(all(ord), 0); sort(all(ord), [&] (int x, int y) { return a[x] < a[y]; });
    vector<int> seg(4*n);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            seg[i] = k;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = max(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        if (r < x or y < l) return 0;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return max(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    int ans = 0;
    for (auto i : ord) {
        int eu = query(query, 1, 0, n-1, li[i], ri[i])+1;
        ckmax(ans, eu);
        upd(upd, 1, 0, n-1, i, eu);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

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
    int r, c, n; cin >> r >> c >> n;
    vector<iii> v1, v2, v3, v4, pts;
    for (int i = 0; i < n; ++i) {
        int h, j, k, l; cin >> h >> j >> k >> l;
        if ((0 < h and h < r and 0 < j and j < c) or (0 < k and k < r and 0 < l and l < c)) continue;
        auto insert = [&] (int x, int y) {
            if (x == 0) v1.pb({x, y, i});
            else if (x == r) v2.pb({x, y, i});
            else if (y == 0) v3.pb({x, y, i});
            else {
                assert(y == c);
                v4.pb({x, y, i});
            }
        };
        insert(h, j), insert(k, l);
    }
    sort(all(v1));
    sort(rbegin(v2), rend(v2));
    sort(rbegin(v3), rend(v3));
    sort(all(v4));
    for (auto x : v1) pts.pb(x);
    for (auto x : v4) pts.pb(x);
    for (auto x : v2) pts.pb(x);
    for (auto x : v3) pts.pb(x);
    vector<int> foi(n);
    stack<int> st;
    for (auto [lixo1, lixo2, id] : pts) {
        if (foi[id]) {
            int k = st.top(); st.pop();
            if (k != id) {
                cout << "NO" << endl;
                exit(0);
            }
        } else foi[id] = 1, st.push(id);
    }
    cout << "YES" << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

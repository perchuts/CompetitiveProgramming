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
    vector<vector<int>> v(2, vector<int>(n)), vc = v;
    vector<int> c;
    for (auto& x : v) for (auto& y : x) cin >> y, c.pb(y);
    sort(all(c)), c.erase(unique(all(c)), end(c));
    for (int i = 0; i < 2; ++i) for (int j = 0; j < n; ++j) vc[i][j] = lower_bound(all(c), v[i][j]) - begin(c) + 1;
    int q; cin >> q;
    vector<int> ans(q);
    int B = sqrt(n);
    vector<vector<iii>> queries(n/B+1);
    for (int i = 0; i < q; ++i) {
        int x, y; cin >> x >> y;
        --x, --y;
        queries[x/B].pb({y, x, i});
    }
    vector<vector<ii>> bit(2, vector<ii>(2*n+1));
    auto insert = [&] (int i, int k, int x, int y) { while (k <= 2*n) bit[i][k].first += x, bit[i][k].second += y, k += k & (-k); };
    auto query = [&] (int i, int k) {
        int ans1 = 0, ans2 = 0;
        while (k) ans1 += bit[i][k].first, ans2 += bit[i][k].second, k -= k & (-k);
        return pair(ans1, ans2);
    };
    vector<int> ptr(2), ss(2);
    int cur = 0;
    auto change = [&] (int i, int k) {
        if (k < 0) ptr[i]--;
        int j = ptr[i];
        auto [sm, cum] = query(i^1, vc[i][j]);
        int X = 0;
        X += sm * v[i][j] - cum;
        assert(X >= 0);
        X += (ss[i^1] - cum) - v[i][j] * (ptr[i^1] - sm); 
        ss[i] += k * v[i][j];
        insert(i, vc[i][j], k, k*v[i][j]);
        cur += X * k;
        if (k > 0) ptr[i]++;
    };
    for (int st = 0; st * B < n; ++st) { 
        sort(all(queries[st]));
        for (auto [p2, p1, id] : queries[st]) {
            while (ptr[1] <= p2) change(1, 1);
            while (ptr[1] > p2+1) change(1, -1);
            while (ptr[0] <= p1) change(0, 1);
            while (ptr[0] > p1+1) change(0, -1); 
            ans[id] = cur;
        }
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}


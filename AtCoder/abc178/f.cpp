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
    vector<int> a(n), b(n);
    vector<vector<int>> freq(n+1, vector<int>(2)), loc(n+1);
    for (int i = 0; i < n; ++i) cin >> a[i], freq[a[i]][0]++, loc[a[i]].pb(i);
    for (auto& x : b) cin >> x, freq[x][1]++;
    vector<ii> caras;
    for (int i = 1; i <= n; ++i) {
        if (freq[i][0] + freq[i][1] > n) {
            cout << "No" << endl;
            exit(0);
        }
        for (int j = 0; j < freq[i][0]; ++j) caras.pb({i, 0});
        for (int j = 0; j < freq[i][1]; ++j) caras.pb({i, 1});
    }
    vector<ii> pairs, ba, bb;
    for (int i = 0; i < n; ++i) {
        if (caras[i].second != caras[i+n].second) {
            if (caras[i].second) swap(caras[i], caras[i+n]);
            pairs.pb({caras[i].first, caras[i+n].first});
        } else if (caras[i].second) bb.pb({caras[i].first, caras[i+n].first});
        else ba.pb({caras[i].first, caras[i+n].first});
    }
    assert(sz(ba) == sz(bb));
    for (int i = 0; i < sz(ba); ++i) {
        auto [x1, x2] = ba[i];
        auto [y1, y2] = bb[i];
        if (x1 != y1 and x2 != y2) pairs.pb({x1, y1}), pairs.pb({x2, y2});
        else assert(x1 != y2 and x2 != y1), pairs.pb({x1, y2}), pairs.pb({x2, y1});
    }
    vector<int> ans(n);
    for (auto [x, y] : pairs) {
        assert(!loc[x].empty());
        ans[loc[x].back()] = y;
        loc[x].pop_back();
    }
    cout << "Yes" << endl;
    for (auto x : ans) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

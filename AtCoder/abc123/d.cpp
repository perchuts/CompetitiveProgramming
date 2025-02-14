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
    vector<int> qt(3); int k; cin >> qt[0] >> qt[1] >> qt[2] >> k;
    vector<vector<int>> v;
    for (int i = 0; i < 3; ++i) {
        vector<int> vv(qt[i]);
        for (auto&x : vv) cin >> x;
        sort(all(vv));
        reverse(all(vv));
        v.pb(vv);
    }
    set<iii> vx;
    vector<vector<int>> ptr(qt[0], vector<int>(qt[1]));
    for (int i = 0; i < qt[0]; ++i) for (int j = 0; j < qt[1]; ++j) {
        vx.insert({-(v[0][i] + v[1][j] + v[2][0]), i, j});
    }
    vector<int> ans;
    for (int aaa = 0; aaa < k; ++aaa) {
        auto [val, i, j] = *begin(vx);
        cout << -val << endl;
        ptr[i][j]++;
        vx.erase({val, i, j});
        if (ptr[i][j] < qt[2]) {
            vx.insert({-(v[0][i] + v[1][j] + v[2][ptr[i][j]]), i, j});
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

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
    int ans = (n-2) * (n-2), block = 450;
    vector<vector<int>> ind(2, vector<int>(n, n-1)), bl = ind;
    while (q--) {
        int op, x; cin >> op >> x; --x, --op;
        int target = min(ind[op][x], bl[op][x/block]);
        ans -= target-1;
        for (int i = 0; (i+1) * block <= target; ++i) ckmin(bl[op^1][i], x);
        int j = target/block*block;
        while (j < target) ckmin(ind[op^1][j++], x);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

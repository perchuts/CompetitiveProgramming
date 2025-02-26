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
    vector<vector<int>> c(3, vector<int>(3));
    for (auto& x : c) for (auto& y : x) cin >> y;
    bool ok = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ok &= (c[i][j] - c[i][(j+1)%3] == c[0][j] - c[0][(j+1)%3]);
            ok &= (c[i][j] - c[(i+1)%3][j] == c[i][0] - c[(i+1)%3][0]);
        }
    }
    cout << (ok ? "Yes" : "No") << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

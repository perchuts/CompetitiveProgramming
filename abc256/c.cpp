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
    vector<int> row(3), col(3);
    for (auto& x : row) cin >> x;
    for (auto& x: col) cin >> x;
    int ans = 0;
    vector<vector<int>> vals(3, vector<int>(3));
    for (int a = 1; a <= 30; ++a) for (int b = 1; b <= 30; ++b) for (int c = 1; c <= 30; ++c) for (int d = 1; d <= 30; ++d) {
        vals[0][0] = a, vals[1][1] = b, vals[2][2] = c, vals[0][1] = d;
        vals[0][2] = row[0] - a - d;
        vals[1][2] = col[2] - vals[0][2] - c;
        vals[1][0] = row[1] - b - vals[1][2];
        vals[2][0] = col[0] - a - vals[1][0];
        vals[2][1] = col[1] - b - vals[0][1];
        int ok = (min({vals[0][2], vals[1][2], vals[1][0], vals[2][0], vals[2][1]}) > 0);
        for (int i = 0; i < 3; ++i) {
            ok &= (row[i] == vals[i][0] + vals[i][1] + vals[i][2]);
            ok &= (col[i] == vals[0][i] + vals[1][i] + vals[2][i]);
        }
        ans += ok;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

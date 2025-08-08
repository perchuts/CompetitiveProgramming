#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

void solve() {
    int n, k; cin >> n >> k;
    if (2 * k > n + 1) {
        cout << "NO" << endl;
        return;
    } 
    cout << "YES" << endl;
    cout << 60 << endl;
    cout << n-k+1 << ' ' << 1 << ' ';
    for (int i = 1; i <= 58; ++i) cout << rnd(1, 1e18) << ' ';
    cout << endl;
}
int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    int mx = 255;
    vector<vector<int>> can(mx+1, vector<int>(mx+1, inf));
    vector<vector<int>> tr(mx+1, vector<int>(mx+1, inf));
    can[0][0] = 0;
    for (int i = 1; i <= mx; ++i) {
        for (int j = 1; j <= i; ++j) {
            int left = i % j, gain = i / j;
            for (int x = 0; x + gain <= i; ++x) {
                bool foi = ckmin(can[i][x+gain], can[left][x]+1);
                if (foi) tr[i][x+gain] = j;
            }
        }
        for (int j = 1; 2*j <= i+1; ++j) {
            if (can[i][j] == 2) {
                cout << i << ' ' << j << " -> " << i%tr[i][j] << ' ' << j-(i/tr[i][j]) << endl;
            }
        }
    }
#endif
}

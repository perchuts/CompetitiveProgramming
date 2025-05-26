#include <bits/stdc++.h>
#pragma GCC target("bmi,bmi2,popcnt,lzcnt")
#pragma GCC optimize("Ofast")
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

int m[3000][3000][12], dp[3000][3000];

void solve(){
    int n, X; cin >> n >> X;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    vector<int> lg(3001);
    for (int i = 2; i <= 3000; ++i) lg[i] = 1 + lg[i/2];
    auto query = [&] (int i, int j, int k) {
        int K = k - (1<<lg[k]);
        k = lg[k];
        return (m[i][j][k]|m[i-K][j-K][k]|m[i-K][j][k]|m[i][j-K][k]);
    };
    ll ans = 0;
    int want = (1 << X) - 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int eu = grid[i][j] - 'A';
            m[i][j][0] = (1 << eu);
            for (int k = 1, x = 1; 2*x <= min(i, j) + 1; ++k, x += x) {
                m[i][j][k] = (m[i][j][k-1] | m[i-x][j-x][k-1] | m[i-x][j][k-1] | m[i][j-x][k-1]);
            }
            if (i == 0 or j == 0) dp[i][j] = (X == 1);
            else {
                dp[i][j] = dp[i-1][j-1];
                while (dp[i][j] <= min(i, j) and query(i, j, min(i, j) + 1 - dp[i][j]) == want) dp[i][j]++;
            }
            ans += dp[i][j];
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

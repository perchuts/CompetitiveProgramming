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
    vector<ii> intr(n);
    for (auto& [x, y] : intr) cin >> x >> y, --y;
    vector<vector<int>> dp(102, vector<int>(102));
    vector<int> freq(101);
    for (int i = 100; i >= 1; --i) for (int j = i; j <= 100; ++j) {
        for (auto [x, y] : intr) {
            if (i <= x and y <= j) freq[dp[i][x-1] ^ dp[y+1][j]] = 1;
        }
        for (int k = 0; ; ++k) {
            if (freq[k] == 0) {
                dp[i][j] = k;
                break;
            }
        }
        for (auto [x, y] : intr) {
            if (i <= x and y <= j) freq[dp[i][x-1] ^ dp[y+1][j]] = 0;
        }
    }
    cout << (dp[1][100] ? "Alice" : "Bob") << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}

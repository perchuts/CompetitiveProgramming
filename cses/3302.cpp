#include <bits/stdc++.h>
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

int dp[2][4*maxn];

void solve(){
    int n, a; cin >> n >> a;
    vector<int> v(n);
    int shift = 500*n;
    dp[0][shift] = 1;
    int turn = 1;
    for (auto& x : v) {
        cin >> x; x -= a;
        int agr = turn&1, antes = agr^1;
        for (int i = -500*turn; i <= 500*turn; ++i) {
            dp[agr][i+shift] = dp[antes][i+shift];
            int j = i - x;
            if (-500*turn <= j and j <= 500*turn) dp[agr][i+shift] += dp[antes][j+shift];
            if (dp[agr][i+shift] >= mod) dp[agr][i+shift] -= mod;
        }
        turn++;
    }
    cout << (mod-1+dp[n&1][shift])%mod << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

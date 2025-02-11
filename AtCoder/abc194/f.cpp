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
    vector<int> num;
    string s; cin >> s;
    for (auto c : s) {
        if ('0' <= c and c <= '9') num.pb(c-'0');
        else num.pb(10+c-'A');
    }
    int qnt; cin >> qnt;
    int inv16 = (mod+1)/2, ans = 0, n = sz(num);
    for (int i = 1; i <= 2; ++i) inv16 = (inv16 * inv16) % mod;
    vector dp(n, vector(qnt+1, 0LL));
    dp[0][0] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= qnt; ++j) {
            dp[i][j] = (dp[i-1][j] * j + dp[i-1][j-1] * (16-j+1)) % mod;
        }
        ans = (ans + dp[i][qnt] * 15 % mod * inv16) % mod;
    }
    vector dp2(n, vector(qnt+2, 0LL));
    dp2[0][qnt] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= qnt; ++j) {
            dp2[i][j] = (dp2[i-1][j] * j + dp2[i-1][j+1] * (16-j)) % mod;
        }
    }
    vector<int> foi(16);
    int tem = 0;
    for (int i = 0; i < n; ++i) {
        int digit = num[i];
        if (tem > qnt) break;
        for (int usar = (i==0); usar < digit; ++usar) {
            if (!foi[usar]) tem++;
            if (tem <= qnt) ans = (ans + dp2[n-i-1][tem]) % mod;
            // tenho n-i-1 digitos pra usar
            if (!foi[usar]) tem--;
        }
        if (foi[digit] == 0) tem++, foi[digit] = 1;
    }
    if (tem == qnt) ans++;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

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
    string s; cin >> s;
    int n = sz(s);
    int q = 0;
    for (auto x : s) q += (x == '?');
    vector<vector<int>> pr(n+1, vector<int>(4)), suf = pr;
    vector<int> id(256), pw(n+1, 1); id['A'] = 0, id['B'] = 1, id['C'] = 2, id['?'] = 3;
    for (int i = 1; i <= n; ++i) {
        pw[i] = 3 * pw[i-1] % mod;
        for (int j = 0; j < 4; ++j) {
            pr[i][j] = pr[i-1][j] + (id[s[i-1]] == j);
        }
    }
    for (int i = 1; i <= n; ++i) for (int j = 0; j < 4; ++j) {
        suf[i][j] = pr[n][j] - pr[i-1][j];
    }
    int ans = 0;
    for (int i = 2; i < n; ++i) {
        if (s[i-1] == 'B') {
            ans = (ans + pr[i-1][0] * suf[i+1][2] % mod * pw[q]) % mod; 
            if (q >= 1) {
                ans = (ans + pr[i-1][3] * suf[i+1][2] % mod * pw[q-1]) % mod;
                ans = (ans + pr[i-1][0] * suf[i+1][3] % mod * pw[q-1]) % mod;
            }
            if (q >= 2) {
                ans = (ans + pr[i-1][3] * suf[i+1][3] % mod * pw[q-2]) % mod;
            }
        }
        if (s[i-1] == '?') {
            ans = (ans + pr[i-1][0] * suf[i+1][2] % mod * pw[q-1]) % mod; 
            if (q >= 2) {
                ans = (ans + pr[i-1][3] * suf[i+1][2] % mod * pw[q-2]) % mod;
                ans = (ans + pr[i-1][0] * suf[i+1][3] % mod * pw[q-2]) % mod;
            }
            if (q >= 3) {
                ans = (ans + pr[i-1][3] * suf[i+1][3] % mod * pw[q-3]) % mod;
            }
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

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
const int mod = (119<<23)+1;
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
    int m; cin >> m;
    vector<int> c(m);
    int M = 0, m_cara = 0, v_cara = 0;
    for (auto& x : c) cin >> x, M += (1 << x);
    vector<int> dp(1024), dp2(1024);
    auto add = [&] (int& x, int y) {
         x += y;
         if (x >= mod) x -= mod;
    };
    vector<int> P(sz(s), 1);
    for (int i = 1; i < sz(s); ++i) P[i] = 10 * P[i-1] % mod;
    reverse(all(P));
    for (int i = 0; i < sz(s); ++i) {
        int digit = s[i] - '0';
        vector<int> ndp(1024), ndp2(1024);
        for (int j = 0; j < 10; ++j) {
            int x = (1<<j);
            for (int mask = 0; mask < 1024; ++mask) {
                if (mask >> j & 1) {
                    add(ndp[mask], dp[mask]), add(ndp[mask], dp[mask-x]);
                    add(ndp2[mask], (dp2[mask] + dp[mask] * j % mod * P[i]) % mod), add(ndp2[mask], (dp2[mask-x] + (dp[mask-x] * j % mod * P[i])) % mod);
                    if (mask == x and min(i, j)) {
                        add(ndp[mask], 1);
                        add(ndp2[mask], j*P[i]%mod);
                    }
                }
            }
            if (j < digit and max(i, j)) add(ndp2[m_cara|x], (v_cara + j*P[i]) % mod), add(ndp[m_cara|x], 1);
        }
        swap(dp, ndp);
        swap(dp2, ndp2);
        m_cara |= (1 << digit);
        v_cara = (v_cara + digit*P[i]) % mod;
    }
    add(dp[m_cara], 1);
    add(dp2[m_cara], v_cara);
    int ans = 0;
    for (int i = 0; i < 1024; ++i) if ((i&M) == M) {
        add(ans, dp2[i]);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

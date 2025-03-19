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
    auto inv = [&] (int b, int e = mod-2) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    int inv3 = inv(3), inv9 = inv(9), ans = 0, P = 0;
    int n, m; cin >> n >> m;
    vector<vector<int>> p(n+1, vector<int>(m+1));
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> p[i][j], P += p[i][j], ans = (ans + inv9 * p[i][j] * p[i][j]) % mod;
    for (int i = 1; i <= n; ++i) {
        int x = 0, y = 0, tot = 0;
        for (int j = 1; j <= m; ++j) {
            tot = (tot + x * p[i][j] * j - y * p[i][j]) % mod;
            tot = (tot + mod) % mod;
            x += p[i][j];
            y = (y + p[i][j] * j) % mod;
        }
        ans = (ans + tot * 2 * inv3) % mod;
    }
    for (int j = 1; j <= m; ++j) {
        int x = 0, y = 0, tot = 0;
        for (int i = 1; i <= n; ++i) {
            tot = (tot + x * p[i][j] * i - y * p[i][j]) % mod;
            tot = (tot + mod) % mod;
            x += p[i][j];
            y = (y + p[i][j] * i) % mod;
        }
        ans = (ans + tot * 2 * inv3) % mod;
    }
    vector<vector<int>> psi = p, psj = p, ps = p;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        psi[i][j] = (psi[i-1][j] + psi[i][j-1] - psi[i-1][j-1] + p[i][j] * i + mod) % mod;
        psj[i][j] = (psj[i-1][j] + psj[i][j-1] - psj[i-1][j-1] + p[i][j] * j + mod) % mod;
        ps[i][j] = (ps[i-1][j] + ps[i][j-1] - ps[i-1][j-1] + p[i][j] + mod) % mod;
    }
    auto geti = [&] (int x1, int y1, int x2, int y2) {
        if (x1 > x2 or y1 > y2) return 0LL;
        return (psi[x2][y2] - psi[x1-1][y2] - psi[x2][y1-1] + psi[x1-1][y1-1] + mod) % mod;
    };
    auto getj = [&] (int x1, int y1, int x2, int y2) {
        if (x1 > x2 or y1 > y2) return 0LL;
        return (psj[x2][y2] - psj[x1-1][y2] - psj[x2][y1-1] + psj[x1-1][y1-1] + mod) % mod;
    };
    auto get = [&] (int x1, int y1, int x2, int y2) {
        if (x1 > x2 or y1 > y2) return 0LL;
        return (ps[x2][y2] - ps[x1-1][y2] - ps[x2][y1-1] + ps[x1-1][y1-1] + mod) % mod;
    };
    int dp = 0, da = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        dp = (dp + i * j % mod * p[i][j] * ps[i-1][j-1]) % mod;
        dp = (dp + i * j % mod * p[i][j] * get(i+1, j+1, n, m)) % mod;
        dp = (dp - psi[i-1][j-1] * j * p[i][j]) % mod;
        dp = (dp - psj[i-1][j-1] * i * p[i][j]) % mod;
        dp = (dp + mod) % mod;
        
        da = (da - i * j % mod * p[i][j] * get(1, j+1, i-1, m)) % mod;
        da = (da - i * j % mod * p[i][j] * get(i+1, 1, n, j-1)) % mod;
        da = (da + geti(1, j+1, i-1, m) * j * p[i][j]) % mod;
        da = (da + getj(1, j+1, i-1, m) * i * p[i][j]) % mod;
        da = (da + mod) % mod;
    }
    ans = (ans + 2 * (dp+da)) % mod;
    int invp = inv(P*P%mod);
    ans = ans * invp % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

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
    int n, m; cin >> n >> m;
    swap(n, m);
    vector<int> fib(m+1, 1);
    for (int i = 2; i <= m; ++i) fib[i] = fib[i-1] + fib[i-2];
    auto get = [&] (int i) {
        int tot = 1;
        for (int l = 0, r = 0; l < m; l = r) {
            while (r < m and (i>>l&1) == (i>>r&1)) r++;
            if (i>>l&1) tot *= fib[r-l];
        }
        return tot;
    };
    vector dp(1<<m, vector(1<<m, 0LL)), resp = dp, mat = dp;
    for (int k = 0; k < (1 << m); ++k) {
        for (int i = 0; i < (1<<m); ++i) {
            for (int j = 0; j < (1<<m); ++j) {
                if ((i & k) != k) continue;
                if ((j & k) != k) continue;
                dp[i][j] += get(i-k) * get(j-k);
            }
        }
    }
    auto multi = [&] (vector<vector<int>> dp1, vector<vector<int>> dp2) {
        vector<vector<int>> res(1<<m, vector<int>(1<<m));
        for (int esq = 0; esq < (1 << m); ++esq) {
            for (int meio = 0; meio < (1 << m); ++meio) {
                for (int dir = 0; dir < (1 << m); ++dir) {
                    res[esq][dir] = (res[esq][dir] + dp1[esq][meio] * dp2[meio][dir]) % mod;
                }
            }
        }
        return res;
    };
    auto brute = [&] (int N, int M) {
        vector<int> ways(1<<M);
        ways.back() = 1;
        int tudo = 1<<M; tudo--;
        for (int i = 0; i < N; ++i) {
            vector<int> nways(1<<M);
            for (int x1 = 0; x1 < (1 << M); ++x1) {
                for (int j = x1; j; j = (j-1)&x1) {
                    nways[x1] += ways[tudo-j] * get(x1-j);
                    nways[x1] %= mod;
                }
                nways[x1] += ways[tudo] * get(x1);
                nways[x1] %= mod;
            }
            swap(nways, ways);
        }
        return ways.back();
    };
    if (n < 4) {
        cout << brute(n, m) << endl;
        exit(0);
    }
    int foi = 0, impar = n % 2;
    n -= 2;
    n /= 2;
    while (n) {
        if (n&1) {
            if (foi == 0) foi = 1, resp = dp;
            else resp = multi(dp, resp);
        }
        dp = multi(dp, dp), n /= 2;
    }
    int ans = 0;
    int tudo = (1<<m)-1; 
    if (impar) {
        vector ndp(1<<m, vector(1<<m, 0LL));
        for (int i = 0; i < (1<<m); ++i) {
            for (int j = 0; j < (1<<m); ++j) {
                for (int k = 0; k < (1<<m); ++k) {
                    if (k & (tudo-j)) continue;
                    ndp[i][k+(tudo-j)] = (ndp[i][k+(tudo-j)] + resp[i][j] * get(k)) % mod;
                }
            }
        }
        resp = ndp;
    } 
    for (int i = 0; i < (1<<m); ++i) {
        for (int j = 0; j < (1<<m); ++j) {
            int ways = resp[i][j] * get(i) * get(j) % mod;
            ans = (ans + ways) % mod;
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

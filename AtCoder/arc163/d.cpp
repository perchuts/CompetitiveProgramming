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
    vector scc(n+1, vector(m+1, 0LL));
    vector dp1(n+1, vector(n+1, vector(m+1, 0LL)));
    vector ncr(n*n+1, vector(n*n+1, 0LL));
    for (int i = 0; i <= n*n; ++i) for (int j = 0; j <= i; ++j) {
        if (j == 0 or j == i) ncr[i][j] = 1;
        else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
    }
    auto add = [&] (int& x, int y) {
        x += y;
        if (x >= mod) x -= mod;
    };
    dp1[0][0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            for (int edg = 0; edg <= m; ++edg) {
                auto& DP = dp1[i][j][edg];
                if (j) add(DP, dp1[i-1][j-1][edg]);
                if (j <= edg) add(DP, dp1[i-1][j][edg-j]);
            }
        }
    }
    vector bad_ways(n, vector(m+1, 0LL));
    for (int i = 1; i <= n; ++i) {
        for (int x = 1; x < i; ++x) {
            for (int e = 0; e <= m; ++e) bad_ways[x][e] = 0;
            for (int e1 = 0; e1 <= x * (x-1) / 2 and e1 <= m; ++e1) {
                for (int e2 = 0; e2 <= x * (i-x) and e1+e2 <= m; ++e2) {
                    int ways = scc[x][e1] * dp1[i][x][e2] % mod;
                    add(bad_ways[x][e1+e2], ways);
                }
            }
        }
        for (int j = 0; j <= m; ++j) {
            scc[i][j] = ncr[i*(i-1)/2][j];
            for (int x = 1; x < i; ++x) for (int e = 0; e <= j; ++e) {
                int ways = bad_ways[x][e] * ncr[(i-x)*(i-x-1)/2][j-e] % mod;
                add(scc[i][j], mod - ways);
            }
        }
    }
    // show, agora sabemos quantas sccs com i vertices e j arestas boas existem
    // dp[n][c1][c2][qtd_edg]
    vector dp2(n+1, vector(n+1, vector(m+1, 0LL)));
    dp2[0][0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        vector ndp(n+1, vector(n+1, vector(m+1, 0LL)));
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; j + k <= i; ++k) {
                int k2 = i - (j+k);
                for (int q = 0; q <= min(m, i * (i-1) / 2); ++q) { 
                    auto& DP = ndp[j][k][q];
                    // colocar antes
                    if (k) add(DP, dp2[j][k-1][q]);
                    // colocar no conjunto
                    if (j and k <= q) add(DP, dp2[j-1][k][q-k]);
                    // colocar depois
                    if (k2 and j+k <= q) add(DP, dp2[j][k][q-j-k]);
                }
            }
        }
        swap(dp2, ndp);
    }
    int ans = 0;
    for (int tam = 1; tam <= n; ++tam) {
        for (int e1 = 0; e1 <= tam*(tam-1)/2 and e1 <= m; ++e1) {
            for (int e2 = 0; e1+e2 <= m; ++e2) {
                for (int esq = 0; esq + tam <= n; ++esq) {
                    int ways = dp2[tam][esq][e2] * scc[tam][e1] % mod;
                    ways = ways * ncr[ncr[esq][2]+ncr[n-tam-esq][2]][m-e1-e2] % mod;
                    add(ans, ways);
                }
            }
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

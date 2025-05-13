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

int solve(int n, vector<int> p, vector<int> q){
    vector<int> fat(n+1, 1), d1(n+5), d2 = d1;
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    vector<vector<int>> dp(n+1, vector<int>(n+1));
    int shift = 1;
    dp[0][0] = d2[shift] = 1;
    //for (int i = 1; i <= n; ++i) {
    //    for (int j = 0; j <= i; ++j) {
    //        dp[i][j] = dp[i-1][j];
    //        // dp[i][j] -> dp[k-2][j-i+k-1]
    //        // diag princ.: k-2 - (j-i+k-1) = -2-j+i+1 = i-j-1
    //        // quero somar tudo da diagonal principal i-j-1: dp[a][a-(i-j-1)] * a
    //        // e a propria soma pra multiplicar por i depois
    //        // somar com i+1 no final!
    //        for (int k = i, left = j-1; left >= 0 and k >= 1; --k, --left) dp[i][j] = (dp[i][j] + (i-k+2) * dp[max(0LL, k-2)][left]) % mod;
    //    }
    //    cout << endl;
    //}
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            int D = i-j-1+shift;
            if (j) dp[i][j] = (mod - d1[D] + i * d2[D]) % mod;
            else dp[i][j] = 1;
            if (i == j) dp[i][j] = (dp[i][j] + i + 1) % mod;
            D++;
            d1[D] = (d1[D] + dp[i][j] * i) % mod;
            d2[D] = (d2[D] + dp[i][j]) % mod;
        }
    }
    vector<vector<int>> onde(2, vector<int>(n)), g(n);
    for (int i = 0; i < n; ++i) onde[0][p[i]] = i, onde[1][q[i]] = i;
    for (int i = 0; i < n; ++i) g[i].pb(onde[1][p[i]]), g[i].pb(onde[0][q[i]]);
    vector<int> vis(n), ciclos;
    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;
        int cur = i, tam = 0;
        while (vis[cur] == 0) {
            vis[cur] = 1, tam++;
            for (auto v : g[cur]) {
                if (vis[v] == 0) { cur = v; break; }
            }
        }
        ciclos.pb(tam);
    }
    vector<int> fp(1);
    fp[0] = 1;
    for (auto x : ciclos) {
        vector<int> dp_eu(x+1);
        //cout << x << endl;
        // supoe que o primeiro cara do ciclo ta desligado
        for (int j = 0; j < x; ++j) dp_eu[j] = dp[x-1][j];
        // agora vamo ligar o cara do ciclo, fixando quantos tem vivo
        dp_eu[x] = (x != 1) + 1;
        for (int j = 1; j < x; ++j) {
            for (int fora = 0; fora + j + 2 <= x; ++fora) {
                dp_eu[j+fora] = (dp_eu[j+fora] + dp[x-j-2][fora] * j * (j+1)) % mod;
            }
        }
        // 1 2 3 4
        // 2 1 4 3
        // 1 dando errado: 8 maneiras
        // 2 dando errado: 20 maneiras
        // 3 dando errado: 16 maneiras
        // 4 dando errado: 4 maneiras
        // 24 - 8 * 3! + 20 * 2! - 16 * 1! + 4 * 0!
        dp_eu[x-1] = (dp_eu[x-1] + (x-1) * x) % mod;
        //for (auto y : dp_eu) cout << y << ' ';
        //cout << endl;
        vector<int> nfp(x+sz(fp));
        for (int i = 0; i < sz(fp); ++i) for (int j = 0; j <= x; ++j) nfp[j+i] = (nfp[j+i] + fp[i] * dp_eu[j]) % mod;
        swap(fp, nfp);
    }
    //cout << "fp: ";
    //for (auto x : fp) cout << x << ' ';
    //cout << endl;
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        int ways = fp[i] * fat[n-i] % mod;
        //cout << ways << endl;
        if (i&1) ans = (ans + mod - ways) % mod;
        else ans = (ans + ways) % mod;
    }
    return ans;
}

int brute(int n, vector<int> p, vector<int> q) {
    vector<int> r(n); iota(all(r), 0);
    int ans = 0;
    do {
        int ok = 1;
        for (int i = 0; i < n; ++i) ok &= (r[i] != p[i] and r[i] != q[i]);
        ans += ok;
    } while (next_permutation(all(r)));
    return ans;
}

int32_t main(){_
#ifndef gato
    int n; cin >> n;
    vector<int> p(n), q(n);
    for (auto& x : p) cin >> x, --x;
    for (auto& x : q) cin >> x, --x;
    cout << solve(n, p, q) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 5);
        vector<int> p(n), q(n); iota(all(p), 0), iota(all(q), 0);
        shuffle(all(p), rng);
        int my = solve(n, p, q), ans = brute(n, p, q);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : p) cout << x + 1 << ' ';
            cout << endl;
            for (auto x : q) cout << x + 1 << ' ';
            cout << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

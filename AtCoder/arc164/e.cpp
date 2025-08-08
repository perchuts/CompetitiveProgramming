#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define int long long
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
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
// [l, r] eh um node -> supoe q eh um filho esquerdo
// entao tem um node [l, r + k]
// porque isso eh importante? pq se [l, r]  \subset [l, r+k] \subset [lx[i], rx[i]], ent nao devo contar lx[i], rx[i]!!
ii solve(int n, int q, vector<int> lx, vector<int> rx){
    vector<vector<int>> fim(n+1, vector<int>(n+1)), comeco = fim, ps = fim, ps2 = fim;
    for (int i = 0; i < q; ++i) {
        fim[lx[i]][rx[i]]++;
        comeco[lx[i]][rx[i]]++;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = n-1; j >= 1; --j) fim[i][j] += fim[i][j+1];
    }
    for (int j = 1; j <= n; ++j) {
        for (int i = 2; i <= n; ++i) comeco[i][j] += comeco[i-1][j];
    }
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) ps[i][j] = fim[i][j] + ps[i-1][j], ps2[i][j] = comeco[i][j] + ps2[i][j-1];
	}
    vector<vector<ii>> dp(n+1, vector<ii>(n+1, {-inf, 0}));
    vector<vector<int>> opt(n+1, vector<int>(n+1));
    int sum = 0;
    for (int l = n; l >= 1; --l) {
        int lopt = l;
        for (int r = l; r <= n; ++r) { 
            dp[l][r] = {-1e18, 0};
            int tem = ps[l][r];
			int aft = (r == n ? 0 : ps[n][r+1] - ps[r][r+1]);
			int bef = ps2[l-1][l-1];
            bool nice = (tem + aft + bef == q);
            if (!nice) {
                dp[l][r] = {1e18, 0};
                for (int k = lopt; k <= opt[l+1][r]; ++k) {
                    sum++;
                    auto tmp = max(dp[l][k], dp[k+1][r]);
                    tmp.first++;
                    if (dp[l][k].first == dp[k+1][r].first) {
                        tmp.second = dp[l][k].second + dp[k+1][r].second;
                        if (tmp.first == 1) tmp.second -= 2*tem-fim[k+1][r]-comeco[l][k];
                    }
                    if (ckmin(dp[l][r], tmp))opt[l][r] = k;
                }
                assert(lopt <= opt[l][r]);
                lopt = opt[l][r];
                //cout << "l = " << l << " r = " << r << " opt = " << opt[l][r] << endl;
            } else {
                //cout << "l = " << l << " r = " << r << " opt = whatever" << endl;
                dp[l][r] = {0, tem};
                opt[l][r] = r-1;
            }
        }
    }
    //cout << sum << endl;
#ifndef gato
    //auto get = [&] (int i, int j) {
    //    if (max(i, j) > n) {
    //        cout << "NOPE" << endl;
    //        return;
    //    }
    //    cout << "dp["<<i<<"]["<<j<<"] = ";
    //    cout << dp[i][j].first << ' ' << dp[i][j].second << endl;
    //};
    //for (int i = 1; i <= n; ++i) {
    //    for (int j = i; j <= n; ++j) get(i, j);
    //}
#endif
    return dp[1][n];
}

ii cubic(int n, int q, vector<int> lx, vector<int> rx){
    vector<vector<int>> fim(n+1, vector<int>(n+1)), comeco = fim, ps = fim, ps2 = fim;
    for (int i = 0; i < q; ++i) {
        fim[lx[i]][rx[i]]++;
        comeco[lx[i]][rx[i]]++;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = n-1; j >= 1; --j) fim[i][j] += fim[i][j+1];
    }
    for (int j = 1; j <= n; ++j) {
        for (int i = 2; i <= n; ++i) comeco[i][j] += comeco[i-1][j];
    }
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) ps[i][j] = fim[i][j] + ps[i-1][j], ps2[i][j] = comeco[i][j] + ps2[i][j-1];
	}
    vector<vector<ii>> dp(n+1, vector<ii>(n+1, {-inf, 0}));
    for (int l = n; l >= 1; --l) {
        for (int r = l; r <= n; ++r) { 
            dp[l][r] = {-1e18, 0};
            int tem = ps[l][r];
			int aft = (r == n ? 0 : ps[n][r+1] - ps[r][r+1]);
			int bef = ps2[l-1][l-1];
            bool nice = (tem + aft + bef == q);
            if (!nice) {
                dp[l][r] = {1e18, 0};
                for (int k = l; k < r; ++k) {
                    auto tmp = max(dp[l][k], dp[k+1][r]);
                    tmp.first++;
                    if (dp[l][k].first == dp[k+1][r].first) {
                        tmp.second = dp[l][k].second + dp[k+1][r].second;
                        if (tmp.first == 1) tmp.second -= 2*tem-fim[k+1][r]-comeco[l][k];
                    }
                    ckmin(dp[l][r], tmp);
                }
            } else if (tem) dp[l][r] = {0, tem};
            else dp[l][r] = {0, 0};
        }
    }
#ifndef gato
    auto get = [&] (int i, int j) {
        if (max(i, j) > n) {
            cout << "NOPE" << endl;
            return;
        }
        cout << "dp["<<i<<"]["<<j<<"] = ";
        cout << dp[i][j].first << ' ' << dp[i][j].second << endl;
    };
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) get(i, j);
    }
#endif
    return dp[1][n];
}

vector<vector<vector<int>>> diversao[20];
vector<vector<ii>> sexo[20];

ii brute(int n, int q, vector<int> lx, vector<int> rx) {
    // bruta todas as arvores binarias e testa
    ii ans = {inf, inf};
    for (int i = 0; i < sz(diversao[n]); ++i) {
        auto g = diversao[n][i];
        auto range = sexo[n][i];
        //if (i == 0) {
            //for (auto u : g) {
            //    for (auto v : u) cout << v << ' ';
            //    cout << endl;
            //}
            //cout << "adsa" << endl;
            //for (auto [aa, bb] : range) cout << aa << ' ' << bb << endl;
        //}
        vector<int> deps(n+1);
        auto search = [&] (auto&& dfs, int k, int lp, int rp, int dep) -> void {
            deps[dep]++;
            if (range[k].second < lp or rp < range[k].first) return;
            if (lp <= range[k].first and range[k].second <= rp) return;
            dfs(dfs, g[k][0], lp, rp, dep+1);
            dfs(dfs, g[k][1], lp, rp, dep+1);
        };
        for (int j = 0; j < q; ++j) search(search, sz(g)-1, lx[j], rx[j], 0);
        for (int j = n; j >= 0; --j) {
            if (deps[j]) {
                ckmin(ans, pair(j, deps[j]));
                break;
            }
        }
    }
    return ans;
}

ii solve_edi(int n, int q, vector<int> lx, vector<int> rx) {
	vector<int> w(n+1);
	int aa = 0;
    for (int i = 0; i < q; ++i) {
		int l = lx[i], r = rx[i];
        w[l-1]++;
        w[r]++;
        if (l == r) aa++;
    }
	vector<int> nw;
	for (int i = 1; i < n; ++i) if (w[i] != 0) nw.pb(w[i]);
	if (nw.empty()) return {0, q};
    if (n == 2) {
        if (aa == 0) return {0, q};
        return {1, 2*aa};
    }
	n = sz(nw);
	swap(w, nw);
    int tot = 1, d = 1;
    while (tot < n) tot = 2 * tot + 1, d++;
    int skip = tot - n;
    vector<vector<int>> dp(tot+1, vector<int>(skip+1, inf));
    dp[0][0] = 0;
    for (int i = 1; i <= tot; ++i) {
        for (int j = 0; j <= skip; ++j) {
            int act = i - j - 1;
			// not skip
            if (0 <= act and act < n) dp[i][j] = dp[i-1][j] + (i&1 ? w[act] : 0);
			// skip
            if (j and i % 2 == 1) ckmin(dp[i][j], dp[i-1][j-1]);
        }
    }
	return {d, 2 * dp[tot][skip]};
}

int32_t main() {_
#ifndef gato
    int n, q; cin >> n >> q;
    vector<int> lx(q), rx(q);
    for (int i = 0; i < q; ++i) cin >> lx[i] >> rx[i];
    auto [a, b] = solve_edi(n, q, lx, rx);
    cout << a << ' ' << b << endl;
#else
    int t = 1;
    int lim = 40;
    diversao[1] = {{{}}};
    sexo[1] = {{{1, 1}}};
    while (true) {
        int n = rnd(lim, lim), q = rnd(1, 100);
        vector<int> lx(q), rx(q);
        for (int i = 0; i < q; ++i) lx[i] = rnd(1, n), rx[i] = rnd(lx[i], n);
        ii my = solve_edi(n, q, lx, rx);
        ii ans = solve(n, q, lx, rx);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << q << endl;
            for (int i = 0; i < q; ++i) cout << lx[i] << ' ' << rx[i] << endl;
            cout << "Your output: " << my.first << ' ' << my.second << endl;
            cout << "Answer: " << ans.first << ' ' << ans.second << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
        //cout << "n = " << n << " q = " << q << endl;
        //cout << my.first << ' ' << my.second << endl;
    }
#endif
}

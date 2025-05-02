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

const int inf = 9e18+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// Z
// 
// z[i] = lcp(s, s[i..n))
//
// Complexidades:
// z - O(|s|)
// match - O(|s| + |p|)

vector<int> get_z(string s) {
	int n = s.size();
	vector<int> z(n, 0);

	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r) z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n and s[z[i]] == s[i + z[i]]) z[i]++;
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}

	return z;
}
// KMP
//
// matching(s, t) retorna os indices das ocorrencias
// de s em t
// autKMP constroi o automato do KMP
//
// Complexidades:
// pi - O(n)
// match - O(n + m)
// construir o automato - O(|sigma|*n)
// n = |padrao| e m = |texto|

template<typename T> vector<int> pi(T s) {
	vector<int> p(s.size());
	for (int i = 1, j = 0; i < s.size(); i++) {
		while (j and s[j] != s[i]) j = p[j-1];
		if (s[j] == s[i]) j++;
		p[i] = j;
	}
	return p;
}

void solve(){
    string s, t; cin >> s >> t;
    swap(s, t);
    int n = sz(s), m = sz(t);
    if (n == m) {
        cout << 0 - (s == t) << endl;
        exit(0);
    }
    if (n < m) {
        string kx = s + "#" + t + t;
        auto kmp = pi(kx);
        vector<int> setinha(m, -1);
        for (int i = 0; i < m; ++i) {
            if (kmp[2*n+i] == n) setinha[i] = (i + n) % m;
        }
        int g = gcd(n, m), ans = 0;
        for (int i = 0; i < g; ++i) {
            int pos = -1;
            for (int j = 0; j < m/g; ++j) if (setinha[(n*j+i)%m] == -1) pos = (n*j+i)%m;
            if (pos == -1) {
                cout << -1 << endl;
                exit(0);
            }
            int cur = 0;
            for (int j = 0; j < m/g; ++j) {
                if (setinha[pos] == -1) cur = 0;
                else cur++;
                ckmax(ans, cur);
                pos = (pos + n) % m;
            }
        }
        cout << ans << endl;
        exit(0);
    }
    // n > m
    // LCP(T, sufixo de S)
    string zx = t + "#" + s;
    auto Z = get_z(zx);
    string kx = s + "#" + t;
    auto kmp = pi(kx);
    vector<int> setinha(n), ok(n, 1);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        // s[i, n) -> t[0, m)
        int tam = Z[m+1+i];
        int mx = min(m, n-i);
        if (tam != mx) assert(tam < mx), setinha[i] = -1, ok[i] = 0;
        else {
            if (n-i == mx) {
                int falta = m - mx;
                if (kmp[n+falta] != falta) setinha[i] = -1;
                else setinha[i] = falta, g[falta].pb(i);
            } else setinha[i] = i + m, g[i+m].pb(i);
        }
    }
    // vou basicamente escolher um lugar pra comecar, e depois vou sair andando!
    vector<int> dp(n, inf);
    auto dfs = [&] (auto&& self, int u) -> void {
        dp[u] += (u >= n-m);
        for (auto v : g[u]) {
            dp[v] = dp[u];
            self(self, v);
        }
    };
    for (int i = 0; i < n; ++i) if (ok[i] and setinha[i] == -1) dfs(dfs, i);
    // certo, agora vou escolher quando vou comecar o match
    string zx2 = s + "#" + t;
    auto Z2 = get_z(zx2);
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        if (Z2[n+1+i] == m-i and ok[m-i]) ckmax(ans, dp[m-i]);
    }
    cout << (ans == inf ? -1 : ans) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

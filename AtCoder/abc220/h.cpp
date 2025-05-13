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
template<char op> vector<int> FWHT(vector<int> f, bool inv = false) {
	int n = f.size();
	for (int k = 0; (n-1)>>k; k++) for (int i = 0; i < n; i++) if (i>>k&1) {
		int j = i^(1<<k);
		if (op == '^') f[j] += f[i], f[i] = f[j] - 2*f[i];
		if (op == '|') f[i] += (inv ? -1 : 1) * f[j];
		if (op == '&') f[j] += (inv ? -1 : 1) * f[i];
	}
	if (op == '^' and inv) for (auto& i : f) i /= n;
	return f;
}
void solve(){
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        adj[u][v] = adj[v][u] = true;
    }
    int l = n/2;
    vector<int> par(1<<l, -1), mask(1<<l), viz(l), par2(1<<(n-l), -1);
    for (int i = 0; i < l; ++i) for (int j = l; j < n; ++j) viz[i] += (adj[i][j] << (j-l));
    par[0] = 0;
    vector A(2, vector(2, vector(1<<(n-l), 0LL))), B = A;
    for (int i = 0; i < (1<<l); ++i) {
        for (int j = 0; j < l; ++j) {
            if (i >> j & 1) {
                if (par[i] == -1) {
                    par[i] = par[i - (1<<j)];
                    for (int k = 0; k < n; ++k) {
                        if (adj[j][k] and (k >= l or !(i>>k&1))) par[i] ^= 1;
                    }
                }
                mask[i] ^= viz[j];
            }
        }
        A[1][par[i]][mask[i]]++;
        A[0][par[i]][mask[i]]++;
    }
    par2[0] = 0;
    for (int i = 0; i < (1<<(n-l)); ++i) {
        for (int j = 0; j < n-l; ++j) {
            if (i >> j & 1) {
                if (par2[i] == -1) {
                    par2[i] = par2[i - (1<<j)];
                    for (int k = 0; k < n; ++k) {
                        if (adj[l+j][k] and (k < l or !(i>>(k-l)&1))) par2[i] ^= 1;
                    }
                }
            }
        }
        B[par2[i]][0][i]++;
        B[par2[i]][1][i]++;
    }
    int ans = 0;
    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 2; ++y) {
            // faz um and convolution aqui
            A[x][y] = FWHT<'&'>(A[x][y]);
            B[x][y] = FWHT<'&'>(B[x][y]);
            vector<int> res(1<<(n-l));
            for (int i = 0; i < 1<<(n-l); ++i) res[i] = A[x][y][i] * B[x][y][i];
            res = FWHT<'&'>(res, true);
            for (int i = 0; i < 1<<(n-l); ++i) {
                if (__builtin_popcount(i) % 2 == (x^y)) ans += res[i];
            }

        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

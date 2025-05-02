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
// 2-SAT
//
// solve() retorna um par, o first fala se eh possivel
// atribuir, o second fala se cada variavel eh verdadeira
//
// O(|V|+|E|) = O(#variaveis + #restricoes)

struct sat {
	int n, tot;
	vector<vector<int>> g;
	vector<int> vis, comp, id, ans;
	stack<int> s;

	sat() {}
	sat(int n_) : n(n_), tot(n), g(2*n) {}

	int dfs(int i, int& t) {
		int lo = id[i] = t++;
		s.push(i), vis[i] = 2;
		for (int j : g[i]) {
			if (!vis[j]) lo = min(lo, dfs(j, t));
			else if (vis[j] == 2) lo = min(lo, id[j]);
		}
		if (lo == id[i]) while (1) {
			int u = s.top(); s.pop();
			vis[u] = 1, comp[u] = i;
			if ((u>>1) < n and ans[u>>1] == -1) ans[u>>1] = ~u&1;
			if (u == i) break;
		}
		return lo;
	}

	void add_impl(int x, int y) { // x -> y = !x ou y
		x = x >= 0 ? 2*x : -2*x-1;
		y = y >= 0 ? 2*y : -2*y-1;
		g[x].push_back(y);
		g[y^1].push_back(x^1);
	}
	void add_cl(int x, int y) { // x ou y
		add_impl(~x, y);
	}
	void add_xor(int x, int y) { // x xor y
		add_cl(x, y), add_cl(~x, ~y);
	}
	void add_eq(int x, int y) { // x = y
		add_xor(~x, y);
	}
	void add_true(int x) { // x = T
		add_impl(~x, x);
	}
	void at_most_one(vector<int> v) { // no max um verdadeiro
		g.resize(2*(tot+v.size()));
		for (int i = 0; i < v.size(); i++) {
			add_impl(tot+i, ~v[i]);
			if (i) {
				add_impl(tot+i, tot+i-1);
				add_impl(v[i], tot+i-1);
			}
		}
		tot += v.size();
	}

	pair<bool, vector<int>> solve() {
		ans = vector<int>(n, -1);
		int t = 0;
		vis = comp = id = vector<int>(2*tot, 0);
		for (int i = 0; i < 2*tot; i++) if (!vis[i]) dfs(i, t);
		for (int i = 0; i < tot; i++)
			if (comp[2*i] == comp[2*i+1]) return {false, {}};
		return {true, ans};
	}
};
void solve(){
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    vector<int> pr(10*maxn);
    for (int i = 2; i < 10*maxn; ++i) {
        if (pr[i]) continue;
        pr[i] = i;
        for (int j = i*i; j < 10*maxn; j += i) pr[j] = i;
    }
    vector<vector<int>> list(10*maxn);
    sat S(2*n);
    for (int i = 0; i < n; ++i) {
        S.add_xor(i, i+n); 
        for (int id = i; id < 2*n; id += n) {
            int val = a[i];
            while (val != 1) {
                int p = pr[val];
                while (pr[val] == p) val /= p;
                list[p].pb(id);
            }
            swap(a[i], b[i]);
        }
    }
    for (int i = 2; i < 10 * maxn; ++i) {
        if (!list[i].empty()) S.at_most_one(list[i]);
    }
    auto [ans, lixo] = S.solve();
    cout << (ans ? "Yes" : "No") << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

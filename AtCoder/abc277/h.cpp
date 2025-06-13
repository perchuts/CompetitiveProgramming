#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    int n, m, q; cin >> n >> m >> q;
    vector<int> a(q), b(q), l(q), r(q);
    for (int i = 0; i < q; ++i) cin >> a[i] >> b[i] >> l[i] >> r[i], --a[i], --b[i];
    ++m;
    sat ss(2*n*m);
    for (int i = 0; i < n; ++i) {
        // m*i+j = sou maior ou igual a (j+1)?
        // n*m+m*i+j = sou menor ou igual a (j+1)?
        for (int j = 1; j < m; ++j) {
            ss.add_impl(m*i+j, m*i+j-1);
            ss.add_xor(m*i+j, n*m+m*i+j-1);
        }
        for (int j = m-2; j >= 0; --j) {
            ss.add_impl(n*m+m*i+j, n*m+m*i+j+1);
            ss.add_xor(n*m+m*i+j, m*i+j+1);
        }
        ss.add_true(m*i);
        ss.add_true(n*m+m*i+m-1);
    }
    for (int i = 0; i < q; ++i) {
        // e se x[a[i]] = j?
        if (r[i] < m) {
            ss.add_true(n*m+m*a[i]+r[i]);
            ss.add_true(n*m+m*b[i]+r[i]);
        }
        for (int j = 0; j <= min(r[i], m-1); ++j) {
            int mn = max(0, l[i]-j), mx = min(m-1, r[i]-j);
            for (int turn = 0; turn < 2; ++turn) {
                if (mn >= m) {
                    ss.add_true(~(n*m+m*a[i]+j));
                } else {
                    ss.add_impl(m*a[i]+j, n*m+m*b[i]+mx);
                    // x[a[i]] >= j => x[b[i]] <= mx
                    // x[a[i]] >= j => x[b[i]] >= mn
                    ss.add_impl(n*m+m*a[i]+j, m*b[i]+mn);

                    // x[a[i]] <= j => x[b[i]] >= mn
                }
                swap(a[i], b[i]);
            }
        }
    }
    auto [state, certificate] = ss.solve();
    if (!state) {
        cout << -1 << endl;
        exit(0);
    }
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            if (certificate[m*i+j]) ans[i]++;
        }
        //cout << "variavel i = " << i << endl;
        //cout << ">=: ";
        //for (int j = 0; j < m; ++j) cout << certificate[m*i+j] << ' ';
        //cout << endl;
        //cout << "<=: ";
        //for (int j = 0; j < m; ++j) cout << certificate[n*m+m*i+j] << ' ';
        //cout << endl;
        cout << ans[i] << ' ';
    }
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

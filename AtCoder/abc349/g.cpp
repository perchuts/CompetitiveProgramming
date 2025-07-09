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

vector<int> solve(int n, vector<int> a) {
    vector<int> par(n), lvl(n);
    iota(all(par), 0);
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    auto unite = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        if (lvl[u] == lvl[v]) ++lvl[u];
    };
    int r = -1, l = -1;
    for (int i = 0; i < n; ++i) {
        if (r < i) {
            for (int j = 1; j <= a[i]; ++j) unite(i-j, i+j);
            l = i - a[i], r = i + a[i];
        } else {
            int k = r - i + 1;
			int mirror = l + r - i;
			if (l < mirror - a[mirror] and a[mirror] < a[i]) {
				return vector<int>();
			}
            while (k <= a[i]) unite(i - k, i + k), k++;
            --k;
			if (i + k > r or (i + k == r and i - k < l)) l = i - k, r = i + k;
        }
    }
    for (int i = 0; i < n; ++i) findp(findp, i);
	//for (auto x : par) cout << x << ' ';
	//cout << endl;
    vector<set<int>> forb(n);
    set<ii> todos;
    vector<int> labels, val(n), vis(n, -1);
    for (int i = 0; i < n; ++i) {
        if (vis[par[i]] == -1) {
            vis[par[i]] = sz(todos);
            todos.insert({sz(todos), par[i]});
            labels.pb(par[i]);
        }
        if (i - a[i] != 0 and i + a[i] < n-1) {
            if (par[i - a[i] - 1] == par[i + a[i] + 1]) return vector<int>();
            forb[par[i-a[i]-1]].insert(par[i+a[i]+1]);
            forb[par[i+a[i]+1]].insert(par[i-a[i]-1]);
        }
    }
    int m = sz(labels), cur = 1;
    for (int i = 0; i < m; ++i) {
        if (val[labels[i]]) continue;
        int eu = labels[i];
        todos.erase({i, eu});
        val[eu] = cur++;
        vector<int> rem;
        for (auto [a, b] : todos) {
            if (forb[eu].find(b) == end(forb[eu])) {
                rem.pb(b);
                for (auto c : forb[b]) forb[eu].insert(c);
            }
        }
        for (auto x : rem) todos.erase({vis[x], x}), val[x] = val[eu];
    }
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) ans[i] = val[par[i]];
    return ans;
}

vector<int> brute(int n, vector<int> a) {
    vector<int> cur(n), resp;
    auto go = [&] (auto&& self, int i) -> bool {
        if (i == n) {
            for (int j = 0; j < n; ++j) {
                for (int k = 1; k <= a[j]; ++k) {
                    if (cur[j-k] != cur[j+k]) return false;
                }
                int k = a[j];
                if (j-k != 0 and j+k != n-1 and cur[j-k-1] == cur[j+k+1]) return false;
            }
            resp = cur;
            return true;
        }
        for (int j = 1; j <= n; ++j) {
            cur[i] = j;
            if (self(self, i+1)) return true;
        }
        return false;
    };
    go(go, 0);
    return resp;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    auto ans = solve(n, a);
    if (ans.empty()) {
        cout << "No" << endl;
        exit(0);
    }
    cout << "Yes" << endl;
    for (auto x : ans) cout << x << ' ';
    cout << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 10);
        vector<int> a(n);
        for (int i = 0; i < n; ++i) a[i] = rnd(0, min(i, n-1-i));
        auto my = solve(n, a);
		if (my.empty()) continue;
        auto ans = brute(n, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            cout << "Your output: ";
            for (auto x : my) cout << x << ' ';
            cout << endl;
            cout << "Resp: ";
            for (auto x : ans) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

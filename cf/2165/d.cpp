#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato
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
// Kuhn
//
// Computa matching maximo em grafo bipartido
// 'n' e 'm' sao quantos vertices tem em cada particao
// chamar add(i, j) para add aresta entre o cara i
// da particao A, e o cara j da particao B
// (entao i < n, j < m)
// Para recuperar o matching, basta olhar 'ma' e 'mb'
// 'recover' recupera o min vertex cover como um par de
// {caras da particao A, caras da particao B}
//
// O(|V| * |E|)
// Na pratica, parece rodar tao rapido quanto o Dinitz


struct kuhn {
	int n, m;
	vector<vector<int>> g;
	vector<int> vis, ma, mb;

	kuhn(int n_, int m_) : n(n_), m(m_), g(n),
		vis(n+m), ma(n, -1), mb(m, -1) {}

	void add(int a, int b) { g[a].push_back(b); }

	bool dfs(int i) {
		vis[i] = 1;
		for (int j : g[i]) if (!vis[n+j]) {
			vis[n+j] = 1;
			if (mb[j] == -1 or dfs(mb[j])) {
				ma[i] = j, mb[j] = i;
				return true;
			}
		}
		return false;
	}
	int matching() {
		int ret = 0, aum = 1;
		for (auto& i : g) shuffle(i.begin(), i.end(), rng);
		while (aum) {
			for (int j = 0; j < m; j++) vis[n+j] = 0;
			aum = 0;
			for (int i = 0; i < n; i++)
				if (ma[i] == -1 and dfs(i)) ret++, aum = 1;
		}
		return ret;
	}
};

pair<vector<int>, vector<int>> recover(kuhn& K) {
	K.matching();
	int n = K.n, m = K.m;
	for (int i = 0; i < n+m; i++) K.vis[i] = 0;
	for (int i = 0; i < n; i++) if (K.ma[i] == -1) K.dfs(i);
	vector<int> ca, cb;
	for (int i = 0; i < n; i++) if (!K.vis[i]) ca.push_back(i);
	for (int i = 0; i < m; i++) if (K.vis[n+i]) cb.push_back(i);
	return {ca, cb};
}
int brute(int n, vector<int> a) {
    kuhn cu(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (abs(a[i] - a[j]) == 1) cu.add(i, j);
        }
    }
    return n-cu.matching();
}

int solve(int n, vector<int> a) {
    // lets start by considering the smallest value.
    // order the ocurrences of it.
    // if min(a) = x occurrs at i1 < i2 < ... < ik, we can always take out on suffix and in on prefix.
    // my guess is that i will always take the maximum number of occurrences possible.
    // and then take least damaging ocurrences possible.
    // by definition we are only considering i -> i+1.
    // only need to optimize this.
    vector<set<int>> occ_in(2*n+1), occ_out(2*n+1);
    for (int i = 0; i < n; ++i) occ_in[a[i]].insert(i), occ_out[a[i]].insert(i);
    int ans = 0;
    for (int i = 1; i < 2*n; ++i) {
        // parear out
        {
            auto it = begin(occ_out[i]);
            while (it != end(occ_out[i])) {
                int x = *it;
                auto prox = occ_in[i+1].lower_bound(x);
                if (prox == end(occ_in[i+1])) break;
                it = next(it);
                //cout << (x) << " " << (*prox) << endl;
                occ_out[i].erase(x);
                occ_in[i+1].erase(*prox);
                ans++;
            }
        }
        // parear in
        if (!occ_in[i].empty()) {
            auto it = prev(end(occ_in[i]));
            while (true) {
                int x = *it;
                auto prox = occ_out[i+1].lower_bound(x);
                if (prox == begin(occ_out[i+1])) break;
                prox = prev(prox);
                if (it != begin(occ_in[i])) it = prev(it);
                //cout << (*prox) << " " << x << endl;
                occ_in[i].erase(x);
                occ_out[i+1].erase(*prox);
                ans++;
                if (occ_in[i].empty()) break;
            }
        }
    }
    return n - ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        cout << solve(n, a) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 50);
        vector<int> a(n);
        for (auto& x : a) x = rnd(1, 2*n);
        auto my = solve(n, a);
        auto ans = brute(n, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

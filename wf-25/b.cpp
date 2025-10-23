#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 1e7+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

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

int crivo[maxn], side[maxn];

bool checker(int n, int k) {
    auto go = [&] (int x) {
        kuhn cu(n+1, n+1);
        for (int i = 1; i <= n; ++i) {
            for (int j = 2*i; j <= n; j += i) {
                if (i == x or j == x or crivo[j/i]) continue;
                int aa = i, bb = j;
                if (side[aa]) swap(aa, bb);
                cu.add(aa, bb);
            }
        }
        return cu.matching();
    };
    return (go(-1) == go(k));
}

int solve(int n) {
    // quero garantir q existe primo P tal que 3P <= N e que existe maximum matching onde 2, 3 nao pareiam com P, 2P ou 3P
    // se existir 4 primos com 4P > N e 3P <= N, acho que fizemos o W
    if (n >= 180) {
        int ans = -1;
        for (int i = 2; i <= n; ++i) {
            if (crivo[i] == 0 and 4 * i > n and 3 * i <= n) { ans = 2 * i; break; }
        }
        return ans;
    }
    auto go = [&] (int x) {
        kuhn cu(n+1, n+1);
        for (int i = 1; i <= n; ++i) {
            for (int j = 2*i; j <= n; j += i) {
                if (i == x or j == x or crivo[j/i]) continue;
                int aa = i, bb = j;
                if (side[aa]) swap(aa, bb);
                cu.add(aa, bb);
            }
        }
        return cu.matching();
    };
    int mx = go(-1);
    for (int i = 2; i <= n; i += 2) {
        if (go(i) == mx) {
            return i;
        }
    }
    return -1;
}

int32_t main() {_
    int lim = 1e7 + 10;
    for (int i = 2; i * i < lim; ++i) {
        if (crivo[i]) continue;
        for (int j = i * i; j < lim; j += i) crivo[j] = 1;
    }
    int lim2 = 180;
    for (int i = 2; i < lim2; ++i) {
        if (crivo[i] == 0) {
            side[i] = 1;
            continue;
        }
        for (int j = 2; ; ++j) {
            if (i % j == 0) {
                side[i] = 1 ^ side[i/j];
                break;
            }
        }
    }
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        int ans = solve(n);
        if (ans == -1) cout << "second" << endl;
        else cout << "first " << ans << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(112, 200);
        int my = solve(n);
        if (checker(n, my) == false) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            cout << "Your output: " << my << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

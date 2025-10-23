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

pair<long double, vector<int>> brute(int n, vector<ii> v) {
    vector<int> ids(n); iota(all(ids), 0);
    auto sortar = [&] (int l, int r, bool type) {
        if (type == 0) {
            sort(begin(ids)+l, begin(ids)+r+1, [&] (int x, int y) {
                return v[x].first < v[y].first;
            });
        } else {
            sort(begin(ids)+l, begin(ids)+r+1, [&] (int x, int y) {
                return v[x].second < v[y].second;
            });
        }
    };
    // constroi a porra da arvore ai irmao
	// meu saco
    vector<ii> ranges;
    vector<ii> filhos;
    vector<vector<int>> bichos;
    auto build = [&] (auto&& self, int l, int r, bool tipo) -> int {
        sortar(l, r, tipo);
        int eu = sz(ranges);
        ranges.pb({l, r});
        bichos.pb({});
        for (int i = l; i <= r; ++i) bichos.back().pb(ids[i]);
        if (l == r) {
            filhos.pb({-1, -1});
            return eu;
        }
        int md = (l+r-1)/2;
        filhos.pb({-1, -1});
        filhos[eu].first = self(self, l, md, tipo^1);
        filhos[eu].second = self(self, md+1, r, tipo^1);
        return eu;
    };
    int root = build(build, 0, n-1, 0), src = 2*n+2*sz(filhos), sink = src+1, fake = sink+1;
    using ld = long double;
    int N = sz(ranges);
    vector<vector<vector<ld>>> dp(N, vector<vector<ld>>(n, vector<ld>(n, 1e18)));
    vector<vector<vector<array<int, 3>>>> rec(N, vector<vector<array<int, 3>>>(n, vector<array<int, 3>>(n)));
    vector<int> ord;
    for (int i = 0; i < N; ++i) {
        if (ranges[i].first == ranges[i].second) ord.pb(ids[ranges[i].first]);
    }
    int trs = 0;
    auto dfs = [&] (auto&& self, int i) -> void {
        auto [l, r] = ranges[i];
        if (l == r) {
            dp[i][bichos[i][0]][bichos[i][0]] = 0;
            return;
        }
        auto [fl, fr] = filhos[i];
        self(self, fl);
        self(self, fr);
        for (auto stl : bichos[fl]) {
            for (auto edl : bichos[fl]) {
                for (auto str : bichos[fr]) {
                    for (auto edr : bichos[fr]) {
                        if (dp[fl][stl][edl] + dp[fr][str][edr] < 1e10) trs++;
                        if (dp[fl][stl][edl] + dp[fr][str][edr] < 1e10) trs++;
                        if (ckmin(dp[i][stl][edr], dp[fl][stl][edl] + dp[fr][str][edr] + hypot(v[edl].first-v[str].first, v[edl].second-v[str].second))) {
                            rec[i][stl][edr][0] = edl;
                            rec[i][stl][edr][1] = str;
                            rec[i][stl][edr][2] = 0;
                        }
                        if (ckmin(dp[i][str][edl], dp[fl][stl][edl] + dp[fr][str][edr] + hypot(v[edr].first-v[stl].first, v[edr].second-v[stl].second))) {
                            rec[i][str][edl][0] = stl;
                            rec[i][str][edl][1] = edr;
                            rec[i][str][edl][2] = 1;
                        }
                    }
                }
            }
        }
    };
    dfs(dfs, 0);
    ld ans = 1e18;
    ii best;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (ckmin(ans, dp[root][i][j])) {
                best.first = i, best.second = j;
            }
        }
    }
    vector<int> passeio;
    auto recover = [&] (auto&& self, int i, int st, int ed) -> void {
        if (st == ed) { passeio.pb(st); return; }
        int tipo = rec[i][st][ed][2];
        int x = rec[i][st][ed][0];
        int y = rec[i][st][ed][1];
        auto [fl, fr] = filhos[i];
        if (tipo) {
            self(self, fr, st, y);
            self(self, fl, x, ed);
        } else {
            self(self, fl, st, x);
            self(self, fr, y, ed);
        }
    };
    // dp[altura][vertice] = esse bicho sobra no final
    recover(recover, 0, best.first, best.second);
    // da pra olhar pra 2^5 bichos de cada vez
    auto check = [&] () {
        ld tot = 0;
        for (int i = 0; i < n-1; ++i) {
            auto x = passeio[i];
            auto y = passeio[i+1];
            tot += hypot(v[x].first-v[y].first, v[x].second-v[y].second);
        }
        return tot;
    };
    int cnt = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (dp[i][j][k] < 1e10) cnt++;
            }
        }
    }
    return pair(ans, passeio);
    return pair(0, vector<int>());
}

pair<long double, vector<int>> solve(int n, vector<ii> v) {
    if (n == 1) return pair(0.0, vector<int>(1, 0));
    vector<int> ids(n); iota(all(ids), 0);
    auto sortar = [&] (int l, int r, bool type) {
        if (type == 0) {
            sort(begin(ids)+l, begin(ids)+r+1, [&] (int x, int y) {
                return v[x].first < v[y].first;
            });
        } else {
            sort(begin(ids)+l, begin(ids)+r+1, [&] (int x, int y) {
                return v[x].second < v[y].second;
            });
        }
    };
    // constroi a porra da arvore ai irmao
	// meu saco
    vector<ii> ranges;
    vector<ii> filhos;
    vector<vector<int>> bichos;
    vector<int> ayuda;
    auto build = [&] (auto&& self, int l, int r, bool tipo) -> int {
        sortar(l, r, tipo);
        int eu = sz(ranges);
        ranges.pb({l, r});
        bichos.pb({});
        ayuda.pb(tipo);
        for (int i = l; i <= r; ++i) bichos.back().pb(ids[i]);
        if (l == r) {
            filhos.pb({-1, -1});
            return eu;
        }
        int md = (l+r-1)/2;
        filhos.pb({-1, -1});
        filhos[eu].first = self(self, l, md, tipo^1);
        filhos[eu].second = self(self, md+1, r, tipo^1);
        return eu;
    };
    int root = build(build, 0, n-1, 0), src = 2*n+2*sz(filhos), sink = src+1, fake = sink+1;
    using ld = long double;
    int N = sz(ranges);
	vector<vector<ld>> dpL(N, vector<ld>(N, 1e18)), dp = dpL, trL = dp, tr = dp;
    // dpL[i][j] = (i ta na esquerda esquerda, j ta na direita esquerda)
    //
    vector<vector<ld>> dist(n, vector<ld>(n));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        dist[i][j] = hypot(v[i].first-v[j].first, v[i].second-v[j].second);
    }
	auto dfs = [&] (auto&& self, int i) -> void {
		auto& [u, v] = filhos[i];
		if (u == -1) {
            int z = bichos[i][0];
            u = v = i;
            dpL[z][z] = dp[z][z] = 0;
			return;
		}
		self(self, u), self(self, v);
        auto [ee, ed] = filhos[u];
        auto [de, dd] = filhos[v];
        for (auto esq : bichos[ee]) {
            for (auto dir : bichos[v]) {
                for (auto esq2 : bichos[ed]) {
                    if (ckmin(dpL[esq][dir], dp[esq][esq2] + dist[esq2][dir])) trL[esq][dir] = esq2;
                    if (ckmin(dpL[esq2][dir], dp[esq2][esq] + dist[esq][dir])) trL[esq2][dir] = esq;
                }
            }
        }
        for (auto dir : bichos[de]) {
            for (auto esq : bichos[u]) {
                for (auto dir2 : bichos[dd]) {
                    if (ckmin(dpL[dir][esq], dp[dir][dir2] + dist[dir2][esq])) trL[dir][esq] = dir2;
                    if (ckmin(dpL[dir2][esq], dp[dir2][dir] + dist[dir][esq])) trL[dir2][esq] = dir;
                }
            }
        }
        for (int __ = 0; __ < 4; ++__) {
            for (auto d1 : bichos[de]) {
                for (auto e1 : bichos[ee]) {
                    for (auto e2 : bichos[ed]) {
                        if (ckmin(dp[d1][e1], dpL[d1][e2] + dp[e2][e1])) tr[d1][e1] = e2;
                    }
                    for (auto d2 : bichos[dd]) {
                        if (ckmin(dp[e1][d1], dpL[e1][d2] + dp[d2][d1])) tr[e1][d1] = d2;
                    }
                }
            }
            if (__ % 2) swap(ee, ed);
            else swap(de, dd);
        }
	};
    dfs(dfs, root);
    ld ans = 1e18;
    int bl, br;
    for (auto esq : bichos[filhos[root].first]) {
        for (auto dir : bichos[filhos[root].second]) {
            if (ckmin(ans, dp[esq][dir])) bl = esq, br = dir;
            if (ckmin(ans, dp[dir][esq])) bl = dir, br = esq;
        }
    }
    vector<int> passeio;
    auto go = [&] (auto&& self, int l, int r) -> void {
        if (l == r) {
            passeio.push_back(l);
            return;
        }
        int argmin1 = tr[l][r];
        int argmin2 = trL[l][argmin1];
        self(self, l, argmin2);
        self(self, argmin1, r);
    };
    go(go, bl, br);
    return pair(ans, passeio);
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<ii> v(n);
        for (auto& [x, y] : v) cin >> x >> y;
        auto [ret, p] = solve(n, v);
        cout << fixed << setprecision(10) << ret << endl;
        for (auto x : p) cout << x+1 << ' ';
        cout << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(5, 30);
        vector<ii> pts(n);
		map<int, bool> m1;
		map<int, bool> m2;
        const int lim = 200;
        for (auto& [x, y] : pts) {
            while (true) {
                x = rnd(0, lim), y = rnd(0, lim);
				if (m1[x] == false and m2[y] == false) break;
            }
			m1[x] = m2[y] = true;
        }
        using ld = long double;
        auto [my, cert_my] = solve(n, pts);
        auto [ans, cert_ans] = brute(n, pts);
        cout << fixed << setprecision(15);
        if (abs(my-ans) > 1) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto [x, y] : pts) cout << x << ' ' << y << endl;
            cout << "Your output: " << my << endl;
            for (auto x : cert_my) cout << x + 1 << ' ';
            cout << endl;
            cout << "Answer: " << ans << endl;
            for (auto x : cert_ans) cout << x + 1 << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

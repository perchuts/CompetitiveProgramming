#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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


vector<vector<int>> oracle(int n, int H, int W, vector<int> h, vector<int> t) {
	vector<int> ord(n); iota(begin(ord), end(ord), 0);
	sort(begin(ord), end(ord), [&] (int x, int y) {
		return h[x] > h[y];
	});
	int fora = 0;
	int Z = max(H, W) + 10;
	for (int l = 0, r = 0; l != n; l = r) {
		while (r != n and h[ord[l]] == h[ord[r]]) r++;	
		for (int bicho = l; bicho < r; ++bicho) {
			vector dp(n+1, vector(Z+1, 0));
			vector tr(n+1, vector(Z+1, -1));
			dp[l][0] = 1;
			int tudo = 0;
			for (int i = l+1; i <= n; ++i) {
				if (i-1 != bicho) tudo += t[ord[i-1]];
				for (int j = 0; j <= Z; ++j) {
					if (i-1 == bicho) {
						dp[i][j] = dp[i-1][j], tr[i][j] = j;
						continue;
					}
					dp[i][j] = dp[i-1][j];
					tr[i][j] = j;
					// so pode por em pe se isso acontecer!!
					if (j-t[ord[i-1]] >= 0 and dp[i-1][j-t[ord[i-1]]] == 1 and h[ord[i-1]] <= H) {
						dp[i][j] = 1;
						tr[i][j] = j - t[ord[i-1]];
					}
				}
			}
			auto rec = [&] (int j) {
				vector<int> pe, deitado;
				for (int i = 0; i < l; ++i) pe.pb(ord[i]);
				for (int i = n; i > l; --i) {
					if (i-1 == bicho) continue;
					int prox = tr[i][j];
					if (prox == j) deitado.pb(ord[i-1]);
					else pe.pb(ord[i-1]);
					j = prox;
				}
				deitado.pb(ord[bicho]);
				reverse(begin(deitado), end(deitado));
                return vector<vector<int>>{pe, deitado};
			};
			for (int pe = max(1LL, fora); pe + h[ord[bicho]] <= W; ++pe) {
				int want = pe-fora;
				if (dp[n][want] and t[ord[bicho]] + (tudo - want) <= H) return rec(want);
			}
		}
		for (int i = l; i < r; ++i) fora += t[ord[i]];
		if (h[ord[0]] > H) break;
	}
    return {};
}

vector<vector<int>> solve(int n, int H, int W, vector<int> h, vector<int> t) {
	vector dp(n+1, vector(W+1, vector(H+1, max(H, W) + 69)));
	vector tr(n+1, vector(W+1, vector(H+1, make_tuple(-1, -1, -1, -1))));
	vector<int> ord(n); iota(begin(ord), end(ord), 0);
	sort(begin(ord), end(ord), [&] (int x, int y) {
		return h[x] > h[y];
	});
	int st = 0;
	bool pode = true;
	for (int i = 1; i <= n; ++i) {
		int id = ord[i-1];
		for (int j = 0; j <= W; ++j) {
			for (int k = 0; k <= H; ++k) {
				int opt = max(H, W) + 69, who = -1;
				// colocar o cara em pe
				if (j - t[id] >= 0 and h[id] <= H) {
					opt = dp[i-1][j - t[id]][k];
					who = 0;
				}
				// colocar o cara deitado
				if (k - t[id] >= 0) {
					if (opt > dp[i-1][j][k-t[id]]) {
						opt = dp[i-1][j][k-t[id]];
						who = 1;
					}
				}
				if (who == 0) tr[i][j][k] = {i-1, j-t[id], k, 0};
				if (who == 1) tr[i][j][k] = {i-1, j, k-t[id], 1};
				dp[i][j][k] = opt;
			}
		}
		if (st <= W and t[id] <= H and dp[i][st][t[id]] > h[id] and pode) {
			dp[i][st][t[id]] = h[id];
			tr[i][st][t[id]] = {i-1, st, 0, 1};
		}
		st += t[id];
		pode &= (h[id] <= H);
	}
	auto rec = [&] (int j, int k) {
		vector<int> pe, deitado;
		bool vai_empe = 0;
		for (int i = n; i; --i) {
			if (k == 0) vai_empe = true;
			if (vai_empe) {
				pe.pb(ord[i-1]); continue;
			}
			auto [ni, nj, nk, tipo] = tr[i][j][k];
			if (tipo == 0) pe.pb(ord[i-1]);
			else deitado.pb(ord[i-1]);
			j = nj, k = nk;
		}
		reverse(begin(deitado), end(deitado));
		return vector<vector<int>>{pe, deitado};
	};
	// j, k nao pode ser zero!!
	for (int j = 1; j <= W; ++j) {
		for (int k = 1; k <= H; ++k) {
			if (dp[n][j][k] + j <= W) {
				return rec(j, k);
			}
		}
	}
	return {};
}
int32_t main() {_
	auto print = [&] (vector<vector<int>> z) {
		if (z.empty()) {
			cout << "impossible" << endl;
			return;
		}
		cout << "upright ";
		for (auto x : z[0]) cout << x+1 << ' ';
		cout << endl;
		cout << "stacked ";
		for (auto x : z[1]) cout << x+1 << ' ';
		cout << endl;
		cout << endl;
	};
#ifndef gato
    int n, H, W; cin >> n >> H >> W;
    vector<int> h(n), t(n);
    for (int i = 0; i < n; ++i) cin >> h[i] >> t[i];
    auto ans = solve(n, H, W, h, t);
	print(ans);
#else
    int T = 1;
    while (true) {
        int n = rnd(1, 10), H = rnd(1, 1000), W = rnd(1, 1000);
        vector<int> h(n), t(n);
        for (auto& x : h) x = rnd(1, max(H, W));
        for (auto& x : t) x = rnd(1, 1000);
        auto my = solve(n, H, W, h, t);
        auto ans = oracle(n, H, W, h, t);
        auto checker = [&] () {
            if (my.empty()) return true;
            if (my[0].empty() or my[1].empty()) return false;
            for (int i = 1; i < sz(my[1]); ++i) if (h[my[1][i]] > h[my[1][i-1]]) return false;
            int tw = h[my[1][0]];
            for (auto x : my[0]) {
                if (h[x] > H) return false;
                tw += t[x];
            }
            if (tw > W) return false;
            int th = 0;
            for (auto x : my[1]) th += h[x];
            if (th > H) return false;
            vector<int> cnt(n);
            for (auto x1 : my) for (auto x2 : x1) cnt[x2]++;
            if ((*max_element(all(cnt))) > 1 or (*min_element(all(cnt)) == 0)) return false;
            return true;

        };
        auto over = [&] () {
            cout << "Wrong answer on test " << T << endl;
            cout << checker() << endl;
            cout << n << ' ' << H << ' ' << W << endl;
            for (int i = 0; i < n; ++i) cout << h[i] << ' ' <<  t[i] << endl;
            cout << "Your solution: " << endl; print(my);
            cout << "Answer: " << endl; print(ans);
            exit(0);
        };
        if ((my.empty()) != (ans.empty()) or !checker()) over();
        cout << "Accepted on test " << T++ << endl;
    }
#endif
}

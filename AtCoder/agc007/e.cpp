#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int solve(int n, vector<vector<ii>> g) {
    auto possible = [&] (int x) {
        vector<vector<ii>> S(n);
        auto dfs = [&] (auto&& self, int u) -> void {
            if (sz(g[u]) == 0) { S[u] = {{0, 0}}; return; }

            auto [L, wL] = g[u][0];
            auto [R, wR] = g[u][1];
            self(self, L), self(self, R);

            if (sz(S[L]) > sz(S[R])) swap(L, R), swap(wL, wR);

            int tl = sz(S[L]), tr = sz(S[R]);

            if (min(tl, tr) == 0) return;

            vector<ii> L_first, R_first;

            int lst = 0;

            for (int i = 0; i < tl; ++i) {
                int l = lst, r = tr-1, act = tr;
                while (l <= r) {
                    int md = l + (r-l+1)/2;
                    if (S[R][md].first <= x - wL - wR - S[L][i].second) act = md, l = md+1;
                    else r = md-1;
                }
                if (act == tr) continue;
                L_first.pb({S[L][i].first+wL, S[R][act].second+wR});
                lst = act+1;
            }

            lst = tr-1;

            for (int i = tl-1; ~i; --i) {
                int l = 0, r = lst, act = tr;
                while (l <= r) {
                    int md = l + (r-l+1)/2;
                    if (S[R][md].second <= x - wL - wR - S[L][i].first) act = md, r = md-1;
                    else l = md+1;
                }
                if (act == tr) continue;
                R_first.pb({S[R][act].first+wR, S[L][i].second+wL});
                lst = act-1;
            }
			reverse(all(R_first));

            int i = 0, j = 0;

            while (i != sz(L_first) and j != sz(R_first)) {
                if (L_first[i].first == R_first[j].first) {
                    if (L_first[i].second <= R_first[j].second) S[u].pb(L_first[i]);
                    else S[u].pb(R_first[j]);
                    i++, j++;
                } else if (L_first[i].first < R_first[j].first) S[u].pb(L_first[i++]);
                else S[u].pb(R_first[j++]);
                if (sz(S[u]) > 1 and S[u].back().second > S[u][sz(S[u])-2].second) S[u].pop_back();
            }

            //if (u == 2) {
            //    cout << "L:" << endl;
            //    for (auto [x, y] : L_first) cout << x << " " << y << endl;
            //    cout << "R:" << endl;
            //    for (auto [x, y] : R_first) cout << x << " " << y << endl;
            //}

            while (i != sz(L_first)) S[u].pb(L_first[i++]);
            while (j != sz(R_first)) S[u].pb(R_first[j++]);
        };
        dfs(dfs, 0);
		//for (int i = 0; i < n; ++i) {
		//	cout << "S[" << i+1 << "]: " << endl;
		//	for (auto [x, y] : S[i]) cout << x << " " << y << endl;
		//}
        return !S[0].empty();
    };
	//possible(22);
	//exit(0);

    int l = 0, r = n*131072, ans = r;

    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md, r = md-1;
        else l = md+1;
    }
    return ans;
}

int brute(int n, vector<vector<ii>> g) {
    vector<int> non_leaf;
    vector<int> id(n);
    for (int i = 0; i < n; ++i) if (sz(g[i])) id[i] = sz(non_leaf), non_leaf.pb(i);
    int ans = 1e18;
    for (int m = 0; m < (1 << sz(non_leaf)); ++m) {
        int cur = 0, is_first = 1;
        auto dfs = [&] (auto&& self, int u, int w, int pw) -> int {
            if (g[u].empty()) {
                if (is_first == 1) is_first = 0;
                else ckmax(cur, w);
                return pw;
            }
            auto [L, wL] = g[u][0];
            auto [R, wR] = g[u][1];
            if (m >> id[u] & 1) {
                int x = self(self, R, w+wR, wR);
                return self(self, L, x+wL, wL)+pw;
            } 
            int x = self(self, L, w+wL, wL);
            return self(self, R, x+wR, wR)+pw;
        };
        dfs(dfs, 0, 0, 0);
        ckmin(ans, cur);
    }
	//cout << "penis" << endl;
	//for (auto x : non_leaf) {
		//cout << "x = " << x+1 << ": ";
		//cout << g[x][0].first+1 << " " << g[x][1].first+1 << endl;
	//}
    return ans;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<vector<ii>> g(n);
    for (int i = 1; i < n; ++i) {
        int j, c; cin >> j >> c; --j;
        g[j].pb({i, c});
    }
    cout << solve(n, g) << endl;
    //cout << brute(n, g) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(3, 17);
        vector<vector<ii>> g(n);
        vector<ii> edg;
        for (int i = 1; i < n; ++i) {
            int j = rnd(0, i-1), c = rnd(0, n);
            edg.pb({j, c});
            g[j].pb({i, c});
        }
        bool ok = 1;
        for (auto x : g) ok &= (sz(x) == 0 or sz(x) == 2);
        if (!ok) continue;
        int my = solve(n, g), ans = brute(n, g);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto [x, y] : edg) cout << x+1 << " " << y << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

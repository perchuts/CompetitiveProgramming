#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

const int LINF = 1e18;

int d[(1<<9)][5050], lst[1<<9][5050];

int steiner(vector<int> S, const vector<vector<pair<int, int>>>& g) {
    if (S.empty()) return 0;
    assert(S.size() <= 9);
    int k = S.size();
    int n = g.size();
    for (int mask = 0; mask < (1 << k); mask++) for (int v = 0; v < n; v++) lst[mask][v] = d[mask][v], d[mask][v] = LINF;
    for (int v = 0; v < n; ++v) d[0][v] = 0;
    for (int i = 0; i < k; ++i) d[1 << i][S[i]] = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        for (int a = (mask-1) & mask; a; a = (a-1) & mask) {
            int b = mask ^ a;
            if (b > a) break;
            for (int v = 0; v < n; ++v) {
                d[mask][v] = min(d[mask][v], d[a][v] + d[b][v]);
            }
        }
		priority_queue<pair<ll, int>> pq;
		for (int v = 0; v < n; ++v) {
			if (d[mask][v] == LINF) continue;
			pq.emplace(-d[mask][v], v);
		}
		while (pq.size()) {
			auto [ndist, u] = pq.top(); pq.pop();
			if (-ndist > d[mask][u]) continue;
			for (auto [idx, w] : g[u]) if (d[mask][idx] > d[mask][u] + w) {
				d[mask][idx] = d[mask][u] + w;
				pq.emplace(-d[mask][idx], idx);

			}
		}
    }
    return d[(1<<k)-1][S[0]];
}

int32_t main() {_
    int n, m, V, k; cin >> n >> m >> V >> k;
    vector< vector<vector<pair<int, int>>> > vila(V);
    vector<int> st(V), cor(n);
    for (int i = 0; i < V; ++i) {
        int x; cin >> x;
        if (i) st[i] = st[i-1] + vila[i-1].size();
        for (int j = st[i]; j < st[i] + x; ++j) cor[j] = i;
        vila[i].resize(x);
    }
    vector<array<int, 3>> conn(V);
	int sum = 0;
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w; --u, --v;
        if (cor[u] == cor[v]) {
            int s = cor[u];
            vila[s][u-st[s]].pb({v-st[s], w});	
            vila[s][v-st[s]].pb({u-st[s], w});	
        } else {
            if (cor[v] != (cor[u] + 1) % V) swap(u, v);
            conn[cor[u]] = {u, v, w};
            sum += w;
        }
    }
    vector<int> mark(n);
    for (int i = 0; i < k; ++i) {
        int u; cin >> u; --u;
        mark[u] = 1;
    }
    // custos:
    // 0: direita + esquerda, 1 = esquerda, 2 = direita.
    vector<array<int, 4>> cost(2*V);
    vector<int> bichos;
    vector<int> imp(V);
	int opt = 1e18;
    for (int i = 0; i < V; ++i) {
        vector<int> S_base;
        int tam = vila[i].size();
        int x1 = conn[(i-1+V)%V][1];
        int x2 = conn[i][0];
        x1 -= st[i];
        x2 -= st[i];
		int k = 0;
        for (int j = st[i]; j < st[i] + tam; ++j) {
            if (mark[j]) S_base.pb(j - st[i]), k++;
        }
        if (!S_base.empty()) bichos.pb(i), imp[i] = true;
        auto S = S_base;
        cost[i][0] = steiner(S, vila[i]);
        S.pb(x1);
        cost[i][1] = steiner(S, vila[i]);
        S.pop_back();
        S.pb(x2);
        cost[i][2] = steiner(S, vila[i]);
		int eu = LINF;
		if (k) {
			for (int j = 0; j < (1 << k); ++j) eu = min(eu, lst[(1<<k)+j][x1] + d[(2 << k) - 1 - j][x2]);
		}
        S.pb(x1);
        cost[i][3] = steiner(S, vila[i]);
		sum += cost[i][3];
        cost[i+V] = cost[i];
		if (k) {
			eu -= cost[i][3], opt = min(opt, eu);
		}
    }
	int ans = sum + opt;
    if (bichos.size() == 1) ans = min(ans, cost[bichos[0]][0]);
    for (int w = 0; w < bichos.size(); ++w) {
        int st = bichos[w], en = bichos[(w+1)%bichos.size()];
        for (int __ = 0; __ < 2; ++__) {
            int vi = 1, tot = cost[en][1];
            for (int i = st; i != en; i = (i + 1) % V) {
                vi += imp[i];
                tot += conn[i][2];
                if (i == st) tot += cost[i][2];
                else tot += cost[i][3];
            }
            if (vi == bichos.size()) ans = min(ans, tot);
            swap(st, en);
        }
    }
    cout << ans << endl;
}

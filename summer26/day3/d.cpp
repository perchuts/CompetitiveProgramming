#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define endl '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

using ll = long long;

void solve() {
    vector<int> posicoes;
    struct node { int ss = 0, opt = 0, opt_nn = 0; };
    auto merge = [&] (node a, node b) {
        node c;
        c.ss = a.ss + b.ss;
        c.opt = min(a.opt, a.ss + b.opt_nn);
        c.opt_nn = min(a.opt_nn, a.ss + b.opt_nn);
        return c;
    };
    int n; cin >> n;
    int N = 5 * n + 5;
    vector<node> seg(4*N+10);
    node nulo; nulo.ss = nulo.opt = nulo.opt_nn = 1e18;
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k, bool atv = 0) -> void {
        if (l == r) { 
            seg[i].ss += k, seg[i].opt_nn += k;
            if (atv == 0) seg[i].opt = 0LL;
            else seg[i].opt = min(0LL, seg[i].ss);
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k, atv);
        else self(self, 2*i+1, md+1, r, x, k, atv);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
        if (r < x or y < l) return nulo;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return merge(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
	vector<int> x(n), v(n), c(n), t(n);
	for (int i = 0; i < n; ++i) cin >> x[i];
	for (int i = 0; i < n; ++i) cin >> c[i];
	for (int i = 0; i < n; ++i) cin >> v[i];
	for (int i = 0; i < n; ++i) cin >> t[i];
    for (int i = 0; i < n; ++i) {
        posicoes.pb(x[i]);
        posicoes.pb(x[i] - v[i]);
        posicoes.pb(x[i] - v[i] + 1);
        posicoes.pb(x[i] + v[i]);
        posicoes.pb(x[i] + v[i] - 1);
    }
    sort(begin(posicoes), end(posicoes));
    posicoes.erase(unique(begin(posicoes), end(posicoes)), end(posicoes));
    for (auto k : posicoes) cout << k << " ";
    cout << endl;
    vector<vector<pair<int, int>>> tipo1(N+1);
    vector<int> ps(N+1);
    auto get = [&] (int pos) { return lower_bound(begin(posicoes), end(posicoes), pos) - begin(posicoes); };
    int total = 0;
    for (int i = 0; i < n; ++i) {
        if (t[i] == 2) {
            total += c[i];
            int esq = get(x[i] - v[i]), dir = get(x[i] + v[i] + 1) - 1;
            ps[esq] -= c[i];
            ps[dir+1] += c[i];
            cout << "adding " << -c[i] << " to " << esq << " " << dir << endl;
            upd(upd, 1, 0, N, esq, -c[i]);
            upd(upd, 1, 0, N, dir+1, c[i]);
        } else {
            tipo1[get(x[i]-v[i]+1)].pb({get(x[i]+v[i])-1, c[i]});
        }
    }
    bool ok = 1;
    // total - dentro < soma de val
    // total - dentro - soma de val < 0
    // sou proibido de terminar o meu range em posicoes onde nao existe ninguem morrendo!
    auto go = [&] (auto&& self, int l, int r) {
        if (l >= r) return;
        // quero guardar tambem a soma de todos os segmentos de m's que comem o range inteiro...
        int md = (l + r) / 2;
        cout << "range: " << l << " " << r << endl;
		int S = 0;
        for (int i = l; i <= r; ++i) {
            cout << "i = " << i << endl;
            for (auto [end_pos, val] : tipo1[i]) {
				S -= val;
                upd(upd, 1, 0, N, end_pos+1, val, 0);
                upd(upd, 1, 0, N, end_pos, 0, 1);
                cout << "adding " << -val << " until " << end_pos << endl;
            }
            auto z = query(query, 1, 0, N, l, r);
            cout << "opt: " << z.opt << ' ' << z.opt + total + S << endl;
            if (z.opt + total + S < 0) {
				cout << "AQUI" << endl;
				ok = 0;
			}
        }
        // undo
        for (int i = l; i <= r; ++i) {
            for (auto [end_pos, val] : tipo1[i]) upd(upd, 1, 0, N, end_pos+1, -val, 0), upd(upd, 1, 0, N, end_pos, 0, 0);
        }
        // agora vai
        self(self, l, md);
        self(self, md+1, r);
    };
    go(go, 0, posicoes.size()-1);
    cout << (ok ? "Yes" : "No") << endl;
    cout << endl << endl;
}

int32_t main() {_
	int t; cin >> t;
	while (t--) solve();
}

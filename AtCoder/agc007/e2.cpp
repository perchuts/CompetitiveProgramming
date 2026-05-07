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

void solve() {
    int n; cin >> n;
    vector<vector<ii>> g(n);
    for (int i = 1; i < n; ++i) {
        int j, c; cin >> j >> c; --j;
        g[j].pb({i, c});
    }
    // S[u] = { (a, b) onde primeiro cara ta a distancia a de u, ultimo cara ta a distancia b de u}
    // S[u] = { (0, 0) } se u eh folha
    // (a1, b1), (a2, b2), ... (ak, bk)
    // (c1, d1), (c2, d2), ... (cl, dl)
    // se u tem filhos L, R, com arestas wL, wR:
    // se (a1, b1) \in S[L], (a2, b2) \in S[R]:
    // (a1+wL, b2+wR) \in S[u] se b1+a2+wL+wR <= x
    // (a2+wR, b1+wL) \in S[u] se b2+a1+wL+wR <= x
    // certo, entao agora suponha que S[L], S[R] formam conjuntos pareto.
    // como eu construo S[u] de maneira a manter essa invariante?
    // ai < a{i+1}, ci < c{i+1}
    // bi > b{i+1}  di > d{i+1}
    // ci <= x-bj-wL-wR
    // f(j) = maior ci tal que aquilo eh verdade
    // pega o primeiro j tal que f(j) >= k.
    // entao claimo que se eu for parear o de cima primeiro, vou usar j.
    // isso acontece porque vamos ter os pares: (aj+wL, dk+wR), (a{j+1}+wL, dk+wR) e aj < a{j+1}, entao eh isto.
    // desse modo, podemos brutar quem vai aparecer primeiro, e garantimos que vamos ter uma quantidade no maximo linear de pares no pareto.
    // agora, vale a pena um cara aparecer mais que uma vez? 
    // associe os indices em (ci, di) com o menor j t.q. f(j) >= i -> g(i).
    //
    //
    // a parada eh que se g([x, y]) = j, entao vale sempre a pena adicionar apenas (aj+wL, dy+wR), pois d eh decrescente!
    // entao conseguimos o seguinte: se (ai, bi) for aparecer primeiro, ele ira contribuir para apenas um par.
    // se (ai, bi) for aparecer por ultimo, ele tambem ira contribuir para apenas um par: sera o menor j tal que
    // dj <= x - wL - wR - ai (pois usaremos o cj no par, e c eh crescente)
    // note tambem que o par do i nesse caso ta <= que o par do i+1, ent da pra fazer umas micro optimizations
    // se conseguirmos encontrar com quem (ai, bi) deve ser pareado em ambos os casos, o problema esta resolvido (small to large)
    // problema nem um pouco agradavel: soh isso ja esta nlog^2. tem uma busca binaria no meio. complicado hein... talvez funcione anyway
    // em caso de (ai, bi) primeiro: compute os f(j). O(log) por cara.
    // dai, se f(j) != f(j-1), adicione (ai, bi), (c{f(j)}, d{f(j)}) em S[u].
    // temos algo codavel em O(nlog^3)
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
                if (L_first.empty() or act != lst) L_first.pb({S[L][i].first+wL, S[R][act].second+wR});
                lst = act;
            }

            lst = tr-1;

            for (int i = tl-1; ~i; --i) {
                int l = lst, r = lst, act = tr;
                while (l <= r) {
                    int md = l + (r-l+1)/2;
                    if (S[R][md].second <= x - wL - wR - S[L][i].first) act = md, r = md-1;
                    else l = md+1;
                }
                if (act == tr) continue;
                if (R_first.empty() or act != lst) R_first.pb({S[R][act].first+wR, S[L][i].second+wL});
                lst = act;
            }

            int i = 0, j = 0;

            while (i != sz(L_first) and j != sz(R_first)) {
                if (L_first[i].first == R_first[j].first) {
                    if (L_first[i].second <= R_first[j].second) S[u].pb(L_first[i]);
                    else S[u].pb(R_first[j]);
                    i++, j++;
                } else if (L_first[i].first < R_first[j].first) S[u].pb(L_first[i++]);
                else S[u].pb(R_first[j++]);
            }

            while (i != sz(L_first)) S[u].pb(L_first[i++]);
            while (j != sz(R_first)) S[u].pb(R_first[j++]);
        };

        dfs(dfs, 0);
        return !S[0].empty();
    };

    int l = 0, r = n*131072, ans = r;

    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md, r = md-1;
        else l = md+1;
    }

    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

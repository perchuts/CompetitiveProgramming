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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> solve(int n, int q, vector<int> a, vector<int> p, vector<ii> qu) {
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) g[p[i]].pb(i);
    vector<int> subt(n);
    auto pre = [&] (auto&& self, int u) -> void {
        for (auto v : g[u]) self(self, v), subt[u] += subt[v];
        subt[u]++;
    };
    pre(pre, 0);
    vector<vector<int>> g2;
    vector<int> tipo, pai, w_(n, -1), quem(n), cara;
    vector<ii> add;
    auto rake_and_compress = [&] (auto&& self, int u) -> int {
        int big = -1;
        for (auto v : g[u]) {
            if (ckmax(big, subt[v])) w_[u] = v;
        }
        // compress?
        if (big == -1) {
            int eu = sz(g2);
            g2.pb({}), tipo.pb(1), pai.pb(-1);
            quem[u] = eu;
            vector<ii> up;
            int cur = u, tam_lst = 0;
            while (true) {
                up.pb({subt[cur]-tam_lst, quem[cur]});
                tam_lst = subt[cur];
                if (cur == 0 or w_[p[cur]] != cur) break;
                cur = p[cur];
            }
            auto go = [&] (auto&& self2, int l, int r) -> int {
                if (l == r) return up[l].second;
                if (l > r) return -1;
                int S = 0;
                for (int i = l; i <= r; ++i) S += up[i].first;
                int esq = 0, dir = S;
                for (int i = l; i <= r; ++i) {
                    dir -= up[i].first;
                    if (2 * max(esq, dir) <= S) {
                        int f1 = self2(self2, l, i-1);
                        int f2 = self2(self2, i+1, r);
                        if (f1 != -1 and f2 != -1) {
                            pai[up[i].second] = pai[f1] = sz(g2);
                            g2.pb({}), tipo.pb(2), pai.pb(-1);
                            pai.back() = pai[f2] = sz(g2);
                        } else if (f1 != -1) pai[up[i].second] = pai[f1] = sz(g2);
                        else pai[up[i].second] = pai[f2] = sz(g2);
                        g2.pb({}), tipo.pb(2), pai.pb(-1);
                        return sz(g2)-1;
                    }
                    esq += up[i].first;
                }
                assert(false);
            };
            return go(go, 0, sz(up)-1);
        }
        // rake
        queue<int> filhos;
        for (auto v : g[u]) if (v != w_[u]) filhos.push(self(self, v));
        while (sz(filhos) > 1) {
            int x = filhos.front(); filhos.pop();
            int y = filhos.front(); filhos.pop();
            pai[x] = pai[y] = sz(g2);
            filhos.push(sz(g2));
            g2.pb({}), tipo.pb(0), pai.pb(-1);
        }
        int eu = sz(g2);
        if (!filhos.empty()) pai[filhos.front()] = eu;
        g2.pb({}), tipo.pb(1), pai.pb(-1);
        quem[u] = eu;
        assert(eu < sz(g2));
        return self(self, w_[u]);
    };
    int root = rake_and_compress(rake_and_compress, 0);
    cara = vector<int>(root+1, -1);
    vector<int> high(root+2, -1);
    for (int i = 0; i < n; ++i) cara[quem[i]] = i;
    assert(root == sz(g2)-1);
    vector<int> height(root+1), deg(root+1);
    //for (int i = root-1; ~i; --i) height[i] = 1 + height[pai[i]], deg[pai[i]]++;
    //cout << *max_element(all(height)) << endl;
    //exit(0);
    for (int i = 0; i < root; ++i) g2[pai[i]].pb(i);
    //cerr << "tipo: ";
    //for (auto x : tipo) cerr << x << ' ';
    //cerr << endl;
    //cerr << "quem: ";
    //for (auto x : quem) cerr << x << ' ';
    //cerr << endl;
    vector<array<int, 3>> out(root+1);
    out.pb({0, 0, 1});
    enum sexo { RAKE, NODE, COMPRESS };
    // {A, B} --- {C, D}
    // f{A, B}(x) = Ax + B
    // f{C, D}(f{A, B}(x)) = f{C, D}(Ax + B) = C*(Ax + B) + D = ACx + BC + D = {AC, BC + D}
    // attach subtree:
    // {A, B} --- {C, D} => {A*D, B}
    // update value: {A, B} --- (x) => {A, x}
    //
    auto merge = [&] (int u, int v, int w) {
        high[u] = max(high[v], high[w]);
        if (tipo[u] == RAKE) out[u][2] = out[v][2] * out[w][2] % mod;
        if (tipo[u] == COMPRESS) {
			if (high[v] < high[w]) swap(v, w);
            out[u][0] = out[v][0] * out[w][0] % mod;
            out[u][1] = (out[v][0] * out[w][1] + out[v][1]) % mod;
            out[u][2] = (out[w][2] * out[v][0] + out[v][1]) % mod;
        }
        if (tipo[u] == NODE) {
            assert(cara[u] != -1);
            ckmax(high[u], subt[cara[u]]);
            out[u][0] = out[v][2] * out[w][2] % mod;
            out[u][1] = a[cara[u]];
            out[u][2] = (out[u][0] + out[u][1]) % mod;
        }
    };
    //cerr << "edges: " << endl;
    auto build = [&] (auto&& self, int u) -> void {
        if (u > root) return;
        if (g2[u].empty()) {
			high[u] = subt[cara[u]];
            out[u][0] = 1;
            out[u][1] = out[u][2] = a[cara[u]];
            return;
        }
        if (sz(g2[u]) == 1) g2[u].pb(root+1);
        //cerr << u << " " << g2[u][0] << endl;
        //cerr << u << " " << g2[u][1] << endl;
        self(self, g2[u][0]), self(self, g2[u][1]);
        merge(u, g2[u][0], g2[u][1]); 
    };
    build(build, root);
    //cerr << "out: " << endl;
    //for (int i = 0; i <= root; ++i) cerr << out[i][0] << ' ' << out[i][1] << ' ' << out[i][2] << endl;
    //cerr << "queries: " << endl;
    vector<int> ans;
    for (auto [v, x] : qu) {
        int u = quem[v];
        out[u][1] = a[v] = x;
        out[u][2] = (x + (g2[u].empty() ? 0 : out[u][0])) % mod;
        //cerr << "new value of " << u << " is " << out[u][0] << ' ' << out[u][1] << ' ' << out[u][2] << endl;
        while (u != root) {
            u = pai[u];
            //cerr << "updating " << u << endl;
            merge(u, g2[u][0], g2[u][1]);
            //cerr << "new value: " << out[u][0] << ' ' << out[u][1] << ' ' << out[u][2] << endl;
        }
        ans.pb(out[root][2]);
    }
    return ans;
}

vector<int> brute(int n, int q, vector<int> a, vector<int> p, vector<ii> qu) {
    vector<int> ans;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) g[p[i]].pb(i);
    for (auto [x, y] : qu) {
        a[x] = y;
        auto go = [&] (auto&& self, int u) -> int {
            if (g[u].empty()) return a[u];
            int ret = 1;
            for (auto v : g[u]) ret = ret * self(self, v) % mod;
            return (ret + a[u]) % mod;
        };
        ans.pb(go(go, 0));
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, q; cin >> n >> q;
    vector<int> p(n), a(n);
    for (int i = 1; i < n; ++i) cin >> p[i], --p[i];
    for (auto& x : a) cin >> x;
    vector<ii> qu(q);
    for (auto& [x, y] : qu) cin >> x >> y, --x;
    while(t--) {
        auto ans = solve(n, q, a, p, qu);
        for (auto x : ans) cout << x << endl;
    }
#else
    int t = 1;
    int n, q = 1;
    // funny tree
    int nn = 587;
    vector<int> label(nn);
    vector<int> p = {-1}, a;
    int cur = 0;
    for (int i = 0; i < nn; ++i) {
        label[i] = cur++;
        if (i) {
            int pai = i / 2;
            p.pb(label[pai]);
        }
        for (int j = 0; j < nn; ++j) p.pb(cur-1), cur++;
    }
    a = vector<int>(p.size(), 0);
    n = sz(a);
    cout << n << endl;
    vector<ii> qu(q);
    for (auto& [x, y] : qu) x = rnd(0, n-1), y = rnd(0, 10);
    solve(n, q, a, p, qu);
    //exit(0);
    //int t = 1;
    //while (true) {
    //    int n = rnd(3, 1000), q = 5;
    //    vector<ii> qu(q);
    //    vector<int> p(n), a(n);
    //    for (auto& [x, y] : qu) x = rnd(0, n-1), y = rnd(0, 5);
    //    for (auto& x : a) x = rnd(0, 5);
    //    for (int i = 1; i < n; ++i) p[i] = rnd(0, i-1);
    //    auto my = solve(n, q, a, p, qu);
    //    auto ans = brute(n, q, a, p, qu);
    //    if (my != ans) {
    //        cout << "Wrong answer on test " << t << endl;
    //        cout << n << ' ' << q << endl;
    //        for (int i = 1; i < n; ++i) cout << p[i]+1 << ' ';
    //        cout << endl;
    //        for (auto x : a) cout << x << ' ';
    //        cout << endl;
    //        for (auto [x, y] : qu) cout << x + 1 << ' ' << y << endl;
    //        cout << "Your output: ";
    //        for (auto x : my) cout << x << ' ';
    //        cout << endl;
    //        cout << "Answer: ";
    //        for (auto x : ans) cout << x << ' ';
    //        cout << endl;
    //        exit(0);
    //    }
    //    cout << "Accepted on test " << t++ << endl;
    //}
#endif
}

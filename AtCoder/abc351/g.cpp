#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define gato

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

int solve(int n, int q, vector<int> a, vector<int> p, vector<ii> qu) {
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) g[p[i]].pb(i);
    vector<int> subt(n);
    auto pre = [&] (auto&& self, int u) -> void {
        for (auto v : g[u]) self(self, v), subt[u] += subt[v];
        subt[u]++;
    };
    pre(pre, 0);
    // first, adjust height (compress)
    // then, adjust node degree (rake)
    vector<vector<int>> g2;
    vector<int> tipo, pai, w(n, -1), quem(n);
    auto rake_and_compress = [&] (auto&& self, int u) -> int {
        int big = -1;
        for (auto v : g[u]) {
            if (ckmax(big, subt[v])) w[u] = v;
        }
        // compress?
        if (big == -1) {
            int eu = sz(g2);
            g2.pb({}), tipo.pb(1), pai.pb(-1);
            quem[u] = eu;
            priority_queue<ii, vector<ii>, greater<>> up;
            int cur = u, tam_lst = 0;
            while (true) {
                up.push({subt[cur]-tam_lst, quem[cur]});
                tam_lst = subt[cur];
                if (cur == 0 or w[p[cur]] != cur) break;
                cur = p[cur];
            }
            if (sz(up) == 1) return eu;
            g2.pb({}), tipo.pb(2), pai.pb(-1);
            while (sz(up) > 1) {
                auto [w1, x] = up.top(); up.pop();
                auto [w2, y] = up.top(); up.pop();
                pai[x] = pai[y] = sz(g2)-1;
                up.push({w1+w2, sz(g2)-1});
                g2.pb({}), tipo.pb(2), pai.pb(-1);
            }
            g2.pop_back(), tipo.pop_back(), pai.pop_back();
            return sz(g2)-1;
        }
        // rake
        queue<int> filhos;
        for (auto v : g[u]) if (v != w[u]) filhos.push(self(self, v));
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
        return self(self, w[u]);
    };
    int root = rake_and_compress(rake_and_compress, 0);
    assert(root == sz(g2)-1);
    //cout << w[0] << endl;
    //for (int i = 0; i <= root; ++i) cout << pai[i] << ' ' << i << endl;
    //for (auto x : quem) cout << x << ' ';
    //cout << endl;
    //for (auto x : tipo) cout << x << ' ';
    //cout << endl;
    //while (q--) {
    //    int v, x; cin >> v >> x; --v;
    //}
    vector<int> height(root+1);
    for (int i = root-1; ~i; --i) height[i] = 1 + height[pai[i]];
    return *max_element(all(height));
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
    while(t--) solve(n, q, a, p, qu);
#else
    int t = 1;
    int n = 200000, q = 1;
    vector<int> p(n), a(n);
    
    vector<ii> qu(q);
    for (auto& [x, y] : qu) x = rnd(0, n-1), y = rnd(0, 10);
    cout << solve(n, q, a, p, qu) << endl;
    //while (true) {
    //    int my = solve(), ans = brute();
    //    if (my != ans) {
    //        cout << "Wrong answer on test " << t << endl;
    //        cout << "Your output: " << my << endl;
    //        cout << "Answer: " << ans << endl;
    //        exit(0);
    //    }
    //    cout << "Accepted on test " << t++ << endl;
    //}
#endif
}

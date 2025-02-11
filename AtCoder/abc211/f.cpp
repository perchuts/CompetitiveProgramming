#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 1e5+200;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int seg[4*maxn], lz[4*maxn];

void push(int i, int l, int r) {
    seg[i] += lz[i];
    if (l != r) lz[2*i] += lz[i], lz[2*i+1] += lz[i];
    lz[i] = 0;
}
void upd(int i, int l, int r, int x, int y, int k) {
    push(i, l, r);
    if (x <= l and r <= y) {
        lz[i] += k;
        push(i, l, r);
        return;
    }
    if (r < x or y < l) return;
    int md = (l+r)/2;
    upd(2*i, l, md, x, y, k), upd(2*i+1, md+1, r, x, y, k);
}
int query(int i, int l, int r, int x) {
    push(i, l, r);
    if (l == r) return seg[i];
    int md = (l+r)/2;
    if (x <= md) return query(2*i, l, md, x);
    return query(2*i+1, md+1, r, x);
}
void solve(){
    int n; cin >> n;
    vector<vector<ii>> poly(n);
    for (int i = 0; i < n; ++i) {
        int m; cin >> m;
        poly[i].resize(m);
        for (auto& [x, y] : poly[i]) cin >> x >> y;
    }
    int q; cin >> q;
    vector<ii> qu(q);
    for (auto& [x, y] : qu) cin >> x >> y;
    // N = 1
    // N = 2?
    // vou inserir dois pontos (l, r+1) em estrutura(i)
    // quero perguntar a soma de prefixo em 1, x pra toda estrutura e somar tudo
    // alternativamente, vou olhar pros pontos (x) onde se localizam as queries
    // a cada momento q eu insiro uma retinha (l, r), vou ter varios pontos aqui dentro ne
    // a resposta desses caras pode mudar?
    //
    vector<tuple<int, int, int, int>> ev;
    for (int i = 0; i < n; ++i) {
        int m = poly[i].size();
        for (int j = 0; j < m; ++j) {
            auto [x1, y1] = poly[i][j];
            auto [x2, y2] = poly[i][(j+1)%m];
            if (y1 != y2) continue;
            ev.pb({y1, min(x1, x2), max(x1, x2)-1, i});
        }
    }
    int id = 0;
    for (auto [x, y] : qu) ev.pb({y+1, -inf, x, id++}); 
    sort(all(ev), greater<>());
    vector<int> ans(q), sexo(n);
    vector<ord_set<ii>> foi(n);
    // ray casting seems pretty hopeless on this problem...
    int N = 100005;
    for (auto [y, a, b, c] : ev) {
        if (a == -inf) {
            // query
            ans[c] = query(1, 0, N, b);
        } else {
            // update
            int qnt = foi[c].order_of_key(make_pair(a, 1e9));
            upd(1, 0, N, a, b, (qnt%2?-1:1));
            foi[c].insert(make_pair(a, sexo[c]++));
            foi[c].insert(make_pair(b+1, sexo[c]++));
        }
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

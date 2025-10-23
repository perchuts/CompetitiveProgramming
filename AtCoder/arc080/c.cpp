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
    vector<int> p(n), onde(n);
    for (int i = 0; i < n; ++i) cin >> p[i], --p[i], onde[p[i]] = i;
    struct node {
        ii oe = {inf, inf};
        ii eo = {inf, inf};
        int o = inf, e = inf;
    } nulo;
    vector<node> seg(4*n);
    auto merge = [&] (node a, node b) {
        node res;
        res.o = min(a.o, b.o);
        res.e = min(a.e, b.e);
        res.oe = min({a.oe, b.oe, pair(a.o, b.e)});
        res.eo = min({a.eo, b.eo, pair(a.e, b.o)});
        return res;
    };
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) { 
            if (l&1) seg[i].o = p[l];
            else seg[i].e = p[l];
            return;
        };
        int md = (l+r) / 2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
        if (x <= l and r <= y) return seg[i];
        if (r < x or y < l) return nulo;
        int md = (l+r)/2;
        return merge(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    set<array<int, 4>> sexo;
    build(build, 1, 0, n-1);
    auto add = [&] (int l, int r) {
        if (l >= r) return;
        auto qq = query(query, 1, 0, n-1, l, r);
        if (l&1) sexo.insert({qq.oe.first, qq.oe.second, l, r});
        else sexo.insert({qq.eo.first, qq.eo.second, l, r});
    };
    add(0, n-1);
    while (!sexo.empty()) {
        auto opt = *begin(sexo);
        cout << opt[0]+1 << ' ' << opt[1]+1 << ' ';
        sexo.erase(opt);
        int i = onde[opt[0]], j = onde[opt[1]];
        int l = opt[2], r = opt[3];
        add(l, i-1);
        add(i+1, j-1);
        add(j+1, r);
    }
    cout << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

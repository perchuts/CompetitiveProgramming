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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
    int n; cin >> n;
    vector<int> p(n), c(n), quem(n+1);
    for (auto& x : p) cin >> x;
    for (int i = 0; i < n; ++i) quem[p[i]] = i;
    for (auto& x : c) cin >> x, --x;
    vector<int> resto(n+1), par(n), lvl(n), comp(n), qnt_comps(n);
    set<int> vivos;
    for (int i = 0; i < n; ++i) vivos.insert(i), par[i] = i, comp[i] = 1;
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    auto unite = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        qnt_comps[c[u]]--;
        comp[u] += comp[v];
        if (lvl[u] == lvl[v]) lvl[u]++;
    };
    for (int i = 0; i < n; ++i) resto[c[i]]++, qnt_comps[c[i]]++;
    for (int i = 0; i < n-1; ++i) {
        if (c[i] == c[i+1]) unite(i, i+1);
    }
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        // vou matar uma pessoa dessa cor!
        int j = quem[i];
        ans = ans * (comp[findp(findp, j)]) % mod;
        //cout << resto[c[j]] - qnt_comps[c[j]] + 1 << endl;
        //cout << j << ' ' << comp[findp(findp, j)] << ' ' << resto[c[j]] << ' ' << qnt_comps[c[j]] << endl;
        auto it = vivos.lower_bound(j);
        if (it != begin(vivos) and it != prev(end(vivos))) {
            auto it2 = prev(it);
            auto it3 = next(it);
            if (c[*it2] == c[*it3]) unite(*it2, *it3);
        }
        comp[findp(findp, j)]--;
        if (comp[findp(findp, j)] == 0) qnt_comps[c[j]]--;
        resto[c[j]]--;
        vivos.erase(j);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}

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

void solve(){
    int n; cin >> n;
    vector<int> a(n);
    vector<vector<int>> occ(n+1);
    for (auto& x : a) cin >> x;
    for (int i = 0; i < n; ++i) occ[a[i]].pb(i);
    // abrir todo mundo, depois fechar todo mundo
    // entao a ordem em que eu faco os abres e fechas nao importa
    // sera q eh busca binarizavel? - vai ser demais!!
    auto possible = [&] (int x) {
        set<int> sexo;
        int tot = 0, big = 0;
        for (int i = n; i > x; --i) {
            for (auto j : occ[i]) sexo.insert(j);
        }
        for (int i = x; i >= 1; --i) {
            for (auto j : occ[i]) sexo.insert(j);
            if (sexo.empty()) return pair(0LL, 0LL);
            auto eu = *begin(sexo);
            tot -= eu;
            ckmax(big, eu);
            sexo.erase(eu);
        }
        sexo.clear();
        for (int i = n; i > x; --i) {
            for (auto j : occ[i]) if (j > big) sexo.insert(j);
        }
        for (int i = x; i >= 1; --i) {
            for (auto j : occ[i]) if (j > big) sexo.insert(j);
            if (sexo.empty()) return pair(0LL, 0LL);
            auto eu = *prev(end(sexo));
            tot += eu;
            sexo.erase(eu);
        }
        return pair(1LL, tot);
    };
    int l = 1, r = n, ans = 0;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        auto [can, val] = possible(md);
        if (can) l = md + 1, ans = val;
        else r = md - 1;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}

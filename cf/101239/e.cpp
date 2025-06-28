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
    vector<string> v(n+1);
    for (auto& x : v) cin >> x;
    vector<int> ord(n+1); iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) { return sz(v[x]) > sz(v[y]); });
    auto faz_o_l = [] {
        cout << "impossible" << endl;
        exit(0);
    };
    if (ord[0]) faz_o_l();
    vector<vector<vector<int>>> go(n+1);
    vector<int> id(200);
    id['A'] = 0;
    id['C'] = 1;
    id['M'] = 2;
    for (int i = 0; i <= n; ++i) {
        int m = sz(v[ord[i]]);
        go[i] = vector<vector<int>>(m+1, vector<int>(3, -1));
        for (int j = m-1; ~j; --j) go[i][j] = go[i][j+1], go[i][j][id[v[ord[i]][j]]] = j;
    }
    vector<vector<int>> sol(2);
    auto subseq = [&] (int i, int j) {
        int cur = 0;
        for (auto c : v[ord[i]]) {
            cur = go[j][cur][id[c]] + 1;
            if (!cur) return false;
        }
        return true;
    };
    sol[0].pb(0), sol[1].pb(0);
    int last_push = 0;
    for (int i = 1; i <= n; ++i) {
        int a = subseq(i, sol[0].back());
        int b = subseq(i, sol[1].back());
        if (!max(a, b)) faz_o_l();
        if (last_push != i-1) {
            int c = subseq(i, i-1);
            if (!c) {
                sol[a ^ 1].pb(i);
                for (int j = last_push + 1; j < i; ++j) sol[a].pb(j);
                last_push = i;
            } 
        } else if (!min(a, b)) last_push = i, sol[a ^ 1].pb(i);
    }
    for (int i = last_push + 1; i <= n; ++i) sol[0].pb(i);
    cout << sz(sol[0]) - 1 << ' ' << sz(sol[1]) - 1 << endl;
    for (int i = 0; i < 2; ++i) {
        reverse(all(sol[i])); sol[i].pop_back();
        for (auto j : sol[i]) cout << v[ord[j]] << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

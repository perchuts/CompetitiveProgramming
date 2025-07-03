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
    int n, m; cin >> n >> m;
    vector<int> x(m); cin >> x[0];
    vector<array<int, 4>> edg(m);
    vector<vector<ii>> sexo(n);
    for (int i = 0; i < m; ++i) for (int j = 0; j < 4; ++j) cin >> edg[i][j];
    for (int i = 0; i < m; ++i) edg[i][0]--, edg[i][1]--, sexo[edg[i][0]].pb({edg[i][2], i});
    for (int i = 0; i < n; ++i) sort(all(sexo[i]));
    vector<int> ord(m), tim(n); iota(all(ord), 0); 
    sort(all(ord), [&] (int a, int b) { 
        if (edg[a][2] == edg[b][2]) return a < b;
        return edg[a][2] < edg[b][2]; 
    });
    for (auto id : ord) {
        int u = edg[id][0], v = edg[id][1], i = tim[u]++, d = edg[id][2]+x[id];
        if (i+1 < sz(sexo[u]) and id) {
            int id2 = sexo[u][i+1].second;
            ckmax(x[id2], d - edg[id2][2]);
        }
        int j = lower_bound(all(sexo[v]), pair<int,int>(edg[id][3], 0LL)) - begin(sexo[v]);
        if (j != sz(sexo[v])) {
            int id2 = sexo[v][j].second;
            ckmax(x[id2], x[id] + edg[id][3] - edg[id2][2]);
        }
    }
    for (int i = 1; i < m; ++i) cout << x[i] << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}


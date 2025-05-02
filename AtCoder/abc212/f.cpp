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
    int n, m, q; cin >> n >> m >> q;
    vector<int> ini(m+1), fim(m);
    vector<vector<ii>> tt(n);
    vector<ii> edg(m);
    ini[m] = 1e18;
    for (int i = 0; i < m; ++i) {
        cin >> edg[i].first >> edg[i].second >> ini[i] >> fim[i];
        --edg[i].first, --edg[i].second;
        tt[edg[i].first].pb({ini[i], i});
    }
    for (int i = 0; i < n; ++i) tt[i].pb({1e18, m}), sort(all(tt[i]));
    vector<vector<int>> sexo(m+1, vector<int>(17));
    for (int i = 0; i < m; ++i) {
        int j = lower_bound(all(tt[edg[i].second]), make_pair(fim[i], 0LL)) - begin(tt[edg[i].second]);
        sexo[i][0] = tt[edg[i].second][j].second;
    }
    sexo[m][0] = m;
    for (int i = 1; i < 17; ++i) {
         sexo[m][i] = m;
        for (int j = 0; j < m; ++j) sexo[j][i] = sexo[sexo[j][i-1]][i-1];
    }
    while (q--) { 
        int x, y, z; cin >> x >> y >> z;
        swap(x, y);
        --x;
        int j = lower_bound(all(tt[x]), make_pair(y, 0LL)) - begin(tt[x]);
        j = tt[x][j].second;
        if (j == m) {
            cout << x+1 << endl;
            continue;
        }
        for (int k = 16; ~k; --k) {
            int prox = sexo[j][k];
            if (prox != m and ini[prox] < z) j = prox;
        }
        if (fim[j] >= z and ini[j] < z) cout << edg[j].first + 1 << ' ' << edg[j].second + 1 << endl;
        else if (fim[j] < z) cout << edg[j].second+1 << endl;
        else cout << edg[j].first+1 << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

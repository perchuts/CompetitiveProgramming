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
// Centroid decomposition
//
// decomp(0, k) computa numero de caminhos com 'k' arestas
// Mudar depois do comentario
//
// O(n log(n))
const int MAX = maxn;
vector<int> g[MAX];
int sz[MAX], rem[MAX];
int pref[maxn][2], caras[maxn][2];
int val[maxn], ans;
int CC = 0;
void dfs(int& tam, int i, int l, int d, int type) {
    tam++;
    pref[i][0] = pref[i][1] = 0;
    ckmin(pref[i][0], d), ckmin(pref[i][1], -d);
    if (l != -1) ckmin(pref[i][0], pref[l][0]), ckmin(pref[i][1], pref[l][1]);
    if (type == 1) {
        for (int j = 0; j < 2; ++j) {
            int min_subindo = d + pref[i][j^1];
            //cout << "i = " << i << " j = " << j << " min_s = " << min_subindo << ' ' << d << ' ' << pref[i][j] << endl;
            if (min_subindo >= 0) {
                ans += caras[d][j^1];
                //cout << "sum: " << "i = " << i << " j = " << j << " d = " << d << " add = " << caras[d][j^1] << " min_subindo = " << d + pref[i][j] << endl;
            }
            d *= -1;
        }
    } else {
        for (int j = 0; j < 2; ++j) {
            int min_subindo = d + pref[i][j^1];
            if (min_subindo >= 0) caras[d][j]++;
            d *= -1;
        }
        //cout << i << ": ";
        //cout << pref[i][0] << ' ' << pref[i][1] << endl;
    }
	for (int j : g[i]) if (j != l and !rem[j]) {
        dfs(tam, j, i, d+val[j], type);
    }
}

int dfs_sz(int i, int l=-1) {
	sz[i] = 1;
	for (int j : g[i]) if (j != l and !rem[j]) sz[i] += dfs_sz(j, i);
	return sz[i];
}

int centroid(int i, int l, int size) {
	for (int j : g[i]) if (j != l and !rem[j] and sz[j] > size / 2)
		return centroid(j, i, size);
	return i;
}
void decomp(int i) {
	int c = centroid(i, i, dfs_sz(i));
    //int c = i;
    //cout << "centroid = " << c << endl;
	rem[c] = 1;
    CC = c;
    int mx = 0;
    pref[c][0] = pref[c][1] = 0;
    ckmin(pref[c][0], val[c]), ckmin(pref[c][1], -val[c]);
	for (int j : g[c]) if (!rem[j]) {
        int cur_t = 0;
		dfs(cur_t, j, c, val[j]+val[c], 1);
        ckmax(mx, cur_t);
        dfs(cur_t, j, -1, val[j], -1);
	}
    if (val[c] == 1) ans += caras[1][1];
    else ans += caras[1][0];
    //cout << "Ans = " << ans << endl;
    for (int i = 0; i <= mx+5; ++i) caras[i][0] = caras[i][1] = 0;
	for (int j : g[c]) if (!rem[j]) decomp(j);
}

void solve(){
    int n; cin >> n;
    string s; cin >> s;
    for (int i = 0; i < n; ++i) val[i] = (s[i] == '(' ? 1 : -1);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    decomp(0);
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

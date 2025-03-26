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
    int m; cin >> m;
    vector<string> words(m);
    vector<int> id(300);
    int n = 52*52*52;
    vector<vector<int>> gi(n);
    vector<int> deg(n), status(n, -1);
    for (int i = 'a'; i <= 'z'; ++i) id[i] = i - 'a';
    for (int i = 'A'; i <= 'Z'; ++i) id[i] = i - 'A' + 26;
    for (auto& x : words) {
        cin >> x;
        int ss = sz(x);
        int in = id[x[0]] + 52 * id[x[1]] + 52 * 52 * id[x[2]];
        int out = id[x[ss-3]] + 52 * id[x[ss-2]] + 52 * 52 * id[x[ss-1]];
        gi[out].pb(in), deg[in]++;
    }
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (!deg[i]) q.push(i), status[i] = 0;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : gi[u]) {
            if (status[u] == 0) {
                if (status[v] != -1) assert(status[v] == 1);
                else status[v] = 1, q.push(v);
            } else {
                deg[v]--;
                if (status[v] == -1 and deg[v] == 0) status[v] = 0, q.push(v);
            }
        }
    }
    for (auto x : words) {
        int ss = sz(x);
        int out = id[x[ss-3]] + 52 * id[x[ss-2]] + 52 * 52 * id[x[ss-1]];
        if (status[out] == -1) cout << "Draw" << endl;
        if (status[out] == 1) cout << "Aoki" << endl;
        if (status[out] == 0) cout << "Takahashi" << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

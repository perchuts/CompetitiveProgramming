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
    string s, t; cin >> s >> t;
    vector<int> par(26, -1), aponta(26);
    for (int i = 0; i < n; ++i) {
        if (par[s[i]-'a'] != -1 and par[s[i]-'a'] != t[i]-'a') {
            cout << -1 << endl;
            exit(0);
        }
        par[s[i]-'a'] = t[i]-'a';
    }
    int ans = 0, existe = 0, nice = 0;
    vector<int> deg(26);
    for (int i = 0; i < 26; ++i) {
        if (par[i] != -1) {
            existe++;
            deg[par[i]]++;
        } else nice = 1;
    }
    queue<int> q;
    vector<int> vis(26);
    for (int i = 0; i < 26; ++i) {
        if (deg[i] == 0 and par[i] != -1) q.push(i);
        if (deg[i] == 0) nice = 1;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (par[u] == -1) continue; 
        vis[u] = 1;
        deg[par[u]]--;
        aponta[par[u]] = 1;
        ans++;
        if (deg[par[u]] == 0) q.push(par[u]);
    }
    for (int i = 0; i < 26; ++i) {
        if (vis[i] or par[i] == -1) continue;
        if (par[i] == i) continue;
        if (!nice) {
            cout << -1 << endl;
            exit(0);
        }
        int cur = i, aaa = 0;
        while (vis[cur] == 0) vis[cur] = 1, ans++ , aaa |= aponta[cur], cur = par[cur];
        if (aaa == 0) ans++;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}


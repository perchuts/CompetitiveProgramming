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

void solve() {
    int n; cin >> n;
    vector<int> p(n+1);
    vector<int> val(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        if (i >= p[i]) val[i-p[i]]++;
    }
    vector<int> pw(n+1, 1);
    for (int i = 1; i <= n; ++i) pw[i] = 2 * pw[i-1] % mod;
    int ans = 0;
    for (int d = 0; d < n; ++d) {
        vector<int> deg(n+2), vis(n+2), seta(n+2);
        for (int i = 1; i <= n; ++i) {
            seta[i] = min(n+1, p[i] + d);
            deg[seta[i]]++;
        }
        seta[n+1] = n+1;
        queue<int> q;
        for (int i = 1; i <= n+1; ++i) {
            if (!deg[i]) q.push(i);
        }
        while (!q.empty()) {
            int i = q.front(); q.pop();
            vis[i] = 1;
            deg[seta[i]]--;
            if (deg[seta[i]] == 0) q.push(seta[i]);
        }
        int ct = 0;
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) continue;
            ct++;
            int cur = i;
            while (!vis[cur]) vis[cur] = 1, cur = seta[cur];
        }
        ans = (ans + pw[ct] - 1 + mod) % mod;
    }
    cout << ans << endl;


    // se eu shiftar os indices em x unidades, farei o W
    // ou seja, i - p[i] = j - p[j]
    // 
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

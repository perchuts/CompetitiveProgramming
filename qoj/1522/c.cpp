#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

inline void add(int& x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

inline void sub(int& x, int y) {
    x -= y;
    if (x < 0) x += mod;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<array<int, 2>> la(n+1), lb(m+1);
    for (int i = 1; i <= n; ++i) cin >> la[i][0] >> la[i][1];
    for (int i = 1; i <= m; ++i) cin >> lb[i][0] >> lb[i][1];
    const int V = 500;
    vector<vector<int>> lr(m+1, vector<int>(2*V+1)), nlr = lr;
    for (int i = 0; i <= V; ++i) lr[0][i+V] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            // apply prefix sum
            // + A - B
            for (int k = -V; k <= V; ++k) {
                nlr[j][k+V] = 0;
                // use A
                if (i) {
                    int l = k - la[i][1], r = k - la[i][0];
                    if (-V <= r and l <= 0) {
                        ckmax(l, -V);
                        ckmin(r, 0);
                        int z = lr[j][r+V]; 
                        if (l != -V) sub(z, lr[j][l-1+V]);
                        add(nlr[j][k+V], z);
                    }
                }
                // use B
                if (j) {
                    int l = k + lb[j][0], r = k + lb[j][1];
                    if (r > 0 and l <= V) {
                        ckmax(l, 1);
                        ckmin(r, V);
                        int z = nlr[j-1][r+V];
                        sub(z, nlr[j-1][l-1+V]);
                        add(nlr[j][k+V], z);
                    }
                }
                if (k != -V) add(nlr[j][k+V], nlr[j][k-1+V]);
            }
            if (min(i, j)) cout << (nlr[j][V]-nlr[j][V-1]+mod)%mod << " \n"[j==m];
        }
        swap(nlr, lr);
    }
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

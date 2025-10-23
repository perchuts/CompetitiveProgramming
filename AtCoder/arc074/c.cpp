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

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<ii>> restr(n+1);
    for (int i = 0; i < m; ++i) {
        int x, y, z; cin >> x >> y >> z;
        if (y == 1 and z != 1) {
            cout << 0 << endl;
            exit(0);
        }
        restr[y].pb({x, z});
    }
    // dp[i][j][k] = outra cor sem ser essa acontceu aqui, outra cor sem ser essa aconteceu ali
    vector dp(n+1, vector(n+1, vector(3, 0LL)));
    dp[0][0][0] = dp[0][0][1] = dp[0][0][2] = 1;
    auto add = [&] (int& x, int y) { 
        x += y;
        if (x >= mod) x -= mod;
    };
    for (int i = 2; i <= n; ++i) {
        // dont change last position
        vector ndp = dp;
        // RGB (in this order)
        for (int j = 0; j < i; ++j) {
            for (int k = 0; k < i; ++k) {
                // change last position!
                // RGB
                // [G][B][0]
                // [B][R][1]
                // [R][G][2]
                // six options: 
                // 0-> 1
                add(ndp[k][i-1][1], dp[j][k][0]);
                // 1-> 0
                add(ndp[i-1][j][0], dp[j][k][1]);
                // 1-> 2
                add(ndp[k][i-1][2], dp[j][k][1]);
                // 2-> 1
                add(ndp[i-1][j][1], dp[j][k][2]);
                // 0-> 2
                add(ndp[i-1][j][2], dp[j][k][0]);
                // 2-> 0
                add(ndp[k][i-1][0], dp[j][k][2]);
            }
        }
        // agora tirar os lixos

        for (int j = 0; j < i; ++j) {
            for (int k = 0; k < i; ++k) {
                bool ok = true;
                for (auto [l, x] : restr[i]) {
                    if (x == 1) {
                        if (max(j, k) >= l) ok = false;
                    } else if (x == 2) {
                        // vou ter 3
                        if (l <= min(j, k)) ok = false;
                        // vou ter 1
                        if (max(j, k) < l) ok = false;
                    } else {
                        // vou ter 2
                        if (min(j, k) < l) ok = false;
                    }
                    if (!ok) break;
                }
                if (!ok) ndp[j][k][0] = ndp[j][k][1] = ndp[j][k][2] = 0;
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) for (int w = 0; w < 3; ++w) add(ans, dp[i][j][w]);
    cout << ans << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

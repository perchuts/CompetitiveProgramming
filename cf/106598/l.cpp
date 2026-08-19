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

    int n; cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x, x++;
    // 1 5 3 7 2 6 4
    // 1       2   4

    vector esq_can(n+1, vector(n+1, vector(2, 0)));
    auto dir_can = esq_can;

    vector<int> bichos(n), esq(n+2), dir(n+2);

    for (int l = n; l >= 1; --l) {
        for (int r = l; r <= n; ++r) {
            int j = 0;
            for (int i = 0; i < n; ++i) {
                if (l <= v[i] and v[i] <= r) bichos[j++] = v[i];
            }
            for (int i = 0; i < j; ++i) {
                if (bichos[i] == l) {
                    if (i == 0) esq_can[l][r][0] = 0;
                    else esq_can[l][r][0] = bichos[i-1];

                    if (i == j-1) dir_can[l][r][0] = n+1;
                    else dir_can[l][r][0] = bichos[i+1];
                }
                if (bichos[i] == r) {
                    if (i == 0) esq_can[l][r][1] = 0;
                    else esq_can[l][r][1] = bichos[i-1];

                    if (i == j-1) dir_can[l][r][1] = n+1;
                    else dir_can[l][r][1] = bichos[i+1];
                }
            }
        }
    }

    vector help(n+1, vector(n+2, vector(n+2, 0)));
    for (int k = 1; k <= n; ++k) {
        for (int l = k; l >= 1; --l) {
            if (l == k) {
                dir[0] = n+1;
                esq[n+1] = 0;
            } else {
                dir[0] = l, esq[l] = 0;
                dir[l] = n+1, esq[n+1] = l;
            }
            for (int r = l+1; r <= n; ++r) {
                if (r == k) continue;
                auto undo = [&] (int who) {
                    if (who == 0 or dir[who] == n+1) return;
                    help[k][l][r] -= ((who < k) != (dir[who] < k));
                };
                auto redo = [&] (int who) {
                    if (who == 0 or dir[who] == n+1) return;
                    help[k][l][r] += ((who < k) != (dir[who] < k));
                };
                int c = 1;
                int px, py;
                help[k][l][r] = help[k][l][r-1], px = esq_can[l][r][c], py = dir_can[l][r][c];
                int z = r;
                if (px != k) {
                    undo(px);
                    int dd = dir[px];
                    esq[z] = px, dir[px] = z;
                    dir[z] = dd, esq[dd] = z;
                } else {
                    int ant = esq[py];
                    undo(ant);
                    esq[z] = ant, dir[ant] = z;
                    dir[z] = py, esq[py] = z;
                }
                redo(z);
                redo(esq[z]);
            }
        }
    }

    vector<vector<int>> dp(n+2, vector<int>(n+2));

    for (int l = n; l >= 1; --l) {
        for (int r = l; r <= n; ++r) {
            for (int k = l; k <= r; ++k) {
                ckmax(dp[l][r], dp[l][k-1] + dp[k+1][r] + help[k][l][r]);
            }
        }
    }

    cout << dp[1][n] << endl;
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

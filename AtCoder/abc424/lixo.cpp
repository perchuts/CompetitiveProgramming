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

array<int8_t, 3> tr[101][101][101][101];

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<ii> sexo(m);
    vector dp(n+1, vector(n+1, vector(m+1, -1e18)));
    for (auto& [x, y] : sexo) cin >> x >> y;
    sort(rbegin(sexo), rend(sexo));
    sort(rbegin(a), rend(a));
    a.pb(-10);
    dp[0][0][a[0]] = 0;
    for (auto x : a) cout << x << ' ';
    cout << endl;
    for (int i = 0; i <= n; ++i) {
        // onde que esta o primeiro item nao usado
        for (int j = i; j <= n; ++j) {
            // quanto que o a[0] tem
            for (int k = 0; k <= n; ++k) {
                // dp[x][i][j][k] = escolhi ate o item x, estou olhando pro i, a barreira atual eh o j, o a[0] tem k.
                // qual era o estado anterior a esse? acho que eh mais facil fazer a transicao reversa, ou seja, posso me manter aqui
                // ou usar e ir pra outro lugar.
                tr[i][j][k][0][0] = i;
                tr[i][j][k][0][1] = j;
                tr[i][j][k][0][2] = k;
                int c0 = i, c1 = j, c2 = k;
                if (i != j and a[i] <= k) c2 = -1;
                if (i == j) {
                    if (i == 0 and c2 != a[0]) c2 = -1;
                    if (i != 0 and a[i-1] <= k) c2 = -1;
                }
                for (int use = 1; use <= n; ++use) {
                    if (c2 != -1) {
                        if (c0 == c1) {
                            if (a[c1] == c2+1) c1++, c0++;
                            else c2--, c1 = 1;
                        } else c0++;
                    }
                    tr[i][j][k][use][0] = c0;
                    tr[i][j][k][use][1] = c1;
                    tr[i][j][k][use][2] = c2;
                }
            }
        }
    }
    for (auto [bx, cx] : sexo) {
        auto ndp = dp;
        // onde que o ponteiro do guloso vai estar
        for (int i = 0; i <= n; ++i) {
            // onde que esta o primeiro item nao usado
            for (int j = i; j <= n; ++j) {
                // quanto que o a[0] tem
                for (int k = 0; k <= n; ++k) {
                    int c0 = tr[i][j][k][bx][0];
                    int c1 = tr[i][j][k][bx][1];
                    int c2 = tr[i][j][k][bx][2];
                    if (c2 != -1) {
                        cout << i << ' ' << j << ' ' << k << ' ' << bx << ": ";
                        cout << c0 << ' ' << c1 << ' ' << c2 << endl << flush;
                        ckmax(ndp[c0][c1][c2], dp[i][j][k] + cx);
                    }
                    // dp[x][i][j][k] = escolhi ate o item x, estou olhando pro i, a barreira atual eh o j, o a[0] tem k.
                    // qual era o estado anterior a esse? acho que eh mais facil fazer a transicao reversa, ou seja, posso me manter aqui
                    // ou usar e ir pra outro lugar.
                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) for (int j = i; j <= n; ++j) for (int k = 0; k <= n; ++k) ckmax(ans, dp[i][j][k]);
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

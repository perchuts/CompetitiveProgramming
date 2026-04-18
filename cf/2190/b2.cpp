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
    string s; cin >> s;
    auto add = [&] (int& x, int y) {
        x += y;
        if (x >= mod) x -= mod;
    };
    vector dp(n+1, vector(n+1, vector(4, 0LL)));
    dp[0][0][0] = 1;
    for (auto c : s) {
        // posso ignorar essa letra!
        vector ndp = dp;
        for (int score = 0; score <= n; ++score) {
            for (int tam = 1; tam <= n; ++tam) {
                // vou usar essa letra
                if (c == '(') {
                    if (!score) continue;
                    // tava no estagio 0 antes
                    add(ndp[score][tam][0], dp[score-1][tam-1][0]);
                    // tava no estagio 1 antes
                    add(ndp[score][tam][2], dp[score-1][tam-1][1]);
                    // tava no estagio 2 antes
                    add(ndp[score][tam][3], dp[score-1][tam-1][2]);
                    // tava no estagio 3 antes
                    add(ndp[score][tam][3], dp[score-1][tam-1][3]);
                } else {
                    if (score == n) continue;
                    // tava no estagio 0 antes
                    add(ndp[score][tam][1], dp[score+1][tam-1][0]);
                    // tava no estagio 1 antes
                    add(ndp[score][tam][1], dp[score+1][tam-1][1]);
                    // tava no estagio 2 antes
                    add(ndp[score][tam][2], dp[score+1][tam-1][2]);
                    // tava no estagio 3 antes
                    add(ndp[score][tam][3], dp[score+1][tam-1][3]);

                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int tam = 2; tam <= n; ++tam) {
        add(ans, dp[0][tam][3] * (tam-2) % mod);
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
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

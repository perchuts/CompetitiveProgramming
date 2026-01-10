#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // if i use B[n] at 1, i'm kinda screwed.
    // So we can do three iterations: Ignore B[n] at 1, use B[n] at 1 but not at N, use B[n] at both
    // each one of them is easy to handle. -> bruh
    auto S = [] (int x) {
        int ret = x * (x + 1) / 2;
        return ret % mod;
    };
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) { 
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    int inv6 = fexp(6, mod-2);
    auto S2 = [inv6] (int x) { return (2*x+1) * x % mod * (x+1) % mod * inv6 % mod; };
    auto add = [&] (int& x, int y) { x += y; x %= mod;  };
    // ignore B[n] at 1. i dont know B[n] up to the last point. must determine 1,2,3,4,...N
    // 0: use A[i]
    // 1: use B[i] 
    // 2: use B[i-1] only at me
    // 3: use B[i-1] at both
    // duas coisas tem que ser consideradas: se o B nao entra na multiplicacao, tenho que levar em conta todos os valores que eu ignorei ele msm assim
    // isso torna as transicoes MUITO mais chatas; tem que considerar elas individualmente!
    int ans  = 0;
    for (int turn = 0; turn < 3; ++turn) {
        vector dp(n+1, vector(2, vector(4, 0LL)));
        if (turn == 0) {
            dp[0][0][1] = 1;
            dp[1][0][0] = a[0];
            dp[1][0][1] = (mod-S(a[0]-1)) % mod;
            dp[1][1][1] = (mod-a[0]) % mod;
        } else if (turn == 1) {
            dp[1][0][2] = S(a[n-1]-1);
            dp[1][1][2] = a[n-1];
        } else {
            dp[1][0][3] = (mod-S2(a[n-1]-1)) % mod;
            int sq = a[n-1] * a[n-1] % mod;
            dp[1][1][3] = (mod-sq) % mod;
        }
        
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < 2; ++j) {
                add(dp[i][j][0], dp[i-1][j][0] * (a[i-2]+j));
                add(dp[i][j][0], (dp[i-1][j][2]+dp[i-1][j][3]) * (a[i-2]+j));
                add(dp[i][j][0], dp[i-1][j][1]);
                dp[i][j][0] = dp[i][j][0] * a[i-1] % mod;

                add(dp[i][j][1], dp[i-1][j][0] * (a[i-2]+j));
                add(dp[i][j][1], (dp[i-1][j][2]+dp[i-1][j][3]) * (a[i-2]+j));
                add(dp[i][j][1], dp[i-1][j][1]);
                dp[i][j][1] = dp[i][j][1] * (mod-S(a[i-1]-(1-j))) % mod;

                add(dp[i][j][2], dp[i-1][j][0]);
                add(dp[i][j][2], (dp[i-1][j][2]+dp[i-1][j][3]));
                dp[i][j][2] = dp[i][j][2] * S(a[i-2]-(1-j)) % mod;


                add(dp[i][j][3], dp[i-2][j][0] * (i == 2 ? 1LL : a[i-3]+j));
                add(dp[i][j][3], (dp[i-2][j][2]+dp[i-2][j][3]) * (i == 2 ? 1LL : a[i-3]+j));
                add(dp[i][j][3], dp[i-2][j][1]);
                dp[i][j][3] = dp[i][j][3] * (mod - S2(a[i-2]-(1-j))) % mod;
            }

            add(dp[i][1][0], dp[i-1][0][0] * a[i-1]);
            add(dp[i][1][0], (dp[i-1][0][2]+dp[i-1][0][3]) * a[i-1]);
            for (int j = 0; j < 4; ++j) {
                if (j == 1) continue;
                int adc = 0;
                add(adc, dp[i-1][0][j] * (mod - S(a[i-1]-1)));
                add(adc, dp[i-1][0][j] * a[i-2] % mod * (mod - a[i-1]));
                add(adc, dp[i-1][0][j] * (mod - a[i-1]));
                add(dp[i][1][1], adc);
            }
            add(dp[i][1][1], dp[i-1][0][1] * (mod - a[i-1]));
            add(dp[i][1][2], dp[i-1][0][0] * a[i-2]);
            add(dp[i][1][2], (dp[i-1][0][2]+dp[i-1][0][3]) * a[i-2]);
            int sq = a[i-2] * a[i-2] % mod; sq = (mod - sq) % mod;
            for (int j = 0; j < 4; ++j) {
                if (j == 1) continue;
                int adc = 0;
                add(adc, dp[i-2][0][j] * (mod - S2(a[i-2]-1)));
                add(adc, dp[i-2][0][j] * sq % mod * (i == 2 ? 1LL : a[i-3]));
                add(adc, dp[i-2][0][j] * sq);
                add(dp[i][1][3], adc);
            }
            add(dp[i][1][3], dp[i-2][0][1] * sq);
        }
        if (turn == 0) {
            // pegar transicao a transicao e somar nessa porra!
            for (int j = 0; j < 4; ++j) {
                if (j == 1) continue;
                add(ans, dp[n][1][j] * (a[n-1]+1) + dp[n][0][j]);
            }
            add(ans, dp[n][1][1]);
        } else if (turn == 1) {
            for (int j = 0; j < 4; ++j) {
                if (j == 1) continue;
                add(ans, dp[n][1][j]);
            }
        } else {
            for (int j = 0; j < 4; ++j) {
                if (j == 1) continue;
                add(ans, dp[n-1][1][j] * (a[n-2]+1) + dp[n-1][0][j]);
            }
            add(ans, dp[n-1][1][1]);
        }
    }
    cout << ans << endl;
}
int pensador(vector<int> a, int task) {
    int ans = 0;
    for (int i = 0; i <= a[0]; ++i) {
        for (int j = 0; j <= a[1]; ++j) {
            for (int k = 0; k <= a[2]; ++k) {
                if (i < a[0] and j < a[1] and k < a[2]) continue;
                vector<array<int, 3>> sexo(3);
                sexo[0][0] = a[0], sexo[1][0] = a[1], sexo[2][0] = a[2];
                sexo[0][1] = -i, sexo[1][1] = -j, sexo[2][1] = -k;
                sexo[0][2] = k, sexo[1][2] = i, sexo[2][2] = j;
                int tot_prod = 1;
                for (int w = 0; w < 3; ++w) {
                    int ntot = 0;
                    for (int x = 0; x < 3; ++x) {
                        if (task == 0 and w == 0 and x == 2) continue;
                        if (task == 1 and w == 0 and x != 2) continue;
                        if (task == 1 and w == 2 and x == 1) continue;
                        if (task == 2 and w == 0 and x != 2) continue;
                        if (task == 2 and w == 2 and x != 1) continue;
                        ntot += (tot_prod * sexo[w][x]);
                    }
                    swap(tot_prod, ntot);
                }
                ans += tot_prod;
            }
        }
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
    //vector<int> a = {1, 3, 6};
    //for (int i = 0; i < 3; ++i) {
    //    cout << pensador(a, i) << endl;
    //}
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

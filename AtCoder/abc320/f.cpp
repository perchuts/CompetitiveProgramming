#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato
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

int solve(int n, int h, vector<int> pos, vector<int> cost, vector<int> fuel){
    vector dp(h+1, vector(h+1, vector(2, 1e18)));
    for (int i = 0; i <= h; ++i) dp[h][i][1] = 0;
    int last = 0;
    pos.pb(pos.back());
    for (int i = 0; i < n; ++i) {
        vector ndp(h+1, vector(h+1, vector(2, 1e18)));
        int d = pos[i] - last;
        // nao fazer nada
        for (int x = 0; x + d <= h; ++x) for (int y = d; y <= h; ++y) ckmin(ndp[x][y][0], min(dp[x+d][y-d][0], dp[x+d][y-d][1]));
        // recarregar no x
        for (int x = 0; x + d <= h; ++x) for (int y = d; y <= h; ++y) 
            ckmin(ndp[min(x+fuel[i], h)][y][1], cost[i] + min(dp[x+d][y-d][0], dp[x+d][y-d][1]));
        if (i) {
            //recarregar no y
            for (int x = 0; x + d <= h; ++x) for (int y = d; y <= h; ++y) 
                ckmin(ndp[x][y][0], cost[i-1] + dp[x+d][min(h, y-d+fuel[i-1])][0]);
            //fazer os 2 ao mesmo tempo
            for (int x = 0; x + d <= h; ++x) for (int y = d; y <= h; ++y) 
                ckmin(ndp[min(x+fuel[i], h)][y][1], cost[i] + cost[i-1] + dp[x+d][min(h, y-d+fuel[i-1])][0]);
        }
        last = pos[i];
        swap(dp, ndp);
    }
    int ans = 1e18;
    for (int i = 0; i <= h; ++i) ckmin(ans, dp[i][i][0]);
    return (ans < 1e12 ? ans : -1);
}

int brute(int n, int h, vector<int> pos, vector<int> cost, vector<int> fuel){
    int ans = 1e18;
    //for (int i = 0; i < (1 << 2*n); ++i) {
    //    bool ok = 1;
    //    for (int j = 0; j < n; ++j) {
    //        if ((i >> j & 1)) ok &= !((i >> (2*j))&1);
    //    }
    //    if (!ok) continue;
    //    int agr = 0, comb = h, custo = 0;
    //    for (int j = 0; j < n; ++j) {
    //        int d = agr-pos[j];
    //        if (d > comb) {
    //            custo = 1e18;
    //            break;
    //        }
    //        comb -= d;
    //        if (i >> j & 1) comb = min(h,
    //    }
    //}
    return (ans < 1e12 ? ans : -1);
}

int32_t main(){_
#ifndef gato
    int n, h; cin >> n >> h;
    vector<int> pos(n), cost(n), fuel(n);
    for (auto& x : pos) cin >> x;
    for (int i = 0; i < n-1; ++i) cin >> cost[i] >> fuel[i];
    cout << solve(n, h, pos, cost, fuel) << endl;
#else
    int t = 1;
    while (t--) {
        int n = 3, h = rnd(1, 10);
        vector<int> pos(3);
        pos[0] = rnd(1, 5);
        for (int i = 1; i < n; ++i) pos[i] = rnd(pos[i-1]+1, pos[i-1]+h);
        vector<int> cost(n), fuel(n);
        for (int i = 0; i < n-1; ++i) cost[i] = rnd(1, 10), fuel[i] = rnd(1, h);
        int my = solve(n, h, pos, cost, fuel);
        int ans = brute(n, h, pos, cost, fuel);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << h << endl;
            for (auto x : pos) cout << x << ' ';
            cout << endl;
            for (int i = 0; i < n-1; ++i) cout << cost[i] << ' ' << fuel[i] << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
        }
    }
#endif
}

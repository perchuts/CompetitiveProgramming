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
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // estou liberado de fazer uma solucao nk?
    // 10^5 * 1800 -> sim!
    // want to choose an increasing subsequence. only them will recieve stuff
    // so actually only 360 elements matter!
    vector<ii> v2 = {{a[0], 0}};
    for (int i = 1; i < n; ++i) {
        if (v2.back().first < a[i]) {
            v2.pb({a[i], i});
        }
    }
    // dp[pos][value][spent]
    // remember to consider transition last element -> n!!
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(k+1, vector<int>(k+1, -inf)));
    dp[1][0][0] = 0;
    //for (auto [x, y] : v2) cout << x << ' ' <<y << endl;
    v2.pb({0, n});
    for (int i = 0; i < sz(v2); ++i) {
        auto [val, pos] = v2[i];
        int prox_pos = (i == sz(v2)-1 ? n : v2[i+1].second);
        for (int j = 0; j <= k; ++j) {
            for (int w = 0; w <= k; ++w) { 
                dp[i&1][j][w] = dp[(i&1)^1][j][w] + (prox_pos - pos) * j;
            }
        }
        for (int j = 0; j <= k; ++j) {
            for (int w = 0; w <= k; ++w) {
                if (j) ckmax(dp[(i&1)^1][j][w], dp[(i&1)^1][j-1][w]);
                if (j <= val and w >= j) ckmax(dp[i&1][j][w], dp[(i&1)^1][j][w-j] + (prox_pos - pos) * j);
                //cout << dp[i&1][j][w] << " ";
            }
            //cout << endl;
        }
        //cout << endl;
        
    }
    int ans = 0;
    for (int j = 0; j <= k; ++j) {
        for (int w = j; w <= k; ++w) { 
            ckmax(ans, dp[(sz(v2)&1)^1][j][w]);
        }
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

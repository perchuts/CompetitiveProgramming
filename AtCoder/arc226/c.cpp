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

vector<iii> solve(int n, int m) {
    if (n % 2 == 0 or m % 2 == 0) {
        vector<iii> ans;
        for (int i = 0; i < n-1; i += 2) {
            for (int j = 0; j < m-1; j += 2) {
                ans.pb({i, j, 1});
            }
        }
        return ans;
    }
    //vector<int> dp(1<<(n*m), -1e18);
    //jco
    //auto get = [&] (int mask, int i, int j) {
    //    return (mask >> (m*i+j)) & 1;
    //};
    //auto sq = [&] (int i, int j, int s) {
    //    return (1 << (m*i+j)) + (1 << (m*(i+s)+j)) + (1 << (m*i+(j+s))) + (1 << (m*(i+s)+(j+s)));
    //};
    //dp[0] = 0;
    //vector<iii> tr(1<<(n*m));
    //for (int i = 1; i < (1 << (n*m)); ++i) {
    //    for (int h = 0; h < n-1; ++h) {
    //        for (int c = 0; c < m-1; ++c) {
    //            if (!get(i, h, c)) continue;
    //            for (int s = 1; h + s < n and c + s < m; ++s) {
    //                if (get(i, h+s, c) and get(i, h, c+s) and get(i, h+s, c+s) and ckmax(dp[i], dp[i-sq(h, c, s)]+1)) {
    //                    tr[i] = {h, c, s};
    //                }
    //            }
    //        }
    //    }
    //}
    //int opt = 0;
    //for (int i = 0; i < (1 << (n*m)); ++i) {
    //    if (dp[opt] < dp[i]) opt = i;
    //}
    //vector<iii> ops;
    //while (opt) {
    //    ops.pb(tr[opt]);
    //    auto [h, c, s] = tr[opt];
    //    opt -= sq(h, c, s);
    //}
    //cout << sz(ops) << endl;
    //for (auto [x, y, z] : ops) cout << x+1 << " " << y+1 << ' ' << z << endl;
    ii ini = {0, 0};
    ii fim = {min(n, m)-1, min(n, m)-1};
    vector<iii> ans;
    if (n < m) {
        for (int i = 0; i < n-1; i += 2) {
            for (int j = n; j < m; j += 2) {
                ans.pb({i, j, 1});
            }
        }
    } else if (m < n) {
        for (int i = m; i < n; i += 2) {
            for (int j = 0; j < m-1; j += 2) {
                ans.pb({i, j, 1});
            }
        }
    }
    while (true) {
        auto [x1, y1] = ini;
        auto [x2, y2] = fim;
        int n2 = x2-x1+1;
        int m2 = y2-y1+1;
        if (min(n2, m2) <= 3) break;
        int t = min(n2, m2);
        ans.pb({x1, y1, t-1});
        for (int i = x1+1; i < x2-2; i += 2) ans.pb({i, y1, 1});
        for (int i = x1+2; i < x2-1; i += 2) ans.pb({i, y2-1, 1});
        for (int i = y1+2; i < y2-1; i += 2) ans.pb({x1, i, 1});
        for (int i = y1+1; i < y2-2; i += 2) ans.pb({x2-1, i, 1});
        ini = {x1+2, y1+2};
        fim = {x2-2, y2-2};
    }
    auto [x1, y1] = ini;
    auto [x2, y2] = fim;
    int n2 = x2-x1+1;
    int m2 = y2-y1+1;
    if (n2 == 3) {
        //cout << "n2" << endl;
        for (int i = y1; i < y2; i += 2) ans.pb({x1, i, 1});
    } else if (m2 == 3) {
        //cout << "m2" << endl;
        for (int i = x1; i < x1; i += 2) ans.pb({i, y1, 1});
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        auto ans = solve(n, m);
        //vector<vector<int>> aa(n, vector<int>(m, -1));
        //int ptr = 1;
        //for (auto [i, j, s] : ans) {
        //    if (max({aa[i][j], aa[i+s][j], aa[i][j+s], aa[i+s][j+s]}) != -1) {
        //        assert(false);
        //    }
        //    aa[i][j] = aa[i+s][j] = aa[i][j+s] = aa[i+s][j+s] = ptr++;
        //    for (int i = 0; i < n; ++i) {
        //        for (int j = 0; j < m; ++j) {
        //            cout << aa[i][j] << " ";
        //        }
        //        cout << endl;
        //    }
        //cout << endl;
        //    cout << flush;
        //}
        cout << sz(ans) << endl;
        for (auto [x, y, z] : ans) cout << x+1 << " " << y+1 << " " << z << endl;
    }
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

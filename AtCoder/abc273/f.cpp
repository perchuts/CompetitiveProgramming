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

void solve(){
    int n, x; cin >> n >> x;
    vector<int> coord = {x, 0}, y(n), z(n);
    map<int, int> quem;
    for (auto& a : y) cin >> a, coord.pb(a);
    for (int i = 0; i < n; ++i) quem[y[i]] = i;
    for (auto& a : z) cin >> a, coord.pb(a);
    for (int i = 0; i < n; ++i) quem[z[i]] = i+n;
    quem[x] = inf;
    quem[0] = -inf;
    sort(all(coord));
    auto get = [&] (int k) { return lower_bound(all(coord), k) - begin(coord); };
    int ans = 1e18;
    queue<ii> q; q.push({get(0), get(0)});
    int N = sz(coord), st = get(0);
    vector dp(N, vector(N, vector(2, ans)));
    vector<int> id(N);
    for (int i = 0; i < N; ++i) id[i] = quem[coord[i]];
    for (int i = N-1; ~i; --i) {
        for (int j = i; j < N; ++j) {
            if (i == j) {
                if (i == st) dp[i][j][0] = dp[i][j][1] = 0; 
                continue;
            }
            for (int b = 0; b < 2; ++b) {
                int v1 = coord[i];
                if (i < N-1) {
                    int v2 = (b ? coord[j] : coord[i+1]);
                    if (id[i] >= n) {
                        ckmin(dp[i][j][0], dp[i+1][j][b] + abs(v1-v2));
                    } else if (id[i] >= 0) {
                        int k = get(z[id[i]]);
                        if (i+1 <= k and k <= j) ckmin(dp[i][j][0], dp[i+1][j][b] + abs(v1-v2));
                    }
                }
                v1 = coord[j];
                if (j) {
                    int v2 = (b ? coord[j-1] : coord[i]);
                    if (id[j] >= n) {
                        ckmin(dp[i][j][1], dp[i][j-1][b] + abs(v1-v2));
                    } else if (id[j] >= 0) {
                        int k = get(z[id[j]]);
                        if (i <= k and k <= j-1) ckmin(dp[i][j][1], dp[i][j-1][b] + abs(v1-v2));
                    }
                }
            }
            if (coord[i] == x) ckmin(ans, dp[i][j][0]);
            if (coord[j] == x) ckmin(ans, dp[i][j][1]);
        }
    }
    cout << (ans == 1e18 ? -1 : ans) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

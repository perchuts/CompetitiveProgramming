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
double dp[100001], other[100001];
int forb[100001];
void solve(){
    int n, m, k; cin >> n >> m >> k;
    for (int i = 0; i < k; ++i) {
        int x; cin >> x;
        forb[x] = i+1;
    }
    if (m <= k) {
        for (int i = 0; i+m < n; ++i) {
            bool ok = 1;
            for (int j = i+1; j <= i+m; ++j) ok &= (forb[j] != 0);
            if (ok) {
                cout << -1 << endl;
                exit(0);
            }
        }
    }
    double s1 = 0, s2 = 0;
    for (int j = n-1; ~j; --j) {
        other[j] = 0;
        if (j + m + 1 < n) {
            s1 -= dp[j+m+1];
            s2 -= other[j+m+1];
        }
        s1 += dp[j+1];
        s2 += other[j+1];
        if (j == 0) {
            s1 /= m, s2 /= m;
            dp[0] = 1+(s1)/(1.0-s2);
            for (int x = 1; x < n; ++x) dp[x] += other[x] * dp[0];
        } else {
            if (forb[j]) {
                other[j] = 1;
            } else {
                dp[j] = s1/(double)m;
                other[j] = s2/(double)m;
            }
            dp[j] += 1;
        }
    }
    cout << fixed << setprecision(10) << dp[0] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

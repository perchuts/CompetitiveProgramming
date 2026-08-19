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

void brute(int n, int m, int k) {

}

void solve() {
    int n, m, k; cin >> n >> m >> k;
    auto get = [&] (vector<int> b, bool count_b = 1) {
        vector dp(n+1, 0LL);
        int sd = 0;
        for (auto d : b) {
            vector ndp(n+1, 0LL);
            for (int w = 0; w <= n; ++w) {
                for (int i = 0; i < k and i <= w; ++i) {
                    ndp[w] = (ndp[w] + dp[w-i]) % mod;
                }
            }
            for (int i = 0; i < d; ++i) {
                if (sd + i <= n) ndp[sd+i] = (ndp[sd+i] + 1) % mod;
            }
            swap(dp, ndp);
            // can fall now!
            sd += d;
        }
        int ans = (count_b == 1 and sd % (k-1) == n % (k-1) and sd <= n);
        for (int i = n % (k-1); i <= n; i += k-1) ans = (ans + dp[i]) % mod;
        return ans;
    };
    int np = (n-1) % (k-1) + 1, mp = (m-1) % (k-1) + 1, r = (n + m - 1) / (k-1);
    vector<int> lb(r), ub(r);
    lb[r-1-(m-k+np)/(k-1)] = np;
    ub[r-1-(n-k+mp)/(k-1)] = k-mp;
    for (int i = r-(n-k+mp)/(k-1); i < r; ++i) ub[i] = k-1;
    reverse(all(lb)), reverse(all(ub));
    for (auto x : lb) cout << x << " ";
    cout << endl;
    for (auto x : ub) cout << x << " ";
    cout << endl;
    int x = get(ub), y = get(lb, 0);
    int ans = (mod + x - y) % mod;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

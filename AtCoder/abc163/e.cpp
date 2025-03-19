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

int brute(int n, vector<int> a){
    vector<int> p(n);
    iota(all(p), 0);
    int best = 0;
    do {
        int cur = 0;
        for (int i = 0; i < n; ++i) cur += abs(p[i] - i) * a[p[i]];
        ckmax(cur, best);
    } while (next_permutation(all(p)));
    return best;
}

int solve(int n, vector<int> a) {
    vector<vector<int>> dp(n+1, vector<int>(n+1, -1e18));
    vector<int> p(n); iota(all(p), 0);
    sort(all(p), [&] (int x, int y) { return a[x] > a[y]; });
    dp[0][0] = 0;
    for (int s = 1; s <= n; ++s) {
        for (int i = 0; i <= s; ++i) {
            int k = p[s-1], j = s - i;
            if (i != 0) ckmax(dp[i][j], dp[i-1][j] + abs(k - i + 1) * a[k]);
            if (i != s) ckmax(dp[i][j], dp[i][j-1] + abs(n - j - k) * a[k]);
        }
    }
    int ans = -1e18;
    for (int i = 0; i < n; ++i) ckmax(ans, dp[i][n-i]); 
    return ans;
}

int32_t main(){_
#ifdef gato
    int t = 1;
    while (true) {
        int n = rnd(1, 8);
        vector<int> a(n);
        for (auto& x : a) x = rnd(1, 5);
        int ans = brute(n, a), my = solve(n, a);
        if (ans != my) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#else
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << solve(n, a) << endl;
#endif
}

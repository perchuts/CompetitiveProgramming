#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
//#define gato
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

int solve(int n, vector<int> a){
    vector<int> ord(2*n); iota(all(ord), 0); 
    sort(all(ord), [&] (int x, int y) { return a[x] > a[y]; });
    set<ii> s, s2;
    vector<int> mark(2*n);
    int ans = 0;
    for (int i = 0; i < n; ++i) ans += a[ord[i]], mark[ord[i]] = 1, s.insert({a[ord[i]], ord[i]});
    int score = 0;
    for (int i = 0; i < 2*n; ++i) {
        score += (mark[i] ? 1 : -1);
        if (mark[i]) s.erase({a[i], i});
        else s2.insert({-a[i], i});
        if (score < 0) {
            // faz o L
            auto [val, id] = *begin(s);
            auto [val2, id2] = *begin(s2);
            mark[id] = 0;
            mark[id2] = 1;
            ans += -val2-val;
            s.erase({val, id});
            s2.erase({val2, id2});
            score += 2;
        }
    }
    return ans;
}
int brute(int n, vector<int> a) {
    vector<vector<int>> dp(2*n+1, vector<int>(n+1, -1e18));
    dp[0][0] = 0;
    for (int i = 1; i <= 2*n; ++i) {
        for (int j = 0; j <= min(n, i); ++j) {
            if (j) ckmax(dp[i][j], dp[i-1][j-1] + a[i-1]);
            if (j != n) ckmax(dp[i][j], dp[i-1][j+1]);
        }
    }
    return dp[2*n][0];
}
int32_t main(){_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(2*n);
        for (auto& x : a) cin >> x;
        cout << solve(n, a) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 30);
        vector<int> a(2*n);
        for (auto& x : a) x = rnd(0, 500);
        int my = solve(n, a);
        int ans = brute(n, a);
        if (my != ans) {
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
#endif
}

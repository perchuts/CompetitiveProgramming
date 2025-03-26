#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato
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

int solve(int n, int k, vector<int> a){
    int ans = 0;
    priority_queue<int> inside, outside;
    reverse(all(a));
    for (int i = k; i < n; ++i) {
        if ((i+1) % (k+1) == 0) {
            inside.push(-a[i]), ans += a[i];
            while (!outside.empty()) outside.pop();
        } else {
            outside.push(a[i]);
            while (true) {
                int x = -inside.top();
                int y = outside.top();
                if (y > x) {
                    inside.pop(), outside.pop();
                    ans += y - x;
                    inside.push(-y), outside.push(x);
                } else break;
            }
        }
    }
    return ans;
}

int brute(int n, int k, vector<int> a) {
    reverse(all(a));
    vector<int> dp(n+1, -inf);
    dp[0] = 0;
    for (int i = k; i < n; ++i) {
        int lim = (i+1) / (k+1);
        for (int j = lim; j >= 1; --j) {
            ckmax(dp[j], dp[j-1] + a[i]);
        }
    }
    return *max_element(all(dp)); 
}

int32_t main(){_
#ifndef gato
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        cout << solve(n, k, a) << endl;
    }
#else
    int t = 1;
    while (t) { 
        int n = rnd(100, 1e4), k = rnd(1, 50);
        vector<int> a(n);
        for (auto& x : a) x = rnd(1, 1e9);
        int my = solve(n, k, a), ans = brute(n, k, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << k << endl;
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

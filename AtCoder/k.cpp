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

void solve() {
    int n; cin >> n;
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x; pq.push(x);
    }
    vector<int> a;
    while (!pq.empty()) {
        int x = pq.top(); pq.pop();
        if (sz(pq) <= 1) {
            a.pb(x);
            continue;
        }
        int y = pq.top(); pq.pop();
        int z = pq.top(); pq.pop();
        if (x == z) {
            pq.push(x);
            pq.push(2*x);
        } else {
            a.pb(x);
            pq.push(y);
            pq.push(z);
        }
    }
    bitset<2000005> dp;
    dp[0] = 1;
    for (auto x : a) {
        dp |= (dp << x);  
        for (int i = 0; i < x; ++i) {
            if (dp[i]) dp[x-i] = 1;
        }
        dp |= (dp >> x);
    }
    int ans = 0;
    for (int i = 0; i <= 2000000; ++i) ans += dp[i];
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


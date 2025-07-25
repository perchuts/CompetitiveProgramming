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

const int P = 998244353;
int add(int a, int b) {
    a += b;
    if (a >= P) a -= P;
    return a;
}

void solve(){
    int n; cin >> n;
    vector<int> a(n);
    for (auto &i : a) cin >> i;

    vector dp(n + 1, 0ll);
    dp[n] = 1;

    const int MX = 1e5 + 10;
    vector acc(MX, 0LL);

    for (int i = n - 1; i >= 0; --i) {
        dp[i] = add(dp[i + 1], acc[a[i]]);
        acc[a[i]] = add(acc[a[i]], dp[i + 1]);
    }
    
    cout << dp[0] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

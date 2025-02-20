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
    int n, m; cin >> n >> m;
    vector<int> v1(n), v2(m);
    for (auto& x : v1) cin >> x;
    for (auto& x : v2) cin >> x;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int eu = (i * v1[i] - (n-1-i) * v1[i]) % mod;
        eu = (eu + mod) % mod;
        sum = (sum + eu) % mod;
    }
    int ans = 0;
    for (int j = 1; j < m; ++j) {
        int ways = j * (m-j) % mod;
        ans = (ans + ways * (v2[j]-v2[j-1])) % mod;
    }
    cout << (ans * sum) % mod << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

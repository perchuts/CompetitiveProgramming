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
    vector<int> a(n), b(m); 
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    sort(all(a)), sort(all(b));
    reverse(all(a)), reverse(all(b));
    vector<int> use1(n+1), use2(m+1);
    for (int i = 1; i <= n; ++i) use1[i] = use1[i-1] + a[i-1];
    for (int i = 1; i <= m; ++i) use2[i] = use2[i-1] + b[i-1];
    for (int i = n-1; i >= 1; --i) ckmax(use1[i], use1[i+1]);
    int ans = max(0LL, use1[1]);
    for (int i = 1; i <= min(n, m); ++i) ckmax(ans, use2[i] + use1[i]);        
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

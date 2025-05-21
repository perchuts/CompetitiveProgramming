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
    int n; cin >> n;
    vector<int> freq(n+1);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        freq[x]++;
    }
    vector<int> pw(n+1, 1), ans(n+1);
    for (int i = 1; i <= n; ++i) pw[i] = 2 * pw[i-1] % mod;
    for (int i = n; i; --i) {
        int c = 0;
        for (int j = i; j <= n; j += i) c += freq[j];
        ans[i] = (mod - 1 + pw[c]) % mod; 
        for (int j = 2 * i; j <= n; j += i) ans[i] = (ans[i] + mod - ans[j]) % mod;
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

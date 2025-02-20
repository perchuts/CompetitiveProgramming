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
    vector<int> a(n+1), pr(n+1), suf(n+2);
    for (int i = 1; i <= n; ++i) cin >> a[i], pr[i] = (pr[i-1]) + max(0LL, a[i]);
    for (int i = n; i >= 1; --i) suf[i] = suf[i+1] + max(0LL, -a[i]); 
    int ans = -1e18;
    for (int i = 1; i <= n; ++i) {
        // entao eu preciso ter feito o vizinho desse bicho tambem!
        if (a[i] < 0) {
            if (i != 1 and a[i-1] < 0) continue;
            ckmax(ans, pr[i-1] + abs(a[i]) + suf[i+1]);
        } else {
            if (i != n and a[i+1] > 0) continue;
            ckmax(ans, pr[i-1] + a[i] + suf[i+1]);
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}

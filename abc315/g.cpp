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
ll inv(ll a, ll b) {
	return a > 1 ? b - inv(b%a, a)*b/a : 1;
}
void solve(){
    int n, a, b, c, x; cin >> n >> a >> b >> c >> x;
    int gbc = gcd(b, c), cl = c / gbc, bl = b / gbc, ibc = inv(bl, cl), ans = 0, sobra = x;
    for (int i = 1; i <= n and a * i <= x; ++i) {
		sobra -= a;
        int z = sobra % c; 
        if (z % gbc) continue;
        int zl = z / gbc, yl = zl * ibc % cl;
        int lim1 = max(1LL, (sobra - c*n + b - 1) / b), lim2 = min(n, (sobra-c)/b);
        if (lim1 > lim2) continue;
        int x1 = lim1/cl, x2 = lim2/cl, aq = 0;
        if (x1 == x2) {
            aq += (lim1 % cl <= yl and yl <= lim2 % cl);
        } else {
            aq += x2-x1-1;
            aq += (lim1 % cl <= yl);
            aq += (yl <= lim2 % cl);
        }
        ans += aq;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

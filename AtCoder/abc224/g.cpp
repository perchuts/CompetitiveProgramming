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
    int n, s, t, a, b; cin >> n >> s >> t >> a >> b;
    int l = 1, r = t;
    auto eval = [&] (int i) {
        double ans = b*n/(double)(t-i+1) + a*(t-i)/(double)2;
        return ans;
    };
    while (r-l >= 3) {
        int m1 = l + (r-l)/3;
        int m2 = r - (r-l)/3;
        if (eval(m1) <= eval(m2)) r = m2;
        else l = m1;
    }
    double ans = 5e18;
    for (int i = l; i <= r; ++i) ckmin(ans, eval(i));
    if (s <= t) ckmin(ans, (t-s)*a);
    cout << fixed << setprecision(10) << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

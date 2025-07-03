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
    int n, l, d; cin >> n >> l >> d;
    vector<double> dp1(n+d+5), add(n+d+5);

    double p = 1.0 / d;
    dp1[0] = 1;
    double cum = 0;
    for (int i = 0; i <= n+d; ++i) {
        cum += add[i], dp1[i] += cum;
        if (i < l) add[i+1] += dp1[i] * p, add[i+1+d] -= dp1[i] * p;
    }
    for (int i = 1; i <= n+d; ++i) dp1[i] += dp1[i-1];
    vector<double> ans(n+d+2);
    double sexo = (n < l+d-1 ? dp1[l+d-1] - dp1[n] : 0);
    for (int i = n; ~i; --i) {
        ans[i] = (i >= l ? dp1[i-1] - dp1[l-1] : 0) + sexo;
        ckmax(ans[i], (ans[i+1]-ans[i+d+1])*p);
        ans[i] += ans[i+1]; 
    }
    ans[0] -= ans[1];
    cout << fixed << setprecision(10) << ans[0] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

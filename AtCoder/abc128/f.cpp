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
    vector<int> v(n), x(n), y(n);
    for (auto& z : v) cin >> z;
    for (int i = 1; i < n; ++i) for (int j = i; j < n-2; j += i) {
        x[i] += v[j], y[i] += v[n-1-j];
    }
    int ans = 0;
    for (int a = 2; a < n-1; ++a) {
        int pt = n-1-a;
        auto test = [&] (int d) { 
            if (d >= a) return;
            if (a % d == 0 and a <= pt) return;
            ckmax(ans, x[d] + y[d]); 
        };
        for (int d = 1; d * d <= pt; ++d) {
            if (pt % d) continue;
            test(d), test(pt/d);
        }
        int d = n-1-a;
        for (int i = 1; i * i <= d; ++i) {
            if (d % i) continue;
            y[i] -= v[a];
            x[i] -= v[n-1-a];
            if (i * i != d) y[d/i] -= v[a], x[d/i] -= v[n-1-a];
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

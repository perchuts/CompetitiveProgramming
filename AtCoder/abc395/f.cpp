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
    int n, x; cin >> n >> x;
    vector<int> u(n), d(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) cin >> u[i] >> d[i], sum += u[i] + d[i];
    auto cut = [&] (vector<int>& v) {
        for (int i = 1; i < n; ++i) {
            if (abs(v[i] - v[i-1]) > x) {
                int dist = abs(v[i]-v[i-1])-x;
                if (v[i] > v[i-1]) v[i] -= dist;
                else v[i-1] -= dist;
            }
        }
        for (int i = n-2; ~i; --i) {
            if (abs(v[i] - v[i+1]) > x) {
                int dist = abs(v[i]-v[i+1])-x;
                if (v[i] > v[i+1]) v[i] -= dist;
                else v[i+1] -= dist;
            }
        }
    };
    cut(u), cut(d);
    for (int i = 1; i < n; ++i) assert(abs(u[i]-u[i-1]) <= x), assert(abs(d[i] - d[i-1]) <= x);
    int ans = 1e18;
    for (int i = 0; i < n; ++i) ckmin(ans, u[i] + d[i]);
    cout << sum-n*ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

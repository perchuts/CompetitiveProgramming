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
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    vector<int> pref(n+1);
    for (int i = 1; i <= n; ++i) pref[i] = pref[i-1] + v[i-1];
    int p1 = 2, p2 = 4, ans = 1e18;
    vector<int> a(4);
    a[0] = v[0], a[1] = v[1], a[2] = v[2], a[3] = pref[n] - pref[3];
    auto test = [&] (int a, int b, int c) {
        if (a == b or b == c or c == n+1) return;
        int x1 = pref[a-1], x2 = pref[b-1] - x1, x3 = pref[c-1] - x2 - x1, x4 = pref[n] - x1 - x2 - x3;
        ckmin(ans, max({x1, x2, x3, x4}) - min({x1, x2, x3, x4}));
    };
    for (int i = 3; i <= n-1; ++i) {
        while (p1+1 < i and a[0] + v[p1-1] <= a[1] - v[p1-1]) a[0] += v[p1-1], a[1] -= v[p1-1], p1++;
        while (p2+1 <= n and a[2] + v[p2-1] <= a[3] - v[p2-1]) a[2] += v[p2-1], a[3] -= v[p2-1], p2++;
        for (int j = 0; j < 2; ++j) for (int k = 0; k < 2; ++k) test(p1+j, i, p2+k); 
        a[1] += v[i-1], a[2] -= v[i-1];
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

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
    vector<int> pos(n), a(n), b(n), c(n), p(n), pr(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i]; --p[i];
        pos[p[i]] = i;
    }
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i] >> c[i], swap(c[i], b[i]), swap(a[i], c[i]);
    int ans = 1e18;
    vector<int> bit(n+1, 1e18);
    auto insert = [&] (int x, int k) {
        ++x;
        while (x <= n) ckmin(bit[x], k), x += x & (-x);
    };
    auto query = [&] (int x) {
        ++x;
        int ans = 1e18;
        while (x) ckmin(ans, bit[x]), x -= x & (-x);
        return ans;
    };
    pr[0] = c[0];
    for (int i = 1; i < n; ++i) pr[i] = pr[i-1] + c[i];
    int bef = 0;
    vector<int> sm(n+1); sm[n-1] = min(b.back(), c.back());
    for (int i = n-2; i >= 0; --i) sm[i] = sm[i+1] + min(b[i], c[i]);
    for (int i = 0; i < n; ++i) {
        // so eu (primeiro e ultimo
        ckmin(ans, bef+sm[i+1]);
        // eu nao sou o primeiro, mas sou o ultimo
        int my_best = query(pos[i])+(i?pr[i-1]:0);
        ckmin(ans, my_best+sm[i+1]);
        ckmin(my_best, bef);
        insert(pos[i], my_best-pr[i]);
        bef += min(a[i], c[i]);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

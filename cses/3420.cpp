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
    vector<int> a(n), seta(n, n);
    map<int, int> mp;
    for (auto& x : a) cin >> x;
    mp[a[n-1]] = n-1;
    for (int i = n-2; i >= 0; --i) {
        if (mp.count(a[i])) seta[i] = mp[a[i]];
        mp[a[i]] = i;
    }
    vector<vector<int>> sp(18, vector<int>(n));
    for (int j = 0; j < 18; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {
            if (j == 0) sp[j][i] = seta[i];
            else sp[j][i] = min(sp[j-1][i], sp[j-1][i+(1<<(j-1))]);
        }
    }
    vector<int> tam(n+1);
    for (int i = 2; i <= n; ++i) tam[i] = 1 + tam[i/2];
    auto query = [&] (int l, int r) {
        int tt = tam[r-l+1];
        return min(sp[tt][l], sp[tt][r-(1<<tt)+1]);
    };
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int l = i, r = n-1, opt = i;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (query(i, md) <= md) r = md-1;
            else l = md+1, opt = md;
        }
        ans += opt-i+1;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

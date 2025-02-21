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
    int n, h; cin >> n >> h;
    vector<int> a(n), b(n);
    int mx = 0;
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i], ckmax(mx, a[i]);
    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) {
        return b[x] > b[y];
    });
    int ans = (h+mx-1)/mx, ps = 0;
    for (int i = 0; i < n; ++i) {
        ps += b[ord[i]];
        if (ps >= h) {
            ckmin(ans, i+1);
            break;
        }
        ckmin(ans, i+1+(h-ps+mx-1)/mx);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

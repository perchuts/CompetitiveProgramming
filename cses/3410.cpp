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
    int aa, bb; cin >> aa >> bb;
    vector<int> sign = {1, -1};
    int mxx = (aa+bb), mnx = (aa+bb), mxy = (aa-bb), mny = (aa-bb);
    auto add = [&] (int a, int b) {
        ckmax(mxx, a+b); 
        ckmin(mnx, a+b); 
        ckmax(mxy, a-b);
        ckmin(mny, a-b);
    };
    cout << 0 << endl;
    int ans = 0;
    for (int i = 0; i < n-1; ++i) {
        int x, y; cin >> x >> y;
        ckmax(ans, abs(x+y-mxx));
        ckmax(ans, abs(x+y-mnx));
        ckmax(ans, abs(x-y-mxy));
        ckmax(ans, abs(x-y-mny));
        cout << ans << endl;
        add(x, y);
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

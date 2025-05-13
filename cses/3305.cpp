#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    vector<char> sexo = {'F', 'S'};
    int queries = 0;
    auto ask = [&] (int i, int j) {
        if (j == 0) return inf;
        queries++;
        assert(queries <= 100);
        cout << sexo[i] << ' ' << j << endl;
        int x; cin >> x;
        return x;
    };
    int n, k; cin >> n >> k;
    int other = k - min(n, k);
    auto F = [&] (int x) {
        return min(ask(0, x), ask(1, k-x));
    };
    int ans = F(min(n, k)), l = other, r = min(n, k)-1;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        int a = F(md), b = F(md+1);
        ckmax(ans, max(a, b));
        if (a < b) l = md+1;
        else r = md-1;
    }
    cout << "! " << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

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

const int MAX = maxn;
const int MAX2 = 20;

namespace sparse {
int m[MAX2][MAX], n;
void build(int n2, vector<int> v) {
    n = n2;
    for (int i = 0; i < n; i++) m[0][i] = v[i];
    for (int j = 1; (1<<j) <= n; j++) for (int i = 0; i+(1<<j) <= n; i++)
        m[j][i] = max(m[j-1][i], m[j-1][i+(1<<(j-1))]);
}
int query(int a, int b) {
    int j = __builtin_clz(1) - __builtin_clz(b-a+1);
    return max(m[j][a], m[j][b-(1<<j)+1]);
}
};
void solve(){
    int n; cin >> n;
    vector<int> a(n), seta(n);
    for (auto& x : a) cin >> x;
    int q; cin >> q;
    vector<ii> qu(q);
    seta[n-1] = n;
    for (int i = n-2; ~i; --i) {
        seta[i] = seta[i+1];
        while (a[seta[i]-1] >= 2 * a[i]) seta[i]--;
    }
    for (int i = 0; i < n; ++i) seta[i] = seta[i] - i;
    sparse::build(n, seta);
    for (auto& [x, y] : qu) {
        cin >> x >> y;
        --x, --y;
        int l = 1, r = (y-x+1)/2, ans = 0;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            int k = sparse::query(x, x+md-1);
            int dist = (y-md+1) - x;
            if (k <= dist) ans = md, l = md+1;
            else r = md-1;
        }
        cout << ans << endl;
    }

}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

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
const int maxn = 1e4+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int crivo[maxn];

ll inv(ll a, ll b) {
	return a > 1 ? b - inv(b%a, a)*b/a : 1;
}

void solve(){
    int k; cin >> k;
    if (k % 4 == 0 or k % 5 == 0) {
        cout << -1 << endl;
        return;
    }
    if (k % 2 == 0) k /= 2;
    k *= 9;
    int B = sqrt(k);
    unordered_map<int, int> sexo;
    int cur = 10 % k;
    for (int i = 1; i < B; ++i, cur = 10 * cur % k) {
        if (!sexo.count(cur)) sexo[cur] = i;
    }
    int ans = k+1;
    cur = inv(cur, k);
    for (int j = 0, eu = 1; j <= k; j += B, eu = eu * cur % k) {
        if (j and eu == 1) ckmin(ans, j);
        if (sexo.count(eu)) ckmin(ans, j+sexo[eu]);
    }
    if (ans == k+1) ans = -1;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}

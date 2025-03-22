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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
    int n, a, b, c; cin >> n >> a >> b >> c;
    int N = n+1;
    vector<int> fat(N, 1), ifat(N);
    for (int i = 1; i < N; ++i) fat[i] = i * fat[i-1] % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e & 1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat.back() = fexp(fat.back(), mod-2);
    for (int i = N-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    auto C = [&] (int a, int b) {
        if (a < b) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    int aa = 1, bb = 1, cc = 1, ans = (n&1 ? mod-1 : 1);
    for (int i = 1; i <= n; ++i) { 
        int naa = (2*aa - C(i-1, min(i-1, a)) + mod) % mod;
        int nbb = (2*bb - C(i-1, min(i-1, b)) + mod) % mod;
        int ncc = (2*cc - C(i-1, min(i-1, c)) + mod) % mod;
        if (a >= i) naa = (naa + 1) % mod;
        if (b >= i) nbb = (nbb + 1) % mod;
        if (c >= i) ncc = (ncc + 1) % mod;
        aa = naa, bb = nbb, cc = ncc;
        int ways = aa * bb % mod * cc % mod * C(n, i) % mod;
        if (i % 2 == n % 2) ans = (ans + ways) % mod;
        else ans = (ans + mod - ways) % mod;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

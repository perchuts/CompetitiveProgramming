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
    int r, g, b, k; cin >> r >> g >> b >> k;
    int N = r+g+b+5; N *= 2;
    vector<int> fat(N, 1), ifat(N);
    for (int i = 1; i < N; ++i) fat[i] = i * fat[i-1] % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat.back() = fexp(fat.back(), mod-2);
    for (int i = N-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    auto c = [&] (int a, int b) {
        if (b > a) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    int ans = 0;
    for (int i = k; i <= min(r, g); ++i) {
        int nr = r - i, ng = g - i, nb = b;
        int ways = fat[nr+ng+nb+i];
        ways = ways * ifat[nr] % mod;
        ways = ways * ifat[ng] % mod;
        ways = ways * ifat[nb] % mod;
        ways = ways * ifat[i] % mod;
        ways = ways * c(i, i-k) % mod;
        if (i % 2 == k % 2) ans = (ans + ways) % mod;
        else ans = (ans + mod - ways) % mod;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

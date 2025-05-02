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
    int k; cin >> k;
    string s; cin >> s;
    int n = sz(s), N = n + k;
    vector<int> fat(N+1, 1), ifat(N+1), p25(N+1, 1), p26(N+1, 1);
    for (int i = 1; i <= N; ++i) fat[i] = i * fat[i-1] % mod, p25[i] = 25 * p25[i-1] % mod, p26[i] = 26 * p26[i-1] % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat.back() = fexp(fat.back(), mod-2);
    for (int i = N-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    auto C = [&] (int a, int b) {
        if (a < b) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    int ans = 0;
    for (int i = n-1; i < n+k; ++i) {
        // em qual posicao da string vou ter o ulitmo match
        int ways = C(i, n-1) * p25[i-n+1] % mod * p26[N - i - 1] % mod;
        ans = (ans + ways) % mod;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

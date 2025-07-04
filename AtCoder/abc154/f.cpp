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
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    // quero o numero de maneiras de alcancar caras no retangulo (x1, y1), (x2, y2)
    int N = x1+x2+y1+y2;
    vector<int> fat(N, 1), ifat(N);
    for (int i = 1; i < N; ++i) fat[i] = i * fat[i-1] % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            b = b * b % mod, e /= 2;
        }
        return ans;
    };
    ifat.back() = fexp(fat.back(), mod-2);
    for (int i = N-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    auto C = [&] (int a, int b) {
        if (a < b) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };

    int cur = C(x1+y1, y1), ans = 0;

    for (int i = x1+y1; i <= x2+y2; ++i) {
        ans = (ans + cur) % mod, cur = cur * 2 % mod;
        
        if (i+1 <= x1+y2) cur = (cur + C(i, x1-1)) % mod;
        else cur = (cur + mod - C(i, y2)) % mod;

        if (i+1 <= x2+y1) cur = (cur + C(i, y1-1)) % mod;
        else cur = (cur + mod - C(i, x2)) % mod;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

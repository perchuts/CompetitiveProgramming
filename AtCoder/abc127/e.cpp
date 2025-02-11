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
    int n, m, k; cin >> n >> m >> k;
    vector<int> fat(n*m+1, 1), ifat(n*m+1);
    for (int i = 1; i <= n*m; ++i) fat[i] = fat[i-1] * i % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            b = b * b % mod, e /= 2;
        }
        return ans;
    };
    ifat.back() = fexp(fat.back(), mod-2);
    for (int i = n*m-1; ~i; --i) ifat[i] = (i + 1) * ifat[i+1] % mod;
    auto c = [&] (int a, int b) {
        if (a < b) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int c1 = i+j, c2 = i-j, c3 = -i+j, c4 = -i-j;
            c1 = c1 * (i-1) * (j-1) % mod; 
            c2 = c2 * (i-1) * (m-j) % mod;
            c3 = c3 * (n-i) * (j-1);
            c4 = c4 * (n-i) * (m-j) % mod;
            int tot = (c1+c2+c3+c4 + (j-1)*j+(i-1)*i - (m-j)*j - (n-i)*i) % mod;
            tot = (tot + mod) % mod;
            ans = (ans + tot) % mod;
        }
    }
    cout << (ans * c(n*m-2, k-2)) % mod << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

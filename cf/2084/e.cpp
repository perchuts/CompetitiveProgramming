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
    vector<int> a(n), pos(n, -1), fat(n+1, 1), ifat(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat.back() = fexp(fat.back(), mod-2);
    for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    int m = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] != -1) pos[a[i]] = i+1;
        else m++;
    }
    vector<int> ps(n+1), qnt_w(n+1);
    for (int i = 1; i <= n; ++i) ps[i] = ps[i-1] + (a[i-1] == -1);
    for (int l = 1; l <= n; ++l) for (int r = l; r <= n; ++r) qnt_w[ps[r]-ps[l-1]]++;
    int m1 = 0, lx = n+1, rx = -1, ans = 0;
    for (int i = 0; i < n; ++i) {
        if (pos[i] == -1) m1++;
        else {
            if (lx == n+1) {
                for (int a = 1; a < pos[i]; ++a) for (int b = a; b < pos[i]; ++b) qnt_w[ps[b]-ps[a-1]]--;
                for (int a = pos[i]+1; a <= n; ++a) for (int b = a; b <= n; ++b) qnt_w[ps[b]-ps[a-1]]--;
                lx = rx = pos[i];
            } else if (pos[i] < lx) {
                for (int a = pos[i]+1; a <= lx; ++a) for (int b = rx; b <= n; ++b) qnt_w[ps[b]-ps[a-1]]--;
                lx = pos[i];
            } else if (rx < pos[i]) {
                for (int a = 1; a <= lx; ++a) for (int b = rx; b < pos[i]; ++b) qnt_w[ps[b]-ps[a-1]]--;
                rx = pos[i];
            }
        }
        int ct = 0;
        for (int j = m1; j <= m; ++j) {
            int f = fat[j] * ifat[j-m1] % mod;
            ct = (ct + qnt_w[j] * f) % mod;
        }
        ans = (ans + ct * fat[m-m1]) % mod;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}

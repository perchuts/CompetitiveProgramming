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
    int n, k; cin >> n >> k;
    int kernel = 0;
    vector<int> basis(30);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        for (int j = 29; ~j; --j) {
            if (x >> j & 1) {
                if (basis[j] == 0) {
                    basis[j] = x;
                    break;
                }
                x ^= basis[j];
            }
        }
        if (!x) kernel++;
    }
    kernel = (1<<min(18LL, kernel));
    for (int i = 0; i < 30; ++i) {
        if (basis[i] == 0) continue;
        for (int j = i + 1; j < 30; ++j) {
            if (basis[j] >> i & 1) basis[j] ^= basis[i];
        }
    }
    vector<int> nbasis;
    for (int i = 0; i < 30; ++i) if (basis[i]) nbasis.pb(basis[i]);
    for (int i = 0; k; ++i) {
        int ans = 0;
        for (int w = 0; w < sz(nbasis); ++w) if (i >> w & 1) ans ^= nbasis[w];
        int go = min(kernel, k);
        for (int j = 0; j < go; ++j) cout << ans << ' ';
        k -= go;
    }
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

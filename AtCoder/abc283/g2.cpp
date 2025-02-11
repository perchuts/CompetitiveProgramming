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
    int n, l, r; cin >> n >> l >> r;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> basis(60);
    for (auto x : a) {
        for (int i = 59; ~i; --i) {
            if (x >> i & 1) {
                if (basis[i] == 0) { basis[i] = x; break; }
                x ^= basis[i];
            }
        }
    }
    for (int i = 0; i < 60; ++i) {
        for (int j = i-1; ~j; --j) {
            if (basis[i] >> j & 1) {
                if (basis[j]) basis[i] ^= basis[j];
            }
        }
    }
    vector<int> c;
    for (auto x : basis) if (x) c.pb(x);
    --l, --r;
    for (int i = l; i <= r; ++i) {
        int x = 0;
        for (int j = 0; j < sz(c); ++j) {
            if (i >> j & 1) x ^= c[j]; 
        }
        cout << x << ' ';
    }
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

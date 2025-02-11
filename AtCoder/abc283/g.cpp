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
    vector<int> a(n), basis(60), v;
    for (auto& x : a) {
        cin >> x;
        for (int i = 0; i < 60; ++i) {
            if (x >> i & 1) {
                if (basis[i] == 0) { basis[i] = x, v.pb(x); break; }
                x ^= basis[i];
            }
        }
    }
    // can check in O(logn) if a number exists
    auto contains = [&] (int x, int k) {
        // k = bit to start checking
        for (int i = k; i < 60; ++i) {
            if (x >> i & 1) {
                if (basis[i] == 0) return false;
                x ^= basis[i];
            }
        }
        return true;
    };
    // how many numbers in [0, X)?
    // how many combinations to have a prefix of xor equal to something? if we can solve this, we solved the problem
    // well, its simply  2^|null space| induced by those bits! -> only if this number exists!
    for (auto x : v) cout << x << ' ';
    auto qount = [&] (int x) {
        int tot = 0, null_space = 0;
        for (int i = 59; ~i; --i) {
            // want to check amount of
        }
        return tot;
    };
    for (int current = l; current <= r; ++current) {
        int lx = 0, rx = (1LL<<60)-1, ans;
        while (lx <= rx) {
            int md = lx + (rx-lx+1)/2;
            // open interval!
            if (qount(md) < current) ans = md, rx = md-1; 
            else lx = md+1;
        }
        cout << ans << endl; 
        current++;
    }
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

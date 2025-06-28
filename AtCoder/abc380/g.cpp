#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
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
    int n, k; cin >> n >> k;
    vector<int> p(n);
    for (auto& x : p) cin >> x, --x;
    ord_set<int> sexo;
    auto fexp = [&] (int b, int e = mod-2) {
        int x = 1;
        while (e) {
            if (e&1) x = x * b % mod;
            e /= 2, b = b * b % mod;
        }
        return x;
    };
    int tot = k*(k-1)%mod*fexp(4)%mod, w = 0, invk = fexp(n-k+1);
    for (int i = 0; i < n; ++i) {
        tot += sz(sexo) - sexo.order_of_key(p[i]);
        sexo.insert(p[i]);
    }
    sexo.clear();
    for (int i = 0; i < k; ++i) {
        w += sz(sexo) - sexo.order_of_key(p[i]);
        sexo.insert(p[i]);
    }
    tot = (tot + (mod-w)*invk) % mod;
    for (int i = k; i < n; ++i) {
        w -= sexo.order_of_key(p[i-k]);
        sexo.erase(p[i-k]);
        w += sz(sexo) - sexo.order_of_key(p[i]);
        w %= mod;
        w = (w + mod) % mod;
        sexo.insert(p[i]);
        tot = (tot + (mod-w)*invk) % mod;
    }
    cout << tot << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

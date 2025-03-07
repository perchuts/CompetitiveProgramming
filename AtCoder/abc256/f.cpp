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
    int n, q; cin >> n >> q;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    struct node {
        int suma = 0, indp = 0, sumaj = 0;
        node(){}
    } nulo;  
    vector<node> seg(4*n+10);
    int inv2 = (119<<22)+1;
    auto merge = [&] (node a, node b) {
        node c;
        c.suma = (a.suma + b.suma) % mod;
        c.indp = (a.indp + b.indp) % mod;
        c.sumaj = (a.sumaj + b.sumaj) % mod;
        return c;
    };
    // (i-j+1)*(i-j+2)/2*a[j]
    // (ii-ij+2i-ij+jj-2j+i-j+2)
    // (ii+jj-2ij+3i-3j+2)*(a[j]/2)
    // (ii+3i+2) (jj-3j) (-2ij) (a[j]/2) 
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            seg[i].suma = k;
            seg[i].indp = l*(l-3)%mod*k%mod; seg[i].indp = (seg[i].indp + mod) % mod;
            seg[i].sumaj = 2*l*k % mod;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
        if (r < x or y < l) return nulo;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return merge(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    // (ii+3i+2) (jj-3j) (-2ij) (a[j]/2) 
    for (int i = 1; i <= n; ++i) upd(upd, 1, 1, n, i, a[i]);
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int x, v; cin >> x >> v;
            upd(upd, 1, 1, n, x, v);
        } else {
            int x; cin >> x;
            node ans = query(query, 1, 1, n, 1, x);
            int resp = (ans.indp + (x*(x+3)+2)%mod*ans.suma -x*ans.sumaj) % mod;
            resp = (resp + mod) % mod;
            cout << (resp*inv2)%mod << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

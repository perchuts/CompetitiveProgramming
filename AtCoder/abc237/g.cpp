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
    int n, q, x; cin >> n >> q >> x;
    vector<int> p(n);
    for (auto& z : p) cin >> z;
    for (auto& z : p) {
        if (z < x) z = 0;
        else if (z > x) z = 1;
        else z = -69;
    }
    int pos = 0;
    for (int i = 0; i < n; ++i) if (p[i] == -69) pos = i;
    vector<int> seg(4*n), lz(4*n, -1);
    auto push = [&] (int i, int l, int r) {
        if (lz[i] == -1) return;
        seg[i] = lz[i] * (r-l+1);
        if (l != r) lz[2*i] = lz[2*i+1] = lz[i];
        lz[i] = -1;
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int y, int k) -> void {
        push(i, l, r);
        if (r < x or y < l or x > y) return;
        if (x <= l and r <= y) {
            lz[i] = k;
            push(i, l, r);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, y, k);
        self(self, 2*i+1, md+1, r, x, y, k);
        seg[i] = seg[2*i] + seg[2*i+1];
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        push(i, l, r);
        if (r < x or y < l) return 0LL;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return self(self, 2*i, l, md, x, y) + self(self, 2*i+1, md+1, r, x, y);
    };
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seg[i] = (p[l] == -69 ? 0 : p[l]);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seg[i] = seg[2*i] + seg[2*i+1];
    };
    build(build, 1, 0, n-1);
    while (q--) {
        int c, l, r; cin >> c >> l >> r;
        --l, --r;
        if (c == 1) {
            int qnt = query(query, 1, 0, n-1, l, r);
            // vou por qnt caras no fim, o resto vai ser tudo zero!
            upd(upd, 1, 0, n-1, r-qnt+1, r, 1);
            upd(upd, 1, 0, n-1, l, r-qnt, 0);
            if (l <= pos and pos <= r) pos = r - qnt; 
        } else {
            int qnt = query(query, 1, 0, n-1, l, r);
            // vou por qnt caras no fim, o resto vai ser tudo zero!
            upd(upd, 1, 0, n-1, l, l+qnt-1, 1);
            upd(upd, 1, 0, n-1, l+qnt, r, 0);
            if (l <= pos and pos <= r) pos = l + qnt; 
        }
    }
    cout << pos+1 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

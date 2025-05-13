#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    int n, q; cin >> n >> q;
    vector<int> v(n), ant(n, -1), prox(n, -1), seg(4*n, n);
    for (auto& x : v) cin >> x;
    map<int, set<int>> mp;
    auto upd = [&] (auto&& self, int i, int l, int r, int x) -> void {
        if (l == r) {
            seg[i] = (prox[l] == -1 ? n : prox[l]);
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x);
        else self(self, 2*i+1, md+1, r, x);
        seg[i] = min(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        if (r < x or y < l) return n;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return min(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    auto add = [&] (int i, int k) {
        auto it = mp[k].lower_bound(i);
        if (it != end(mp[k])) {
            prox[i] = (*it);
            ant[*it] = i;
        } else prox[i] = -1;
        if (it != begin(mp[k])) {
            it = prev(it);
            ant[i] = (*it);
            // update *it
            prox[*it] = i;
            upd(upd, 1, 0, n-1, (*it));
        } else ant[i] = -1;
        upd(upd, 1, 0, n-1, i);
        // update i
        mp[k].insert(i);
    };
    auto rem = [&] (int i, int k) {
        int a = ant[i], b = prox[i];
        if (a != -1 and b != -1) {
            // atualizar a
            prox[a] = b;
            upd(upd, 1, 0, n-1, a);
            ant[b] = a;
        } else if (a != -1) {
            prox[a] = -1;
            upd(upd, 1, 0, n-1, a);
            // atualizar a
        } else if (b != -1) {
            ant[b] = -1;
        }
        ant[i] = prox[i] = -1;
        mp[k].erase(i);
    };
    for (int i = 0; i < n; ++i) add(i, v[i]);
    while (q--) {
        int a, b, c; cin >> a >> b >> c;
        if (a == 1) {
            --b;
            rem(b, v[b]);
            v[b] = c;
            add(b, v[b]);
        } else {
            --b, --c;
            int x = query(query, 1, 0, n-1, b, c);
            cout << (x > c ? "YES" : "NO") << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

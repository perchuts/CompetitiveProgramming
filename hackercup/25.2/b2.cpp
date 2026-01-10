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

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    sort(all(a));
    vector<int> v;
    for (int l = 0, r = 0; l != n; l = r) {
        while (r != n and a[l] == a[r]) r++;
        v.pb(r-l);
    }
    reverse(all(v));
    sort(all(b)), reverse(all(b));
    // pick a suffix of v. 
    // worst make 1, then 2, 3, .... K
    int l = 0, r = n-1, ans = 0;
    vector<int> seg(4*n);
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seg[i] = v[l];
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md), self(self, 2*i+1, md+1, r);
        seg[i] = seg[2*i] + seg[2*i+1];
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            seg[i] += k;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = seg[2*i] + seg[2*i+1];
    };
    auto get = [&] (auto&& self, int i, int l, int r, int want) -> int {
        if (l == r) {
            return (seg[i] >= want ? l : l+1);
        }
        int md = (l+r)/2;
        if (seg[2*i] >= want) return self(self, 2*i, l, md, want);
        return self(self, 2*i+1, md+1, r, want-seg[2*i]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x) -> int {
        if (x < 0) return 0LL;
        if (l == r) return seg[i];
        int md = (l+r)/2;
        if (x <= md) return self(self, 2*i, l, md, x);
        return seg[2*i] + self(self, 2*i+1, md+1, r, x);
    };
    auto possible = [&] (int x) {
        int tam = x;
        int z = sz(v);
        build(build, 1, 0, z-1);
        for (auto k : b) {
            if (seg[1] == 0) break;
            int pos = get(get, 1, 0, z-1, k);
            // pos = primeira posicao cujo prefix sum eh >= k
            int A = query(query, 1, 0, z-1, pos), B = query(query, 1, 0, z-1, pos-1);
            int sobra = k - B;
            if (seg[1] == A) {
                // nao vou passar sobra pro proximo
            } else {
                upd(upd, 1, 0, z-1, pos+1, sobra);
                upd(upd, 1, 0, z-1, pos, sobra);
            }
            if (pos != 0) {
                upd(upd, 1, 0, z-1, pos, A-B);
                upd(upd, 1, 0, z-1, pos-1, B-A);
            }
        }
        return (seg[1] == 0);
    };
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md+1, l = md+1;
        else r = md-1;
    }
    int tot = 0;
    for (int i = 0; i < ans; ++i) tot += v[i];
    cout << tot << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

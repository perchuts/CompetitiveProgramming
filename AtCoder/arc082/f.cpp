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
    int X, k; cin >> X >> k;
    vector<int> r(k);
    for (auto& y : r) cin >> y;
    int q; cin >> q;
    vector<ii> qu(q);
    for (auto& [x, y] : qu) cin >> x >> y;
    vector<int> ans(q), id(q); iota(all(id), 0);
    sort(all(id), [&] (int x, int y) { return qu[x].first < qu[y].first; });
    int ptr = 0, prv = 0, lx = 0, rx = X, base = 0;
    auto get = [&] (int z) { return base + max(0LL, min(rx, z)-lx); };
    for (int i = 0; i <= k; ++i) {
        int j = ptr;
        while (j < q and (i == k or qu[id[j]].first < r[i])) j++;
        for (int w = ptr; w < j; ++w) {
            // [ptr, j)
            int cara = id[w];
            auto [tx, x] = qu[cara];
            int val = get(x);
            if (i & 1) val = min(X, val + tx - prv);
            else val = max(0LL, val - (tx - prv));
            ans[cara] = val;
        }

        if (i == k) break;
        ptr = j;
        int df = r[i] - prv;
        prv = r[i];
        if (i & 1) {
            // hora do A farmar
            // f(x) += df pra todo x
            int mxv = base + rx - lx + df;
            if (mxv <= X) {
                base += df;
                continue;
            }
            if (base + df >= X) {
                base = lx = rx = X;
                continue;
            }
            int sobra = mxv - X;
            // base + (rx-sobra-lx) = X
            // base = X - (rx-sobra-lx)
            rx -= sobra;
            base = X - rx + lx;
        } else {
            // hora do A se fuder
            int mnv = base - df;
            if (mnv >= 0) {
                base -= df;
                continue;
            }
            if (base + rx - lx - df <= 0) {
                lx = rx = X;
                base = 0;
                continue;
            }
            // vou morrer ate o cara q eh igual a df
            // df = base + p - lx
            // p = df + lx - base
            lx += df - base;
            base = 0;
        }
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
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

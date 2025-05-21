#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    vector<int> h1, h2;
    for (int i = 0; i < n; ++i) {
        if (2 * i < n) h1.pb(v[i]);
        else h2.pb(v[i]);
    }
    auto print = [&] (int m1, int m2) {
        int A = (m1&m2);
        m1 -= A, m2 -= A;
        cout << __builtin_popcountll(m1) << endl;
        for (int j = 0; j < n; ++j) {
            if (m1 >> j & 1) cout << v[j] << ' ';
        }
        cout << endl;
        cout << __builtin_popcountll(m2) << endl;
        for (int j = 0; j < n; ++j) {
            if (m2 >> j & 1) cout << v[j] << ' ';
        }
        cout << endl;
        exit(0);
    };
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            for (int k = 0; k < n; ++k) {
                if (k == j or k == i) continue;
                for (int l = 0; l < n; ++l) {
                    if (l == k or l == j or l == i) continue;
                    if (v[i] + v[j] == v[k] + v[l]) {
                        print((1LL<<i)+(1LL<<j), (1LL<<k)+(1LL<<l));
                    }
                }
            }
        }
    }
    // agr sei que tem no maximo 1 random repetido..
    auto gen = [&] (int shift, vector<int> vv) {
        vector<ii> ans;
        for (int i = 0; i < (1<<sz(vv)); ++i) {
            int s = 0;
            for (int j = 0; j < sz(vv); ++j) {
                if (i >> j & 1) s += vv[j];
            }
            ans.pb({s, i});
        }
        sort(all(ans));
        for (int i = 1; i < sz(ans); ++i) if (ans[i].first == ans[i-1].first and max(__builtin_popcountll(ans[i].second), __builtin_popcountll(ans[i-1].second)) > 1) print(ans[i].second<<shift, ans[i-1].second<<shift);
        return ans;
    };
    auto a = gen(0, h1);
    auto b = gen(sz(h1), h2);
    // retirar repeticoes
    auto calc = [&] (int x) { 
        int i = 0, j = sz(b)-1, tot = 0;
        while (i != sz(a)) {
            while (j >= 0 and b[j].first + a[i].first > x) --j;
            if (j == -1) break;
            tot += j + 1, ++i;
        }
        map<int, int> foi;
        for (auto y : v) {
            if (y > x) continue;
            if (foi[y]) tot--;
            foi[y] = 1;
        }
        return tot;
    };
    int l = 0, lst = 0;
    for (int i = n-1; ~i; --i) {
        int k = calc(l+(1LL<<i))-1;
        int aqui = k-lst;
        if (aqui <= (1LL<<i)) lst = k, l += (1LL<<i);
    }
    l++;
    int i = 0, j = sz(b)-1;
    vector<int> masks;
    while (i != sz(a)) {
        while (j >= 0 and b[j].first + a[i].first > l) --j;
        if (j == -1) break;
        if (b[j].first + a[i].first == l) {
            int m = a[i].second + (b[j].second<<sz(h1));
            masks.pb(m);
        }
        i++;
    }
    for (i = 0; i < sz(masks); ++i) {
        for (j = i+1; j < sz(masks); ++j) {
            int x = masks[i], y = masks[j];
            int z = x&y;
            x -= z, y -= z;
            if (__builtin_popcount(x) == 1 and __builtin_popcount(y) == 1) continue;
            print(x, y);
        }
    }
    cout << "IMPOSSIBLE" << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

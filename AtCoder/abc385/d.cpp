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
    int n, m, cx, cy; cin >> n >> m >> cx >> cy;
    vector<ii> v(n);
    vector<int> foi(n);
    map<int, set<ii>> X, Y;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        X[x].insert({y, i});
        Y[y].insert({x, i});
    }
    for (int i = 0; i < m; ++i) {
        char c; cin >> c;
        int k; cin >> k;
        if (c == 'L') {
            cx -= k;
            auto it = Y[cy].lower_bound({cx, -1});
            while (it != end(Y[cy])) {
                auto [a, b] = *it;
                if (a > cx+k) break;
                foi[b] = 1;
                it = next(it);
                Y[cy].erase({a, b});
            }
        } else if (c == 'R') {
            auto it = Y[cy].lower_bound({cx, -1});
            while (it != end(Y[cy])) {
                auto [a, b] = *it;
                if (a > cx+k) break;
                foi[b] = 1;
                it = next(it);
                Y[cy].erase({a, b});
            }
            cx += k;
        } else if (c == 'D') {
            cy -= k;
            auto it = X[cx].lower_bound({cy, -1});
            while (it != end(X[cx])) {
                auto [a, b] = *it;
                if (a > cy+k) break;
                foi[b] = 1;
                it = next(it);
                X[cx].erase({a, b});
            }
        } else {
            auto it = X[cx].lower_bound({cy, -1});
            while (it != end(X[cx])) {
                auto [a, b] = *it;
                if (a > cy+k) break;
                foi[b] = 1;
                it = next(it);
                X[cx].erase({a, b});
            }
            cy += k;
        }
    }
    int tot = 0;
    for (int i = 0; i < n; ++i) tot += foi[i];
    cout << cx << ' ' << cy << ' ' << tot << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

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
    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x;
    int inv = 0;
    for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j) {
        if (p[i] > p[j]) inv++;
    }
    if (inv&1) {
        cout << "No" << endl;
        exit(0);
    }
    vector<ii> ops;
    auto op = [&] (int i, int j) {
        ops.pb({i+1, j});
        vector<int> novo;
        for (int k = 0; k < n; ++k) if (k != i and k != i+1) novo.pb(p[k]);
        vector<int> novo2;
        for (int k = 0; k < j; ++k) novo2.pb(novo[k]);
        novo2.pb(p[i]);
        novo2.pb(p[i+1]);
        for (int k = j; k < n-2; ++k) novo2.pb(novo[k]);
        swap(p, novo2);
    };
    cout << "Yes" << endl;
    for (int i = 0; i < n; ++i) {
        int pos = -1;
        for (int j = i; j < n; ++j) {
            if (p[j] == i+1) {
                pos = j; break;
            }
        }
        assert(pos != -1);
        if (pos == i) continue;
        if (pos == n-1) {
            assert(i != n-2);
            op(n-2, n-3);
            pos--;
        }
        if (pos != i) op(pos, i);
    }
    cout << sz(ops) << endl;
    for (auto [x, y] : ops) cout << x << ' ' << y << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

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
    vector<int> a(n), b(n), oa(n+1), ob(n+1);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    for (int i = 0; i < n; ++i) oa[a[i]] = i, ob[b[i]] = i;
    int fixo = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] == b[i]) {
            if (fixo != -1) {
                cout << -1 << endl;
                return;
            }
            fixo = i;
        }
    }
    vector<ii> ops;
    auto apply = [&] (int i, int j) {
        if (i == j) return;
        swap(oa[a[i]], oa[a[j]]);
        swap(ob[b[i]], ob[b[j]]);
        swap(a[i], a[j]), swap(b[i], b[j]);
        ops.pb({i+1, j+1});
    };
    for (int i = 0; i < n; ++i) {
        int parzinho = b[i];
        int onde = ob[a[i]];
        if (a[onde] != b[i]) {
            cout << -1 << endl;
            return;
        }
    }
    if (fixo != -1) {
        if (n % 2 == 0) {
            cout << -1 << endl;
            return;
        }
        if (fixo != n/2) apply(fixo, n/2);
    } else if (n % 2 == 1) {
        cout << -1 << endl;
        return;
    }
    for (int i = 0; i < n/2; ++i) apply(ob[a[i]], n-1-i);
    reverse(all(a));
    assert(a == b);
    cout << sz(ops) << endl;
    for (auto [x, y] : ops) cout << x << ' ' << y << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}

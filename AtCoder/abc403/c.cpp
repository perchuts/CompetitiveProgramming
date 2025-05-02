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
    int n, m, q; cin >> n >> m >> q;
    set<int> adm;
    map<ii, bool> nice;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int x, y; cin >> x >> y;
            nice[{x, y}] = 1;
        } else if (op == 2) {
            int x; cin >> x;
            adm.insert(x);
        } else {
            int x, y; cin >> x >> y;
            cout << (nice[{x, y}] == 1 or adm.find(x) != end(adm) ? "Yes" : "No") << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

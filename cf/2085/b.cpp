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
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    if (v[0] == 0 and v.back() == 0) {
        cout << 3 << endl;
        cout << 1 << ' ' << n-2 << endl;
        cout << 2 << ' ' << 3 << endl;
        cout << 1 << ' ' << 2 << endl;
    } else {
        int prim = -1, lst = -1;
        for (int i = 0; i < n; ++i) {
            if (v[i] == 0) {
                if (prim == -1) prim = i+1;
                lst = i+1;
            }
        }
        if (prim == -1) {
            cout << 1 << endl;
            cout << 1 << ' ' << n << endl;
        } else if (prim != 1) {
            cout << 2 << endl;
            cout << 2 << ' ' << n << endl;
            cout << 1 << ' ' << 2 << endl;
        } else {
            assert(lst != n);
            cout << 2 << endl;
            cout << 1 << ' ' << n-1 << endl;
            cout << 1 << ' ' << 2 << endl;
        }
    }
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}

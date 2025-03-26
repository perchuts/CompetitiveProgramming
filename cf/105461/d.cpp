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
    vector<tuple<int, int, int>> op;
    int qnt = 1, id = 1;
    enum {
        SHIFT_R,
        SHIFT_L,
        ORR,
        XORR,
    };
    while (qnt < n) {
        op.pb({id-1, SHIFT_R, qnt});
        id++;
        op.pb({id-1, ORR, id-2});
        id++;
        qnt *= 2;
    }
    op.pb({id-1, SHIFT_R, 1});
    id++;
    op.pb({id-1, XORR, id-2});
    cout << sz(op) << endl;
    int i = 1;
    for (auto [x, y, z] : op) {
        cout << "B" << i++ << " = " << "B" << x;
        if (y == SHIFT_R) cout << " << ";
        if (y == SHIFT_L) cout << " >> ";
        if (y == XORR) cout << " ^ ";
        if (y == ORR) cout << " | ";
        if (y == SHIFT_R or y == SHIFT_L) {
            cout << z << endl;
        } else cout << "B" << z << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

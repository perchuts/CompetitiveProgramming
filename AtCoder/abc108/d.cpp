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
    int l; cin >> l;
    --l;
    if (l == 1) {
        cout << "2 2" << endl;
        cout << "1 2 0" << endl;
        cout << "1 2 1" << endl;
        exit(0);
    }
    int pot = 0;
    while ((2 << pot) <= l) pot++;
    int N = pot+1;
    vector<iii> edg;
    for (int i = 0; i < pot; ++i) {
        edg.pb({i, i+1, (1<<(pot-i-1))});
        edg.pb({i, i+1, 0});
    }
    int val = (1 << pot);
    for (int i = pot-1; ~i; --i) {
        if (l >> i & 1) {
            edg.pb({0, pot-i, val});
            val += (1 << i);
        }
    }
    edg.pb({0, N-1, l});
    cout << N << " " << sz(edg) << endl;
    for (auto [x, y, z] : edg) cout << x+1 << ' ' << y+1 << ' ' << z << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

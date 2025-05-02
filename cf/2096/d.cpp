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
    map<int, int> d1, d2;
    vector<ii> pos(n);
    int s1 = 0, s2 = 0;
    for (auto& [x, y] : pos) {
        cin >> x >> y;
        d1[x]++;
        d2[x+y]++;
    }
    int a = -1e18, b = -1e18;
    for (auto [x, y] : d1) {
        if (y&1) {
            assert(a == -1e18);
            a = x;
        }
    }
    for (auto [x, y] : d2) {
        if (y&1) {
            assert(b == -1e18);
            b = x;
        }
    }
    assert(min(a, b) != -1e18);
    int x = a;
    int y = b-x;
    cout << x << ' ' << y << endl;
    cout.flush();
}

int32_t main(){_
    int t; cin >> t;
    while (t--) solve();
}

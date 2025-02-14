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
    int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
    int x3, y3, x4, y4;
    int dx = x2-x1, dy = y2-y1;
    int dx2 = -dy, dy2 = dx;
    x3 = x2+dx2, y3 = y2+dy2;
    int dx3 = -dy2, dy3 = dx2;
    x4 = x3+dx3, y4 = y3+dy3;
    cout << x3 << ' ' << y3 << ' ' << x4 << ' ' << y4 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

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
int knightDistance ( int nx , int ny , int kx , int ky , int cx , int cy ) {
    int x = abs ( cx - kx ) , y = abs ( cy - ky ) ;
    if ( x < y )
        swap (x , y ) , swap ( nx , ny ) , swap ( cx , cy ) , swap ( kx , ky ) ;
    if ( x == 1 && y == 0)
        return 3;
    if ( x == 2 && y == 2)
        return 4;
    if ( x == 1 && y == 1 && ((( cx == 0 || cx == nx - 1) && ( cy == 0 ||
        cy == ny - 1) ) || (( kx == 0 || kx == nx - 1) && ( ky == 0 || ky
        == ny - 1) ) ) )
        return 4;
    int steps = max (( x + y + 2) / 3 , ( x + 1) / 2) ;
    return steps + (( x + y + steps ) % 2) ;
}
void solve(){
    int x, y; cin >> x >> y;
    --x, --y;
    cout << knightDistance(2e9, 2e9, x, y, 0, 0) << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}

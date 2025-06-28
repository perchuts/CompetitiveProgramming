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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
    int n, m; cin >> n >> m;
    // se tiver um p = 3k+2 com vp = impar, fizemos o W
    // se tiver um p = 3k+1 com vp = 3k+2, fizemos o W tambem
    // N da errado <=>
    // N = 3^p * a^2 * b^3 * c
    // a = product of primes === 2 mod 3
    // b = product of primes === 1 mod 3
    // c = square free product of primes === 1 mod 3
    // N^(5/6)
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

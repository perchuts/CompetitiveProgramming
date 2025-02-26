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

int solve(int x){
    if (x < 7) return -1;
    if (__builtin_popcountll(x) >= 3) {
        int ans = 0, falta = 3;
        for (int i = 59; ~i and falta; --i) {
            if (x >> i & 1) falta--, ans += (1LL << i);
        }
        return ans;
    }
    if (__builtin_popcountll(x) == 1) return (x/2) + (x/4) + (x/8);
    assert(x >= 8);
    int bit1 = 0, bit2 = 0;
    for (int i = 59; ~i; --i) {
        if (x >> i & 1) {
            if (bit1 == 0) bit1 = (1LL << i);
            else bit2 = (1LL << i);
        }
    }
    int ans = (bit1/2) + (bit1/4) + (bit1/8);
    if (bit2 >= 4) ans = bit1 + (bit2/2) + (bit2/4);
    assert(ans <= x);
    return ans;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) {
        int x; cin >> x;
        cout << solve(x) << endl;
    }
}

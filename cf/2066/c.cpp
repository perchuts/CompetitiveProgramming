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
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // notice the following: 
    // for each transition, we must have
    // 1. f(i, x, x, x), where x = a[0]^a[1]^...^a[i]
    // 2. f(i, y, y, x), where y \ne x is arbitrary.
    // case 1: anything is possible, but this only gives 1 transition.
    // case 2.1: a[i] = x^y. this case gives (i+1, y, x, x), (i+1, y, y, y)
    // case 2.1: a[i] != x^y. forced transition: (i+1, y, y, x^a[i])
    // so we can "ignore" all states in which y != x^a[i], and only worry about (i, x, x, x) and (i, x^a[i], x^a[i], x)
    // dp1(pos, y)
    // dp2(x) -> soh tem uma opcao por node
    map<ii, int> dp1;
    int dp2 = 1, xx = 0;
    for (auto ai : a) {
        int y = xx ^ ai;
        int ndp2 = (dp1[{0, y}] + dp1[{1, y}] + dp1[{2, y}]) % mod;
        for (int i = 0; i < 3; ++i) {
            int val = dp2;
            for (int j = 0; j < 3; ++j) {
                if (i == j) continue;
                val += dp1[{j, y}];
            }
            dp1[{i, xx}] = val % mod;
        }
        dp1[{0, y}] = 0;
        dp1[{1, y}] = 0;
        dp1[{2, y}] = 0;
        xx = y;
        dp2 = ndp2;
    }
    int ans = dp2;
    for (auto [x, y] : dp1) ans = (ans + y) % mod;
    cout << ans << endl;
    // for all y != x^a[i], dp1_{i+1}(pos, y) = dp1_i(pos, y)
    //         y  = x^a[i]: dp1_{i+1}(pos, y) = 0, dp1_{i+1}(pos, x) = dp2_i + dp1_i(y, nao_eh_pos)
    //
    //         dp2 -> soh tem um estado possivel! que eh xor de tudo....
    //         y = x^a[i]: dp2_{i+1} = dp1_i(0, y) + dp1_i(1, y) + dp1_i(2, y)
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}

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
    // pra todo primo p, vou ter arestas 1 -- p-1
    // 2 -- p-2
    // 3 -- p-3
    // p/2 -- p/2+1
    int n; cin >> n;
    vector<int> a, b;
    vector<int> primes;
    for (int i = 2; i < 2*n; ++i) {
        bool ok = true;
        for (int j = 2; j * j <= i; ++j) {
            if (i % j == 0) {
                ok = false;
                break;
            }
        }
        if (ok) primes.pb(i);
    }
    if (n&1) a.pb(1), b.pb(1);
    auto solve = [&] (auto&& self, int k) -> void {
        if (k <= 1) return;
        int x = lower_bound(all(primes), k+1) - begin(primes);
        x = primes[x];
        int nx = x-n-1;
        for (int i = x-k; i <= k; ++i) a.pb(i), b.pb(x-i);
        self(self, nx);
    };
    solve(solve, n);
    for (auto x : a) cout << x << ' ';
    cout << endl;
    for (auto x : b) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

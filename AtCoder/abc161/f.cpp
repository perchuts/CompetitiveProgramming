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
    auto solve = [&] (int n, int N) {
        if (n == 1) return 0LL;
        int ans = 1;
        auto test = [&] (int k) {
            int cur = N;
            while (cur % k == 0) cur /= k;
            if (cur % k == 1) ans++;
        };
        for (int i = 2; i*i <= n; ++i) {
            if (n % i) continue;
            test(i);
            if (i * i != n) test(n/i);
        }
        return ans;
    };
    int n; cin >> n;
    cout << solve(n, n) + solve(n-1, n) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

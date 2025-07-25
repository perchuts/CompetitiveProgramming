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
    int n, M; cin >> n >> M;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % M;
            e /= 2, b = b * b % M;
        }
        return ans;
    };
    int ways = 1;
    int ans2 = 0;
    for (int m = 1; m < n; ++m) {
        ways = ways * (n-m) % M;
        int t = fexp(n, n-m-1);
        int sexo = m * (m+1) / 2 % M;
        ans2 = (ans2 + sexo * t % M * ways) % M;
    }
    ans2 = ans2 * n % M;
    cout << ans2 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

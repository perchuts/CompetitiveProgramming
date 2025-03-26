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
    vector<int> h(n);
    for (auto& x : h) cin >> x;
    vector<int> dp(n+1), ps(n+1);
    dp[1] = ps[1] = 1;
    for (int i = 2; i <= n; ++i) {
        vector<int> ndp(n+1), nps(n+1);
        for (int j = 1; j <= i; ++j) {
            // vou colocar o elemento atual nessa posicao
            if (h[i-1] == h[i-2]) {
                ndp[j] = ps[i-1];
            } else if (h[i-1] > h[i-2]) {
                // preciso ficar antes do h[i-2]
                ndp[j] = (ps[i-1] - ps[j-1] + mod) % mod;
            } else {
                // preciso ficar depois do h[i-2]
                ndp[j] = ps[j-1];
            }
            nps[j] = (nps[j-1] + ndp[j]) % mod;
        }
        swap(dp, ndp), swap(ps, nps);
    }
    cout << ps[n] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

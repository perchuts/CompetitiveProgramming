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
    int n; cin >> n; n *= 2;
    string s; cin >> s;
    int shift = n+2;
    vector<int> dp(2*n+10), freq(2*n+10);
    freq[shift] = 1;
    for (int i = 1; i <= n; ++i) {
        vector<int> ndp(2*n+10), nfreq(2*n+10);
        for (int j = -i; j <= i; ++j) {
            if (s[i-1] != '+') {
                ndp[shift+j] = (ndp[shift+j] + abs(j+1) * freq[shift+j+1] + dp[shift+j+1]) % mod;
                nfreq[shift+j] = (nfreq[shift+j] + freq[shift+j+1]) % mod;
            }
            if (s[i-1] != '-') {
                ndp[shift+j] = (ndp[shift+j] + abs(j-1) * freq[shift+j-1] + dp[shift+j-1]) % mod;
                nfreq[shift+j] = (nfreq[shift+j] + freq[shift+j-1]) % mod;
            }
        }
        swap(dp, ndp);
        swap(freq, nfreq);
    }
    cout << dp[shift] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

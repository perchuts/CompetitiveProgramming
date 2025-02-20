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
    string s1, s2; cin >> s1 >> s2;
    vector<vector<int>> dp(4, vector<int>(4));
    dp[3][3] = 1;
    for (int i = 0; i < n; ++i) {
        vector<vector<int>> ndp(4, vector<int>(4));
        if (s1[i] == s2[i]) {
            for (int eu = 0; eu < 3; ++eu) {
                for (int val1 = 0; val1 <= 3; ++val1) {
                    for (int val2 = 0; val2 <= 3; ++val2) {
                        if (val1 == eu or val2 == eu) continue;
                        ndp[eu][eu] = (ndp[eu][eu] + dp[val1][val2]) % mod;
                    }
                }
            }
        } else {

            for (int eu1 = 0; eu1 < 3; ++eu1) {
                for (int eu2 = 0; eu2 < 3; ++eu2) {
                    if (eu1 == eu2) continue;
                    for (int val1 = 0; val1 <= 3; ++val1) {
                        for (int val2 = 0; val2 <= 3; ++val2) {
                            if (eu1 == val1 or eu2 == val2) continue;
                            ndp[eu1][eu2] = (ndp[eu1][eu2] + dp[val1][val2]) % mod;
                        }
                    }
                }
            }
            i++;
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) ans = (ans + dp[i][j]) % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

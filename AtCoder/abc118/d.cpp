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
    vector<int> use = {0, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    int n, m; cin >> n >> m;
    vector<int> a(m);
    for (auto& x : a) cin >> x;
    vector<string> dp;
    for (int i = 0; i <= 20; ++i) dp.pb("");
    vector<int> can(25);
    can[0] = 1;
    for (int i = 2; i <= 20; ++i) {
        for (auto x : a) {
            int j = use[x];
            if (i >= j) {
                if (can[i-j]) {
                    if (can[i] == 0) {
                        can[i] = 1;
                        dp[i] = dp[i-j] + char('0'+x);
                    } else {
                        ckmax(dp[i], dp[i-j] + char('0'+x));
                    }
                }
            }
        }
    }
    ii best = {100, -1};
    for (auto x : a) ckmin(best, make_pair(use[x], -x)); 
    string ans = "", ss;
    int copies = max(0LL, n/best.first - 6);
    for (int i = 0; i < copies; ++i) ss += char('0'-best.second);
    n -= best.first * copies;
    auto f = [&] (auto&& self, string x, string y, int falta) -> void {
        if (falta == 0) {
            if (ans.empty()) ans = y+x;
            else {
                string t = y+x;
                if (sz(ans) == sz(t)) ckmax(ans, t);
                else if (sz(ans) < sz(t)) ans = t;
            }
            return;
        }
        for (auto z : a) {
            if (use[z] <= falta) {
                self(self, x, y + char('0'+z), falta-use[z]);
                self(self, x + char('0'+z), y, falta-use[z]);
            }
        }
    };
    f(f, ss, "", n);
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}


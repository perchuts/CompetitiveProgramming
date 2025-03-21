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
    int n, m, a, b; cin >> n >> m >> a >> b;
    vector<ii> intr(m);
    for (auto& [l, r] : intr) {
        cin >> l >> r;
        if (r-l+1 >= b) {
            cout << "No" << endl;
            return;
        }
    }
    if (a == b) {
        int x = 1, ok = 1;
        if (x % a != n % a) ok = 0;
        for (auto [l, r] : intr) {
            x += (l-1-x)/a * a;
            if (x + a <= r) { ok = 0; break; }
            x += a;
        }
        cout << (ok ? "Yes" : "No") << endl;
        return;
    }
    deque<int> dp(b+1);
    dp[0] = 1;
    int x = 1, ans = 0, B = b*b;
    intr.pb({n, n});
    for (auto [l, r] : intr) {
        if (l-1-x <= B) {
            for (; x < l-1; ++x) {
                int k = 0;
                for (int i = a; i <= b; ++i) {
                    k |= dp[i-1];
                    if (k) break;
                }
                dp.push_front(k);
                dp.pop_back();
            }
        } else {
            bool ok = 0;
            for (int i = 0; i < b; ++i) ok |= dp[i];
            if (!ok) {
                cout << "No" << endl;
                return;
            }
            for (int i = 0; i <= b; ++i) dp[i] = 1;
            x = l-1;
        }
        if (l == n) for (int i = a; i <= b; ++i) ans |= dp[i-1]; 
        for (; x < r; ++x) dp.push_front(0), dp.pop_back();
    }
    cout << (ans ? "Yes" : "No") << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 2e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int tr[maxn*30][3];

void solve(){
    int n, q; cin >> n >> q;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    vector<int> xx(n+2);
    for (int i = n; i >= 1; --i) xx[i] = xx[i+1] ^ v[i-1];
    int h = 1;
    for (int i = 1; i <= n; ++i) {
        int cur = 0;
        for (int j = 29; ~j; --j) {
            // quero me fuder aqui!
            int ele = (xx[i+1] >> j & 1);
            int eu =  (v[i-1] >> j & 1);
            int target = ele ^ eu;
            if (eu) {
                if (tr[cur][!target] == 0) tr[cur][!target] = h++;
                tr[tr[cur][!target]][2] = i;
            }
            if (tr[cur][target] == 0) tr[cur][target] = h++;
            cur = tr[cur][target];
        }
    }
    while (q--) {
        int x; cin >> x;
        int cur = 0, ans = 0;
        for (int i = 29; ~i; --i) {
            if (x >> i & 1) {
                if (tr[cur][1] == 0) break;
                cur = tr[cur][1];
            } else {
                if (tr[cur][0] == 0) break;
                cur = tr[cur][0];
            }
            ckmax(ans, tr[cur][2]);
        }
        cout << n - ans << ' ';
    }
    cout << endl;
    for (int i = 0; i <= h; ++i) tr[i][0] = tr[i][1] = tr[i][2] = 0;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}

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
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> a[i][j];
    if (n == 1) {
        cout << a[0][0] % m << endl;
        exit(0);
    }
    vector<vector<vector<int>>> left(n, vector<vector<int>>(n, vector<int>())), right = left;
    auto go = [&] (auto&& self, int i, int j, int parar, string cur) -> void {
        char c = char('0'+a[i][j]);
        cur += c;
        if (i + j == parar) {
            int k = 0;
            for (auto x : cur) k = (10 * k + x - '0') % m;
            left[i][j].pb(k);
            return;
        }
        if (i+1 < n) self(self, i+1, j, parar, cur);
        if (j+1 < n) self(self, i, j+1, parar, cur);
    };
    go(go, 0, 0, n-1, "");
    auto go2 = [&] (auto&& self, int i, int j, int parar, string cur) -> void {
        if (i + j == parar) {
            int k = 0;
            reverse(all(cur));
            for (auto x : cur) k = (10 * k + x - '0') % m;
            right[i][j].pb(k);
            return;
        }
        char c = char('0'+a[i][j]);
        if (i-1 >= 0) self(self, i-1, j, parar, cur+c);
        if (j-1 >= 0) self(self, i, j-1, parar, cur+c);
    };
    go2(go2, n-1, n-1, n-1, "");
    int pot = 1;
    for (int i = 0; i < n-1; ++i) pot = 10 * pot % m;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = n-i-1;
        for (auto& x : left[i][j]) x = (x%m * pot) % m;
        for (auto& x : right[i][j]) x %= m;
        sort(all(left[i][j]));
        sort(all(right[i][j]));
        for (auto x : right[i][j]) {
            x %= m;
            ckmax(ans, (x + left[i][j].back()) % m);
            int id = lower_bound(all(left[i][j]), m - x) - begin(left[i][j]) - 1;
            if (id >= 0) ckmax(ans, x + left[i][j][id]);
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

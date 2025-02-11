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
    vector<string> v(n);
    for (auto& x : v) cin >> x;
    const int Q = 10;
    vector<int> mods(Q);
    for (auto& x : mods) x = rnd(1e8, 1e9);
    map<vector<int>, int> mp;
    vector<vector<int>> h(n, vector<int>(Q));
    for (int i = 0; i < n; ++i) {
        reverse(all(v[i]));
        vector<int> cur(Q, 1);
        for (auto x : v[i]) {
            for (int j = 0; j < Q; ++j) {
                h[i][j] = (h[i][j] + (x-'0') * cur[j]) % mods[j];
                cur[j] = (10 * cur[j]) % mods[j];
            }
        }
        mp[h[i]]++;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            vector<int> c = h[i];
            for (int k = 0; k < Q; ++k) c[k] = c[k] * h[j][k] % mods[k];
            ans += mp[c];
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

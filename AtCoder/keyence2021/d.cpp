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
    auto solve = [] (auto&& self, int n) -> vector<vector<int>> {
        if (n == 1) return {{0, 1}};
        auto partial = self(self, n-1);
        vector<vector<int>> ans;
        vector<int> same(1<<n);
        for (auto x : partial) {
            vector<int> v;
            for (auto y : x) v.pb(y), v.pb(y);
            for (int i = 1; i < (1<<n); ++i) same[i] += (v[i] == v[0]);
            ans.pb(v);
        }
        for (int i = 0; i < (1 << (n-1)) - 1; ++i) {
            vector<int> v;
            for (int j = 0; j < (1 << (n-1)); ++j) {
                int x = __builtin_popcount(j ^ i) & 1;
                v.pb(partial[i][j] ^ x), v.pb(partial[i][j] ^ x ^ 1);
            }
            for (int i = 1; i < (1<<n); ++i) same[i] += (v[i] == v[0]);
            ans.pb(v);
        }
        vector<int> v = {0};
        for (int i = 1; i < (1 << n); ++i) v.pb(same[i]==(1<<(n-1))-1);
        ans.pb(v);
        return ans;
    };
    string sexo = "AB";
    auto ans = solve(solve, n);
    cout << (1 << n) - 1 << endl;
    for (auto x : ans) {
        for (auto y : x) cout << sexo[y];
        cout << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

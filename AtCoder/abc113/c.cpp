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
    vector<string> ans(m);
    vector<int> p(m), y(m);
    vector<vector<ii>> sexo(n+1);
    for (int i = 0; i < m; ++i) cin >> p[i] >> y[i], sexo[p[i]].pb({y[i], i});
    for (int i = 1; i <= n; ++i) {
        sort(all(sexo[i]));
        string s = to_string(i);
        reverse(all(s));
        while (sz(s) != 6) s += '0';
        reverse(all(s));
        int id = 1;
        for (auto [a, b] : sexo[i]) {
            string t = to_string(id);
            reverse(all(t));
            while (sz(t) != 6) t += '0';
            reverse(all(t));
            ans[b] = s + t;
            ++id;
        }
    }
    for (auto x : ans) cout << x << endl;
    
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

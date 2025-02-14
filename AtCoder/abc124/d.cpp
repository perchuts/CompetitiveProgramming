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
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for (auto& x : v) {
        char c; cin >> c;
        x = (c == '0');
    }
    vector<int> comps(n+1);
    comps[1] = v[0];
    int ans = 1;
    for (int i = 2; i <= n; ++i) {
        comps[i] = comps[i-1];
        if (v[i-1] == 1 and v[i-2] == 0) comps[i]++;
        auto get_comps = [&] (int l, int r) {
            int resp = comps[r] - comps[l-1];
            if (l != 1 and v[l-1] == 1 and v[l-2] == 1) resp++;
            return resp;
        };
        int l = 1, r = i-1;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (get_comps(md, i) <= k) ckmax(ans, i-md+1), r = md-1;
            else l = md+1;
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

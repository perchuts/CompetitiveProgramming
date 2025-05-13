#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    auto ask = [&] (int i, int j) {
        cout << "? " << i << ' ' << j << endl;
        string s; cin >> s;
        return (s == "YES");
    };
    vector<int> p(n); iota(all(p), 1);
    auto merge_sort = [&] (auto&& self, int l, int r) -> void {
        if (l == r) return;
        int md = (l+r)/2;
        self(self, l, md), self(self, md+1, r);
        vector<int> np;
        int i = l, j = md+1;
        while (i <= md and j <= r) {
            if (ask(p[i], p[j])) np.pb(p[i++]);
            else np.pb(p[j++]);
        }
        while (i <= md) np.pb(p[i++]);
        while (j <= r) np.pb(p[j++]);
        for (int k = l; k <= r; ++k) p[k] = np[k-l];
    };
    merge_sort(merge_sort, 0, n-1);
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) ans[p[i]-1] = i+1;
    cout << "! ";
    for (auto x : ans) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

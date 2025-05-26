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
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> ans(n);
    vector<ii> sexo;
    for (int i = 0; i < 2*n; ++i) {
        sexo.pb({a[i%n] - k*i, i});
    }
    sort(all(sexo));
    set<int> caras;
    for (int l = 0, r = 0; l != sz(sexo); l = r) {
        vector<ii> temp;
        while (r != sz(sexo) and sexo[r].first == sexo[l].first) temp.pb(sexo[r++]);
        for (auto [x, y] : temp) {
            if (y < n) {
                auto it = caras.lower_bound(y);
                if (it == end(caras)) ans[y] = (y+1);
                else ans[y] = ((*it)%n+1);
            }
        }
        for (auto [x, y] : temp) caras.insert(y);
    }
    for (auto x : ans) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

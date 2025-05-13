#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
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
    for (auto& x : v) cin >> x;
    ord_set<ii> s;
    int ans = 0;
    auto add = [&] (int x, int id) {
        int larger = sz(s) - s.order_of_key(pair(x, inf));
        ans += larger;
        s.insert({x, id});
    };
    auto rem = [&] (int x, int id) {
        int smaller = s.order_of_key(pair(x-1, inf));
        ans -= smaller;
        s.erase({x, id});
    };
    for (int i = 0; i < k; ++i) add(v[i], i);
    cout << ans << ' ';
    for (int i = k; i < n; ++i) {
        add(v[i], i);
        rem(v[i-k], i-k);
        cout << ans << ' ';
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

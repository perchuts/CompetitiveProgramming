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
    int n, m, k; cin >> n >> m >> k;
    vector<ii> oo(k);
    vector<int> mnr(n+1, m+1), mnc(m+1, n+1);
    for (auto& [x, y] : oo) cin >> x >> y, ckmin(mnr[x], y), ckmin(mnc[y], x);
    int ans = 0;
    for (int i = 1; i < mnc[1]; ++i) ans += mnr[i]-1;
    vector<int> ord(m); iota(all(ord), 1);
    sort(all(ord), [&] (int x, int y) { return mnc[x] < mnc[y]; });
    int ptr = 1;
    ord_set<ii> s;
    for (auto i : ord) {
        if (i >= mnr[1]) continue;
        while (ptr < mnc[i]) {
			if (ptr < mnc[1]) s.insert({mnr[ptr], ptr});
			ptr++;
		}
        ans += mnc[i]-1;
        ans -= sz(s) - s.order_of_key({i, inf});
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

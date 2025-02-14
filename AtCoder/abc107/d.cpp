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
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int l = 1, r = 1e9, ans = 1e9, want = (n+1)*n/2;
    want = want/2+1;
    auto qnt = [&] (int k) {
        ord_set<ii> sexo;
        int p = 0, qq = 0, z = 0;
        sexo.insert({0, -1});
        for (auto x : a) {
            qq++;
            int val = (x <= k ? 1 : -1);
            p += val;
            z += sexo.order_of_key(make_pair(p-1, qq+1));
            sexo.insert({p, qq});
        }
        return z;
    };
    while (l <= r) {
        int md = (l+r)/2;
        if (qnt(md) >= want) ans = md, r = md-1;
        else l = md+1;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

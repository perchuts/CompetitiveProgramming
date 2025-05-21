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
const int maxn = 5e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
const int MAX = maxn;
namespace seg {
	ll seg[4*MAX], lazy[4*MAX];
	int n;
vector<int> v;

	ll build(int p=1, int l=0, int r=n-1) {
		lazy[p] = 0;
		if (l == r) return seg[p] = v[l];
		int m = (l+r)/2;
		return seg[p] = max(build(2*p, l, m), build(2*p+1, m+1, r));
	}
	void build(int n2, vector<int> v2) {
		n = n2, v = v2;
		build();
	}
	void prop(int p, int l, int r) {
		seg[p] += lazy[p];
		if (l != r) lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
ii query(int p=1, int l=0, int r=n-1) {
    prop(p, l, r);
    if (l == r) return {l, seg[p]};
    int md = (l+r)/2;
    prop(2*p, l, md);
    prop(2*p, md+1, r);
    if (seg[2*p] >= 0) return query(2*p, l, md);
    return query(2*p+1, md+1, r);
}
ll update(int a, int b, int x, int p=1, int l=0, int r=n-1) {
    prop(p, l, r);
    if (a <= l and r <= b) {
        lazy[p] += x;
        prop(p, l, r);
        return seg[p];
    }
    if (b < l or r < a) return seg[p];
    int m = (l+r)/2;
    return seg[p] = max(update(a, b, x, 2*p, l, m),
    update(a, b, x, 2*p+1, m+1, r));
}
};

void solve(){
    int n, b, q; cin >> n >> b >> q;
    vector<int> v(n), val(n);
    for (auto& x : v) cin >> x;
    val = v;
    for (int i = 0; i < n; ++i) {
        if (i) v[i] += v[i-1];
        v[i] -= b;
    }
    seg::build(n, v);
    while (q--) {
        int x, y; cin >> x >> y;
        --x;
        seg::update(x, n-1, y - val[x]);
        val[x] = y;
        auto [pos, tot] = seg::query();
        double ans = (tot + (pos+1) * b)/(double)(pos+1);
        cout << fixed << setprecision(11) << ans << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

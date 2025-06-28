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
// SegTree Persistente
//
// SegTree de soma, update de somar numa posicao
//
// query(a, b, t) retorna a query de [a, b] na versao t
// update(a, x, t) faz um update v[a]+=x a partir da
// versao de t, criando uma nova versao e retornando seu id
// Por default, faz o update a partir da ultima versao
//
// build - O(n)
// query - O(log(n))
// update - O(log(n))

const int MAX = 2e5+10, UPD = 2e5+10, LOG = 20;
const int MAXS = 2*MAX+UPD*LOG;

namespace perseg {
	ll seg[MAXS];
	int rt[UPD], L[MAXS], R[MAXS], cnt, t;
	int n;
    vector<int> v;

	ll build(int p, int l, int r) {
		if (l == r) return seg[p] = v[l];
		L[p] = cnt++, R[p] = cnt++;
		int m = (l+r)/2;
		return seg[p] = build(L[p], l, m) + build(R[p], m+1, r);
	}
	void build(int n2, vector<int> v2) {
		n = n2, v = v2;
		rt[0] = cnt++;
		build(0, 0, n-1);
	}
	ll query(int a, int b, int p, int l, int r) {
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return seg[p];
		int m = (l+r)/2;
		return query(a, b, L[p], l, m) + query(a, b, R[p], m+1, r);
	}
	ll query(int a, int b, int tt) {
		return query(a, b, rt[tt], 0, n-1);
	}
	ll update(int a, int x, int lp, int p, int l, int r) {
		if (l == r) return seg[p] = seg[lp]+x;
		int m = (l+r)/2;
		if (a <= m)
			return seg[p] = update(a, x, L[lp], L[p]=cnt++, l, m) + seg[R[p]=R[lp]];
		return seg[p] = seg[L[p]=L[lp]] + update(a, x, R[lp], R[p]=cnt++, m+1, r);
	}
	int update(int a, int x, int tt=t) {
		update(a, x, rt[tt], rt[++t]=cnt++, 0, n-1);
		return t;
	}
};

void solve(){
    map<int, int> roots;
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int q; cin >> q;
    int lst = 0;
    vector<int> ord(n); iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) {
        return a[x] < a[y];
    });
    perseg::build(n, vector<int>(n, 0));
    for (auto i : ord) roots[a[i]] = perseg::update(i, a[i]);
    auto get = [&] (int x) {
        int l = 0, r = n-1, resp = -1;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (a[ord[md]] <= x) resp = md, l = md+1;
            else r = md-1;
        }
        if (resp == -1) return -1LL;
        return roots[a[ord[resp]]];
    };
    while (q--) {
        int l, r, x; cin >> l >> r >> x;
        l ^= lst, r ^= lst, x ^= lst;
        --l, --r;
        int id = get(x);
        int ans = (id == -1 ? 0 : perseg::query(l, r, id));
        cout << ans << endl;
        lst = ans;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

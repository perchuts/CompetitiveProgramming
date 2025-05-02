#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

const int MAX = 1e6+10, UPD = 1e6+10, LOG = 20;
const int MAXS = 2*MAX+UPD*LOG;

namespace perseg {
	ll seg[MAXS];
	int rt[UPD], L[MAXS], R[MAXS], cnt, t;
	int n;

	ll build(int p, int l, int r) {
		if (l == r) return seg[p] = 0;
		L[p] = cnt++, R[p] = cnt++;
		int m = (l+r)/2;
		return seg[p] = build(L[p], l, m) + build(R[p], m+1, r);
	}
	void build(int n2) {
		n = n2;
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
int qt[maxn];
void build(vector<int>& v) {
	int n = v.size();
	perseg::build(n);
	map<int, int> last;
	int at = 0;
	for (int i = 0; i < n; i++) {
		if (last.count(v[i])) {
			perseg::update(last[v[i]], -1);
			at++;
		}
		perseg::update(i, 1);
		qt[i] = ++at;
		last[v[i]] = i;
	}
}

int query(int l, int r) {
	return perseg::query(l, r, qt[r]);
}

void solve(){
    int n, q; cin >> n >> q;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    build(v);
    while (q--) {
        int l, r; cin >> l >> r;
        --l, --r;
        cout << query(l, r) << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

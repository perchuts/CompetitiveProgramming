#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define int ll

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
// SegTree Esparsa - Lazy
//
// Query: soma do range [a, b]
// Update: flipa os valores de [a, b]
// O MAX tem q ser Q log N para Q updates
//
// Complexidades:
// build - O(1)
// query - O(log(n))
// update - O(log(n))
const int MAX = 2e5*120;
ll N;

namespace seg {
	int seg[MAX], lazy[MAX], R[MAX], L[MAX], ptr;
	int get_l(int i){
		if (L[i] == 0) L[i] = ptr++;
		return L[i];
	}
	int get_r(int i){
		if (R[i] == 0) R[i] = ptr++;
		return R[i];
	}

	void build() { ptr = 2; }

	void prop(int p, ll l, ll r) {
		if (!lazy[p]) return;
        ll add = lazy[p]; add = add * ((r-l+1)%mod) % mod;
        seg[p] = (seg[p] + add)%mod;
		if (l != r) {
        int lp = get_l(p), rp = get_r(p);
        lazy[lp] = (lazy[lp] + lazy[p]) % mod;
        lazy[rp] = (lazy[rp] + lazy[p]) % mod;
    }
		lazy[p] = 0;
	}

	int query(ll a, ll b, int p=1, ll l=0, ll r=N-1) {
		prop(p, l, r);
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return seg[p];
		ll m = (l+r)/2;
		return (query(a, b, get_l(p), l, m)+query(a, b, get_r(p), m+1, r))%mod;
	}

	int update(ll a, ll b, ll k, int p=1, ll l=0, ll r=N-1) {
		prop(p, l, r);
		if (b < l or r < a) return seg[p];
		if (a <= l and r <= b) {
			lazy[p] = (lazy[p] + k) % mod;
			prop(p, l, r);
			return seg[p];
		}
		ll m = (l+r)/2;
		return seg[p] = (update(a, b, k, get_l(p), l, m)+update(a, b, k, get_r(p), m+1, r))%mod;
	}
};
void solve() {
    ll n; int q; cin >> n >> q;
    N = n+1;
    vector<ll> vals;
    map<ll, pair<ll, ll>> range;
    seg::build();
    for(ll l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        range[n/l] = {l, r};
    }
    vector<array<ll, 5>> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i][4] >> queries[i][0] >> queries[i][1];
        if (queries[i][4] == 2) {
            cin >> queries[i][2] >> queries[i][3];
            auto [L, R] = range[queries[i][2]];
            ll nl = max(L, queries[i][0]);
            ll nr = min(R, queries[i][1]);
            if (nl <= nr) seg::update(nl, nr, queries[i][3]);
        } else {
            ll l = queries[i][0], r = queries[i][1];
            cout << seg::query(l, r) << endl;
        }
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

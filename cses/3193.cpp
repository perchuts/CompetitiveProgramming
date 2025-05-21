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
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
template<int D> struct gauss_z2 {
	bitset<D> basis[D], keep[D];
	int rk, in;
	vector<int> id;
 
	gauss_z2 () : rk(0), in(-1), id(D, -1) {};
 
	bool add(bitset<D> v) {
		in++;
		bitset<D> k;
		for (int i = D - 1; i >= 0; i--) if (v[i]) {
			if (basis[i][i]) v ^= basis[i], k ^= keep[i];
			else {
				k[i] = true, id[i] = in, keep[i] = k;
				basis[i] = v, rk++;
				return true;
			}
		}
		return false;
	}
	pair<bool, bitset<D>> coord(bitset<D> v) {
		bitset<D> c;
		for (int i = D - 1; i >= 0; i--) if (v[i]) {
			if (basis[i][i]) v ^= basis[i], c[i] = true;
			else return {false, bitset<D>()};
		}
		return {true, c};
	}
	pair<bool, vector<int>> recover(bitset<D> v) {
		auto [span, bc] = coord(v);
		if (not span) return {false, {}};
		bitset<D> aux;
		for (int i = D - 1; i >= 0; i--) if (bc[i]) aux ^= keep[i];
		vector<int> oc;
		for (int i = D - 1; i >= 0; i--) if (aux[i]) oc.push_back(id[i]);
		return {true, oc};
	}
};
void solve(){
    int n; cin >> n;
    map<int, int> mp1, dp;
    vector<int> v(n);
    dp[0] = 1;
    vector<int> coord(5000);
    int t = 0;
    for (int i = 2; i < 5000; ++i) {
        bool ok = true;
        for (int j = 2; j * j <= i; ++j) {
            if (i % j == 0) ok = false;
        }
        if (ok) coord[i] = t++;
    }
    gauss_z2<669> basis;
    for (auto& x : v) {
        cin >> x;
        int cur = x;
        bitset<669> eu;
        for (int i = 2; i * i <= x; ++i) {
            int qnt = 0;
            while (cur % i == 0) qnt++, cur /= i;
            if (qnt % 2) eu[coord[i]] = 1;
        }
        if (cur != 1) eu[coord[cur]] = 1;
        basis.add(eu);
    }
    int ans = 1;
    for (int i = 0; i < n-basis.rk; ++i) ans = 2 * ans % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;

template <int p> struct mod_int {
	ll expo(ll b, ll e) {
		ll ret = 1;
		while (e) {
			if (e % 2) ret = ret * b % p;
			e /= 2, b = b * b % p;
		}
		return ret;
	}
	ll inv(ll b) { return expo(b, p-2); }

	using m = mod_int;
	int v;
	mod_int() : v(0) {}
	mod_int(ll v_) {
		if (v_ >= p or v_ <= -p) v_ %= p;
		if (v_ < 0) v_ += p;
		v = v_;
	}

	m& operator +=(const m& a) {
		v += a.v;
		if (v >= p) v -= p;
		return *this;
	}
	m& operator -=(const m& a) {
		v -= a.v;
		if (v < 0) v += p;
		return *this;
	}
	m& operator *=(const m& a) {
		v = v * ll(a.v) % p;
		return *this;
	}
	m& operator /=(const m& a) {
		v = v * inv(a.v) % p;
		return *this;
	}
	m operator -() { return m(-v); }
	m& operator ^= (ll e) {
		if (e < 0) {
			v = inv(v);
			e = -e;
		}
		v = expo(v, e);
		return *this;
	}
	bool operator ==(const m& a) { return v == a.v; }
	bool operator !=(const m& a) { return v != a.v; }

	friend istream& operator >>(istream& in, m& a) {
		ll val; in >> val;
		a = m(val);
		return in;
	}
	friend ostream& operator <<(ostream& out, m& a) {
		return out << a.v;
	}

	friend m operator +(m a, m b) { return a += b; }
	friend m operator -(m a, m b) { return a -= b; }
	friend m operator *(m a, m b) { return a *= b; }
	friend m operator /(m a, m b) { return a /= b; }
	friend m operator ^(m a, ll e) { return a ^= e; }
};
typedef mod_int<MOD> mint;

struct matrix : vector<vector<mint>> {
	int n, m;
	matrix(int _n, int _m, bool id = false) : n(_n), m(_m) {
		(*this).assign(n, vector<mint>(m));
		if (id) {
			assert(_n == _m);
			for (int i = 0; i < n; i++) {
				(*this)[i][i] = 1;
			}
		}
	}
	matrix operator * (const matrix& other) const {
		matrix ans(n, other.m);
		for (int k = 0; k < other.m; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					ans[i][k] += (*this)[i][j] * other[j][k];
				}
			}
		}
		return ans;
	}
};

int32_t main() {
	fast_io;
	int n, m; cin >> n >> m;

	vector<int> a(m), b(m);
	vector<vector<int>> quem(60);

	const int mx1 = 100;

	for(int i=0;i<m;i++){
		cin >> a[i] >> b[i];
		for(int j = b[i]; j<60; j++) quem[j].push_back(a[i]);
	}
	

	vector<matrix> T(60, matrix(mx1, mx1));
	for(int k=0;k<60;k++){
		for(int i=0;i<mx1-1;i++){
			T[k][i][i+1] = 1;
		}
		for(auto x : quem[k]){
			T[k][mx1-1][mx1-x] += 1;
		}		
	}

	//for(int k=0;k<4;k++){
	//	for(int i=0;i<mx1;i++){
	//		for(int j=0;j<mx1;j++){
	//			cout << T[k][i][j] << " ";
	//		}
	//		cout << "\n";
	//	}
	//	cout << "\n";
	//}

	vector<matrix> M(60, matrix(mx1, mx1));

	M[1] = T[0];
	for(int k=1;k<60-1;k++){
		M[k+1] = M[k] * T[k] * M[k];
	}

	M[0] = matrix(mx1, mx1, true);
	matrix BORA(mx1, mx1);
	for(int i=0;i<mx1;i++) BORA[i][i] = 1;

	for(int b = 59; b >= 0; b--){
		if(!((n>>b)&1)) continue;
		BORA = M[b] * BORA;
		BORA = T[b] * BORA;
	}

	//for(int i=0;i<mx1;i++){
	//	for(int j=0;j<mx1;j++){
	//		cout << BORA[i][j] << " ";
	//	}
	//	cout << "\n";
	//}

	cout << BORA[mx1-1][mx1-1] << "\n";





}

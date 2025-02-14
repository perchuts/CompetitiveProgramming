#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

const int MOD = 1e9 + 7;

template<int p> struct mod_int {
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
	m& operator ^=(ll e) {
		if (e < 0) {
			v = inv(v);
			e = -e;
		}
		v = expo(v, e);
		return *this;
	}
	bool operator ==(const m& a) { return v == a.v; }
	bool operator !=(const m& a) { return v != a.v; }

	friend m operator +(m a, m b) { return a += b; }
	friend m operator -(m a, m b) { return a -= b; }
	friend m operator *(m a, m b) { return a *= b; }
	friend m operator /(m a, m b) { return a /= b; }
	friend m operator ^(m a, ll e) { return a ^= e; }

	friend ostream& operator <<(ostream& out, m x) {
		out << x.v;
		return out;
	}
};

typedef mod_int<MOD> mint;
typedef vector<mint> poly;

vector<mint> pols[1002];
mint dp[1002][1010];

poly conv(poly a, poly b) {
	poly ans(a.size() + b.size() - 1);
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < b.size(); j++)
			ans[i+j] += a[i] * b[j];
	return ans;
}

poly divslow(const poly& a, const poly& b) {
	poly q, r = a;
	while (r.size() >= b.size()) {
		q.push_back(r.back() / b.back());
		if (q.back() != 0)
			for (int i = 0; i < b.size(); i++)
				r.end()[-i-1] -= q.back() * b.end()[-i-1];
		r.pop_back();
	}
	return r;
}

int32_t main() {
	fast_io;
	for (int i = 0; i < 1002; i++)
		pols[i] = poly(1002, 0);


	int R, C, Q; cin >> R >> C >> Q;
	R--;

	pols[0][0] = 1;
	pols[1][0] = -1;
	pols[1][1] = 1;
	for(int i=2;i<=C;i++){
		pols[i][0] = -pols[i-1][0] - pols[i-2][0];
		for(int j=1;j<=C;j++){
			pols[i][j] = -pols[i-1][j] - pols[i-2][j] + pols[i-1][j-1];

		}
	}

	//for(int i=0;i<5;i++){
	//	for(int j=0;j<6;j++){
	//		cout << pols[i][j] << " ";

	//	}
	//	cout << endl;
	//}

	// pols[C][0] eh o W.
	// Calcular os coeficientes de x^R mod p
	poly bom = pols[C];
	bom.resize(C + 1);
	poly bixo = {0, 1};
	poly ans = {1};
	int k = R;
	while(k){
		if(k & 1) {
			ans = divslow(conv(ans, bixo), bom);
		}
		k /= 2;
		bixo = divslow(conv(bixo, bixo), bom);
	}
	// ANS eh o W.

	ans = divslow(ans, bom);
	//cout << "ans:";
	//for (int i = 0; i < ans.size(); i++) {
	//	int val = ans[i].v;
	//	if (val > MOD/2) cout << "-" << (MOD-val) << " ";
	//	else cout << val << " ";
	//}
	//cout << endl;

	//cout << "bom:";
	//for (int i = 0; i < bom.size(); i++) {
	//	int val = bom[i].v;
	//	if (val > MOD/2) cout << "-" << (MOD-val) << " ";
	//	else cout << val << " ";
	//}
	//cout << endl;


	dp[0][0] = 1;
	for(int i=1;i<=C;i++){
		dp[i][0] = dp[i-1][0] + 2*dp[i-1][1];
		for(int j=1;j<=C+2;j++){
			dp[i][j] = dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1];
		}
	}

	for(int i=0;i<Q;i++){
		int x, y; cin >> x >> y;
		mint resp = 0;
		for(int k=0;k<C;k++){
			resp += ans[k]*dp[k][abs(x-y)];
			//cout << ans[k] << "*" << dp[k][abs(x-y)] << endl;
			//cout << "-" << ans[k] << "*" << dp[k][x+y] << endl;
			//cout << "-" << ans[k] << "*" << dp[k][C+y+2-x] << endl;
			//cout << "k=" << k << " " << resp.v << endl;
			if(x+y <= C+1) resp -= ans[k] * dp[k][x+y];
			//if(C+y+1-x <= C+1) resp -= ans[k] * dp[k][C+y+1-x];
			if(2*C+2-y-x <= C+1) resp -= ans[k] * dp[k][2*C+2-y-x];
		}
		cout << R << " ";
		cout << resp.v << endl;
	}
	
}

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

template<int p> struct mod_int{
	ll expo(ll b, ll e){
		ll ret = 1;
		while (e){
			if (e%2) ret = ret * b % p;
			e /= 2; b = b * b % p;
		}
		return ret;
	}

	ll inv(ll b) {return expo(b, p-2);}

	using m = mod_int;
	int v;
	
	mod_int() : v(0) {}

	mod_int(ll v_) {
		if (v_ >= p or v_ <= -p)  v_ %= p;
		if (v_ < 0) v_ += p;
		v = v_;
	}

	m& operator+=(const m& a){
		v += a.v;
		if (v >= p) v -= p;
		return *this;
	}	

	m& operator-=(const m& a){
		v -= a.v;
		if (v < 0) v += p;
		return *this;
	}

	m& operator*=(const m& a){
		v = v * ll(a.v) % p;
		return *this;
	}

	m& operator/=(const m& a){
		v = v * inv(a.v) % p;
		return *this;
	}

	m operator-() {return m(-v);}

	m& operator^=(ll e){
		if (e < 0){
			v = inv(v);
			e = -e;
		}
		v = expo(v, e);
		return *this;
	}

	bool operator==(const m& a) {return v == a.v;}
	bool operator!=(const m& a) {return v != a.v;}

	friend m operator +(m a, m b) {return a += b;}
	friend m operator -(m a, m b) {return a -= b;}
	friend m operator *(m a, m b) {return a *= b;}
	friend m operator /(m a, m b) {return a /= b;}
	friend m operator ^(m a, ll e) {return a ^= e;}
};

const int mod = 998244353;
typedef mod_int<mod> mint;

void ntt(vector<mint>&a, bool rev){
	int n = a.size(); auto b = a;
	mint g = 1;
	while ((g^(mod/2)) == 1) g += 1;
	if (rev) g = 1/g;

	for (int step = n/2; step; step /= 2){
		mint w = g ^ (mod / (n / step)), wn = 1;
		for (int i = 0; i < n/2; i += step){
			for (int j = 0; j < step; ++j){
				auto u = a[2*i+j], v = wn * a[2*i+j+step];
				b[i+j] = u + v; b[i + n/2 + j] = u - v;
			}
			wn = wn * w;
		}
		swap(a,b);
	}

	if (rev){
		auto n1 = mint(1) / n;
		for (auto &x : a) x *= n1;
	}
}

vector<mint> convolution(const vector<mint> &a, const vector<mint> &b){
	vector<mint> l(a.begin(), a.end()), r(b.begin(), b.end());
	int N = l.size()+r.size()-1, n = 1 << __lg(2*N - 1);
	l.resize(n);
	r.resize(n);
	ntt(l,false);
	ntt(r,false);
	for (int i = 0; i < n; ++i) l[i] *= r[i];
	ntt(l,true);
	l.resize(N);
	return l;
}

int32_t main() {_
	int n, goal; cin >> n >> goal;
	string st; cin >> st;

	vector<int> ans(n+1);
	vector<bool> ba(n), bb(n);
	int sum = 0;
	for (int i = 0; i < n; ++i) if (st[i] != '0'){
		if (i and st[i-1] == '0') sum += st[i]-'0', ba[i] = true; 
		if (i != n-1 and st[i+1] == '0') sum += st[i]-'0', bb[i] = true;
	}

	for (int w = 1; w <= n; ++w){
		int cur = sum;
		for (int k = 0; k*w <= n; ++k){
			int i = k*w;
			if (i < n and ba[i]) cur -= st[i]-'0';
			
			i = k*w - 1;
			if (i >= 0 and bb[i]) cur -= st[i]-'0';
		}
		ans[w] += cur;
	}


	vector<mint> v0(n), v1(n);
	for (int i = 0; i < n; ++i){
		if (st[i] == '0') v0[i] = 1;
		else v1[i] = mint(st[i]-'0');
	}

	vector<mint> va = v0, vb = v1;
	reverse(va.begin(), va.end());
	vector<mint> r1 = convolution(va,vb);
	for (int i = n; i < r1.size(); ++i){
		int p = i-n+1;
		int val = r1[i].v;
		if (p <= n) ans[p] += val;
	}

	va = v0, vb = v1;
	reverse(vb.begin(), vb.end());
	r1 = convolution(va,vb);
	for (int i = n; i < r1.size(); ++i){
		int p = i-n+1;
		int val = r1[i].v;
		if (p <= n) ans[p] += val;
	}

	vector<int> vs;
	for (int i = 1; i <= n; ++i) vs.pb(ans[i]);
	sort(vs.begin(), vs.end());
	reverse(vs.begin(), vs.end());
	cout << vs[goal-1] << endl;

}

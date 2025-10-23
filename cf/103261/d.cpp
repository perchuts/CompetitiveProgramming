#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

ll mul(ll a, ll b, ll m) {
	ll ret = a*b - ll((long double)1/m*a*b+0.5)*m;
	return ret < 0 ? ret+m : ret;
}

int pow(int b, int e, int mod){
	int r = 1;
	while(e){
		if(e&1) r = mul(r, b, mod);
		e /= 2; b = mul(b, b, mod);
	}
	return r;
}

bool prime(ll n) {
	if (n < 2) return 0;
	if (n <= 3) return 1;
	if (n % 2 == 0) return 0;

	ll r = __builtin_ctzll(n - 1), d = n >> r;
	for (int a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
		ll x = pow(a, d, n);
		if (x == 1 or x == n - 1 or a % n == 0) continue;

		for (int j = 0; j < r - 1; j++) {
			x = mul(x, x, n);
			if (x == n - 1) break;
		}
		if (x != n - 1) return 0;
	}
	return 1;
}

ll rho(ll n) {
	if (n == 1 or prime(n)) return n;
	auto f = [n](ll x) { return mul(x, x, n) + 1; };

	ll x = 0, y = 0, t = 30, prd = 2, x0 = 1, q;
	while (t % 40 != 0 or gcd(prd, n) == 1) {
		if (x==y) x = ++x0, y = f(x);
		q = mul(prd, abs(x-y), n);
		if (q != 0) prd = q;
		x = f(x), y = f(f(y)), t++;
	}
	return gcd(prd, n);
}

vector<ll> fact(ll n) {
	if (n == 1) return {};
	if (prime(n)) return {n};
	ll d = rho(n);
	vector<ll> l = fact(d), r = fact(n / d);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}

int32_t main() {
	fast_io;
	int m, kk; cin >> m >> kk;

	auto v = fact(m);
	sort(v.begin(), v.end());


	int phi = 1;
	for(int i=0;i<v.size();){
		int j = i;
		while(j < v.size() && v[j] == v[i]) j++;
		int e = j - i;
		int p = v[i];
		// p ^ e eh fator de m
		int coiso = 1;
		coiso *=  p-1;
		if(p == 2) e--;
		for(int k=0;k<e-1;k++) coiso *= p;
		phi = lcm(phi, coiso);
		if(p == 2 && e == 1) phi = lcm(phi, 2);
		i = j;
	}

	int mk = 0;
	while(mk < kk && phi % 2 == 0){
		phi /= 2;
		mk++;
	}

	if(mk < kk) cout << -1 << endl;
	else{
		for(int i=1;;i++){
			if(gcd(i, m) != 1) continue;
			int b = pow(i, phi, m);
			int a = b;
			int ok = 1;
			for(int k=0;k<kk;k++){
				if(a == 1){
					ok = 0;
					break;
				}
				a = mul(a, a, m);
			}
			if(ok == 0) continue;
			assert(a == 1);
			cout << b << endl;
			return 0;
			}
	}

}

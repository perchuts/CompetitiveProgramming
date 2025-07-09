#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

#define P 998244353
#define MAGIC 1

int fexp(int b, int e){
	int r = 1;
	while(e){
		if(e&1) r = r * b % P;
		e /= 2; b = b * b % P;
	}
	return r;
}
int inv(int g) { return fexp(g, P - 2); }
int add(int a, int b) {
	a += b; if (a >= P) a -= P;
	return a;
}
int sub(int a, int b) {
	a -= b; if (a < 0) a += P;
	return a;
}

void ntt(vector<int>& a, bool rev) {
	int n = a.size(); auto b = a;
	assert(!(n&(n-1)));
	int g = 1;
	while (fexp(g, P / 2) == 1) g += 1;
	if (rev) g = inv(g);

	for (int step = n/2; step; step /= 2) {
		int w = fexp(g, P / n / step), wn = 1;
		for (int i = 0; i < n/2; i += step) {
			for (int j = 0; j < step; j++) {
				auto u = a[2*i + j], v = wn * a[2*i + j + step] % P;
				b[i+j] = add(u, v); b[i + n/2 + j] = sub(u, v);
			}
			wn = wn * w % P;
		}
		swap(a, b);
	}

	if (rev) {
		auto n1 = inv(n);
		for (auto& x : a) x = x * n1 % P;
	}
}

vector<int> conv(vector<int> l, vector<int> r) {
	int N = l.size()+r.size()-1, n = 1;
	while (n <= N) n *= 2;
	l.resize(n); r.resize(n);
	ntt(l, false);
	ntt(r, false);
	for (int i = 0; i < n; i++) l[i] = l[i] * r[i] % P;
	ntt(l, true);
	l.resize(N);
	return l;
}

vector<int> D(vector<int> p) {
	if (p.empty()) return p;
	for (int i = 0; i + 1 < p.size(); i++) p[i] = (i + 1) * p[i + 1] % P;
	p.pop_back();
	return p;
}

vector<int> inv(vector<int> p) {
	assert(!p.empty() && p[0] != 0);
	int val_0 = inv(p[0]); 
	for (int& x : p) x = x * val_0 % P;

	vector<int> q = {inv(p[0])};
	int n = p.size(), k = 1;
	while (k < n) {
		k *= 2;
		q.resize(2*k);
		ntt(q, false);
		vector<int> p0(2*k);
		copy_n(p.begin(), min(k, n), p0.begin());
		ntt(p0, false);
		for (int i = 0; i < 2*k; i++)
			q[i] = q[i] * (2 - (p0[i] * q[i] % P) + P) % P;
		ntt(q, true);
		q.resize(k);
	}
	q.resize(n);

	for (int& x : q) x = x * val_0 % P;
	return q;
}

pair<vector<int>, vector<int>> divslow(const vector<int>& a, const vector<int>& b) {
	vector<int> q, r = a;
	while (r.size() >= b.size()) {
		q.push_back(r.back() * inv(b.back()) % P);
		if (q.back() != 0) {
			for (int i = 0; i < b.size(); i++) {
				r.end()[-i-1] = sub(r.end()[-i-1], q.back() * b.end()[-i-1] % P);
			}
		}
		r.pop_back();
	}
	return {q, r};
}

pair<vector<int>, vector<int>> divmod(const vector<int>& a, const vector<int>& b) {
	if (a.size() < b.size()) return {{}, a};
	if (max(b.size(), a.size() - b.size()) < MAGIC) return divslow(a, b);
	vector<int> ra(a.rbegin(), a.rend());
	vector<int> rb(b.rbegin(), b.rend());
	int k = a.size() - b.size() + 1;
	rb.resize(k);
	vector<int> irb = inv(move(rb)), q = conv(ra, irb);
	q = vector<int>(q.rend() - k, q.rend());
	vector<int> r = conv(move(q), b);
	for (int i = 0; i < r.size(); i++) r[i] = sub(a[i], r[i]);
	while (r.size() > 1 && r.back() == 0) r.pop_back();
	return {q, r};
}

namespace multipoint {
	vector<vector<int>> tree;
	void build(vector<int>& p) {
		int n = p.size();
		tree.resize(2*n);
		for (int i = 0; i < n; i++) tree[n + i] = {P-p[i], 1};
		for (int i = n - 1; i > 0; i--)
			tree[i] = conv(tree[2*i], tree[2*i + 1]);
	}
	vector<int> evaluate(vector<int>& fs, vector<int>& qs) {
		int N = int(qs.size());
		if (N == 0) return {};
		vector<vector<int>> up(2 * N);
		for (int x = 0; x < N; ++x) {
			up[x + N] = {P-qs[x], 1};
		}
		for (int x = N-1; x >= 1; --x) {
			up[x] = conv(up[2 * x], up[2 * x + 1]);
		}
		vector<vector<int>> down(2 * N);
		down[1] = divmod(fs, up[1]).second;
		for (int x = 2; x < 2*N; ++x) {
			down[x] = divmod(down[x / 2], up[x]).second;
		}
		vector<int> y(N);
		for (int x = 0; x < N; ++x) {
			y[x] = (down[x + N].empty() ? 0 : down[x + N][0]);
		}
		return y;
	}
}

int32_t main() {
	fast_io;

	//for (int seed = 0; ; seed++) {

	//int n = rand() % 50 + 1;
	//set<int> st;
	//while (st.size() != n + 1) st.insert(rand() % P);
	//int t = *st.begin(); st.erase(t);
	//vector<int> a(st.begin(), st.end()); random_shuffle(a.begin(), a.end());

	int n, t; cin >> n >> t;
	vector<int> a(n);
	for(auto& x : a) cin >> x;

	for(int i=0;i<n;i++){
		if(a[i] == t){
			for(int j=0;j<n;j++){
				if(j == i) cout << 1 << " ";
				else cout << 0 << " ";
			}
			cout << endl;
			exit(0);
		}
	}

	// tudo tem que ser distinto
	auto b = a;
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	assert(b.size() == n);

	vector<int> MvKaio(n+1); // coeficientes daquele polinomio
	auto vai = [&] (auto&& self, int l, int r) -> vector<int> {
		if (l + 1 == r) return {P-a[l], 1};
		int mid = (l + r) / 2;
		auto ql = self(self, l, mid);
		auto qr = self(self, mid, r);
		auto res = conv(ql, qr);
		return res;
	};
	MvKaio = vai(vai, 0, n);

	vector<int> dmv = D(MvKaio);
	auto g = multipoint::evaluate(dmv, a);
	
	int pt = 0;
	for(int i=0, ti=1; i<=n; i++, ti = ti * t % P){
		pt = (pt + ti * MvKaio[i]) % P;
	}

	for(int i=0;i<n;i++){
		int tai = (t + P- a[i]) % P * g[i] % P;
		cout << pt * fexp(tai, P-2) % P << " ";
	}
	cout << endl;

	//}
}

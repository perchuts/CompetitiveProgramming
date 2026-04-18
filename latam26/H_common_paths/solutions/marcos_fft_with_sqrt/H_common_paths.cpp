#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define pb push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(s) int(s.size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

// NTT
typedef vector<ll> Poly;
const int MOD = 998244353, LG = 19;

// typedef complex<double> base;
struct base{
	double r, i;
	base(double r_ = 0, double i_ = 0) : r(r_), i(i_) {}
	base operator*(const base &o){
		return base(r*o.r - i*o.i, r*o.i + o.r*i);
	}
	
	base& operator*=(const base &o){
		double newr = r*o.r - i*o.i, newi = r*o.i + o.r*i;
		r = newr, i = newi;
		return *this;
	}
 
	double real() const{ return r; }
	
	base& operator+=(const base &o){
		r += o.r, i += o.i;
		return *this;
	}
 
	base& operator/=(const double &o){
		r /= o, i /= o;
		return *this;
	}
	
	base& operator-=(const base &o){
		r -= o.r, i -= o.i;
		return *this;
	}
 
	base operator+(const base &o){
		return base(r + o.r, i + o.i);
	}
 
	base operator-(const base &o){
		return base(r - o.r, i - o.i);
	}	
};
 
double PI = acos(-1);
 
void fft(vector<base> &a, bool inv){
	int n = (int)a.size();
 
	for(int i = 1, j = 0; i < n; i++){
		int bit = n >> 1;
		for(; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if(i < j)
			swap(a[i], a[j]);
	}
 
	for(int len = 2; len <= n; len <<= 1) {
		double ang = 2*PI/len * (inv ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len){
			base w(1);
			for (int j = 0; j < len/2; j++){
				base u = a[i+j], v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w *= wlen;
			}
		}
	}
	if(inv)
		for(int i = 0; i < n; i++)
			a[i] /= n;
}
void multiply(const vector<ll> &a, const vector<ll> &b, vector<ll> &res){
	vector<base> fa, fb, ffa, ffb;
	size_t n = 1;
	while(n < a.size()) n <<= 1;
	while(n < b.size()) n <<= 1;
	n <<= 1;
	fa.resize(n), fb.resize(n);
    ffa.resize(n), ffb.resize(n);
 
    // about sqrt(max(max(a), max(b))), so a % X and a / X
    // are about the same size
    ll X = 450;
 
    for(int i = 0; i < (int)a.size(); i++){
        fa[i] = base((double)(a[i] % X), 0.0);
        ffa[i] = base(double(a[i] / X), 0.0);
    }
 
    for(int i = 0; i < (int)b.size(); i++){
        fb[i] = base((double)(b[i] % X), 0.0);
        ffb[i] = base((double)(b[i] / X), 0.0);
    }
 
	fft(fa, false), fft (fb, false);
    fft(ffa, false), fft(ffb, false);
    vector<base> aa, bb, cc, dd;
    aa.resize(n);
    bb.resize(n);
    cc.resize(n);
    dd.resize(n);
    for(size_t i = 0; i < n; i++){
        aa[i] = ffa[i] * ffb[i];
        bb[i] = ffa[i] * fb[i];
        cc[i] = fa[i] * ffb[i];
        dd[i] = fa[i] * fb[i];
    }
	fft(aa, true);
    fft(bb, true);
    fft(cc, true);
    fft(dd, true);
 
	res.resize(n);
	for(size_t i = 0; i < n; ++i){
        // aa[i] * X * X + bb[i] * X + cc[i] * X + dd[i];
		res[i] += ll(dd[i].real() + 0.5)%MOD;
		res[i] += ll(cc[i].real() + 0.5)%MOD*X%MOD;
		res[i] += ll(bb[i].real() + 0.5)%MOD*X%MOD;
		res[i] += ll(aa[i].real() + 0.5)%MOD*X%MOD*X%MOD;
		res[i] %= MOD;
    }
}

int add(int a, int b) {
	a += b;
	return a >= MOD ? a-MOD : a;
}

int sub(int a, int b) {
	a -= b;
	return a < 0 ? a + MOD : a;
}

int mul(int a, int b) {
	return 1ll * a * b % MOD;
}

int fpow(int a, ll b) {
	int r = 1;
	while(b) {
		if(b & 1) r = mul(r, a);
		b >>= 1;
		a = mul(a, a);
	}
	return r;
}

void addPoly(Poly &p, Poly &q) {
	if(SZ(p) < SZ(q)) p.resize(SZ(q));
	fore(i, 0, SZ(q)) p[i] = add(p[i], q[i]);
}

void subPoly(Poly &p, Poly &q) {
	if(SZ(p) < SZ(q)) p.resize(SZ(q));
	fore(i, 0, SZ(q)) p[i] = sub(p[i], q[i]);
}


// Centroid decomposition

struct Centroid {
	vector<int> tk, szt, subt, dep;
	vector<vector<int>> g;
	int n;

	Centroid(int _n) : n(_n), g(_n), tk(_n), szt(_n), subt(_n), dep(_n) {}

	void addEdge(int x, int y) {
		g[x].pb(y);
		g[y].pb(x);
	}

	int getDirectedSubtreeSize(int x, int y) {
		if(dep[x] < dep[y]) return n - subt[y];
		return subt[x];
	}

	// pol[i] = ways of adding i edges to the intersection
	void processSubtree(int pos, Poly &pol, int depth, int p) {
		vector<int> sizes;
		for(int x : g[pos]) if(x != p) {
			sizes.pb(getDirectedSubtreeSize(x, pos));
			if(!tk[x]) {
				processSubtree(x, pol, depth + 1, pos);
			}
		}
		
		// Ways to finish intersection in node pos
		int tot = 0, acum = 1;
		for(int x : sizes) {
			tot = add(tot, mul(x, acum));
			acum = add(acum, x);
		}

		// Count AB and BA (reflections) 
		tot = mul(tot, 2);

		// Also, both paths can finish at this node
		tot = add(tot, 1);
		
		while(SZ(pol) < depth + 1) pol.pb(0);
		pol[depth] = add(pol[depth], tot);
	}
	
	// Process node rt as root of the current centroid tree
	Poly processRoot(int rt) {
		int k = SZ(g[rt]);
		vector<Poly> pols;
		vector<int> sizes;
		
		for(int x : g[rt]) {
			sizes.pb(getDirectedSubtreeSize(x,rt));
			Poly now;
			if(!tk[x]) {
				processSubtree(x, now, 1, rt);
			}
			pols.pb(now);
		}

		// Compute answer when the intersection includes two neighbours of the root.
		// If we want to compute the sum of the product over all pairs of
		// Polynomials X and Y, we can use: sum(X*Y) = (sum(X)^2 - sum(X^2)) / 2
		Poly sum2, sumcuads;
		fore(i, 0, k) {
			Poly cuad;
			multiply(pols[i], pols[i], cuad);
			addPoly(sum2, pols[i]);
			addPoly(sumcuads, cuad);
		}
		
		Poly ans;
		multiply(sum2, sum2, ans);
		subPoly(ans, sumcuads);
		for(ll &x : ans) x = mul(x, MOD / 2 + 1);
		
		// Compute answer when the intersection includes only one neighour of the root.
		// One part of each path goes to the chosen neighbour, but each of the paths
		// can also extend to another neigbour (different for each of them).
		// 
		int sumSizes = 0, sumCuadSizes = 0;
		fore(i, 0, k) {
			sumSizes = add(sumSizes, sizes[i]);
			sumCuadSizes = add(sumCuadSizes, mul(sizes[i], sizes[i]));
		}
		
		fore(i, 0, k) {
			// One path finishes in the root, the other one extends somewhere else.
			int tot = 2 * (n - sizes[i] - 1);

			// Both paths finish in the root
			tot = add(tot, 1);

			// Both paths extend to different subtrees (outside of this one).
			// We use the same trick for computing sum(size_x * size_y)
			int other = sub(sumSizes, sizes[i]);
			int other2 = sub(sumCuadSizes, mul(sizes[i], sizes[i]));
			tot = add(tot, sub(mul(other, other), other2));

			for(ll &x : pols[i]) x = mul(x, tot);
			addPoly(ans, pols[i]);
		}

		return ans;
	}

	int precalcDfs(int pos, int par, int depth) {
		subt[pos] = 1;
		dep[pos] = depth;
		for(int x : g[pos]) if(x != par) {
			subt[pos] += precalcDfs(x, pos, depth+1);
		}
		return subt[pos];
	}
	
	int calcSize(int x, int f) {
		szt[x] = 1;
		for(int y : g[x]) if(y != f && !tk[y]) {
			szt[x] += calcSize(y,x);
		}
		return szt[x];
	}

	Poly centroidDfs(int x = 0, int f = -1, int sz = -1) {
		if(sz < 0) sz = calcSize(x, -1);
		for(int y : g[x]) if(!tk[y] && szt[y] * 2 >= sz) {
			szt[x] = 0;
			return centroidDfs(y, f, sz);
		}
		tk[x] = 1;
		Poly ans = processRoot(x);
		for(int y : g[x]) if(!tk[y]) {
			Poly cur = centroidDfs(y, x);
			addPoly(ans, cur);
		}
		return ans;
	}

	Poly go() {
		fill(ALL(tk), 0);
		precalcDfs(0, -1, 0);
		return centroidDfs();
	}
};

int main() {FIN;
		int n; cin>>n;
		Centroid c(n);
		
		fore(i, 1, n) {
			int x, y; cin >> x >> y;
			x--; y--;
			c.addEdge(x, y);
		}

		Poly ans = c.go();
		ans.resize(n);
		fore(i, 1, n) cout << ans[i] << " \n"[i+1 == n];
}

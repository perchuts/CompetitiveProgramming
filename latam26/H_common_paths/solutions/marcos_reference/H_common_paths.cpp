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
typedef vector<int> Poly;
const int MOD = 998244353, LG = 19;

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

template<class u, class uu, u p, u root>
struct FFT {
	u r[1 + (2 << LG)];

	constexpr u m(u a, u b) {
		uu k = uu(a) * b;
		#define op(g) g * (g * p + 2)
		k += u(k) * (op(op(op(op(op(-p)))))) * uu(p);
		#undef op
		return u(k >> (8 * sizeof(u)));
	}

	constexpr u red(u k, u a) {
		return a - k * (a >= k);
	}

	FFT() {
		u k = r[2 << LG] = -p % p;
		u b = root;
		u e = p >> LG;

		for(; e; e >>= 1, b = m(b, b))
			if(e & 1) k = m(k, b);

		for(int i = (2 << LG) - 1; i >= 0; i--) {
			r[i] = red(p, m(r[i + 1], k));
			if(!(i & (i - 1))) k = m(k, k);
		}
	}

	Poly cv(const Poly &as, const Poly &bs, u *v) {
		int c = max(SZ(as) + SZ(bs) - 1, 0);
		int n = 1;
		assert(c <= (1 << LG));

		u h = u(uu(-p) * -p % p);
		u a = m(h, p / 2 + 1);
		u x, y;

		while(n < c) {
			n <<= 1;
			h = red(p, m(h, a));
		}

		fore(i, 0, n) {
			v[i]   = i < SZ(as) ? u(as[i]) : 0;
			v[i+n] = i < SZ(bs) ? u(bs[i]) : 0;
		}

		for(auto s : {v, v + n})
			for(int j = n; j >= 2; j--)
				for(int k = j & -j; k >>= 1;)
					fore(i, j - k, j) {
						x = s[i];
						y = s[i - k];
						s[i - k] = red(2 * p, x + y);
						s[i] = m(2 * p + y - x, r[3 * k - j + i]);
					}

		fore(i, 0, n)
			v[i] = m(v[i], v[i + n]);

		fore(j, 2, n + 1)
			for(int k = 1; !(k & j); k <<= 1)
				fore(i, j - k, j) {
					x = m(v[i], r[3 * k + j - i]);
					y = red(2 * p, v[i - k]);
					v[i - k] = x + y;
					v[i] = 2 * p + y - x;
				}

		fore(i, 0, c)
			v[i] = red(p, m(v[i], h));

		return Poly(v, v + c);
	}
};

Poly multiply(const Poly &as, const Poly &bs) {
	static uint32_t v[2<<LG];
	static FFT<uint32_t, uint64_t, 998244353, 3> fft;
	return fft.cv(as, bs, v);
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
			Poly cuad = multiply(pols[i], pols[i]);
			addPoly(sum2, pols[i]);
			addPoly(sumcuads, cuad);
		}
		
		Poly ans = multiply(sum2, sum2);
		subPoly(ans, sumcuads);
		for(int &x : ans) x = mul(x, MOD / 2 + 1);
		
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

			for(int &x : pols[i]) x = mul(x, tot);
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

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
const int MOD = 998244353, RT = 5, MAXN = 1<<19;

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

struct CD {
	int x;
	CD(int x) : x(x) {}
	CD() {}
};

CD operator * (const CD& a, const CD& b) {
	return CD(mul(a.x, b.x));
}

CD operator + (const CD& a, const CD& b) {
	return CD(add(a.x, b.x));
}

CD operator - (const CD& a, const CD& b) {
	return CD(sub(a.x, b.x));
}

vector<int> rts(MAXN + 9, -1);
CD cp1[MAXN + 9], cp2[MAXN + 9];
int R[MAXN + 9];

CD root(int n, bool inv) {
	int r = rts[n] < 0 ? rts[n] = fpow(RT, (MOD-1) / n) : rts[n];
	return CD(inv ? fpow(r, MOD - 2) : r);
}

void dft(CD* a, int n, bool inv) {
	fore(i, 0, n) if(R[i] < i) swap(a[R[i]], a[i]);
	for(int m = 2; m <= n; m *= 2) {
		CD wi = root(m, inv);
		for(int j = 0; j < n; j += m) {
			CD w(1);
			for(int k = j, k2 = j + m / 2; k2 < j + m; k++, k2++) {
				CD u = a[k];
				CD v = a[k2] * w;
				a[k] = u + v;
				a[k2] = u - v;
				w = w * wi;
			}
		}
	}
	if(inv) {
		CD z(fpow(n, MOD - 2));
		fore(i, 0, n) a[i] = a[i] * z;
	}
}

Poly multiply(Poly& p1, Poly& p2) {
	int n = SZ(p1) + SZ(p2) + 1, m = 1, cnt = 0;
	while(m <= n) m += m, cnt++;
	fore(i, 0, m) {
		R[i] = 0;
		fore(j, 0, cnt) R[i] = (R[i] << 1) | ((i >> j) & 1);
	}
	fore(i, 0, m) cp1[i] = cp2[i] = 0;
	fore(i, 0, SZ(p1)) cp1[i] = p1[i];
	fore(i, 0, SZ(p2)) cp2[i] = p2[i];
	dft(cp1, m, 0);
	dft(cp2, m, 0);
	fore(i, 0, m) cp1[i] = cp1[i] * cp2[i];
	dft(cp1, m, 1);
	Poly res;
	fore(i, 0, n-2) res.pb(cp1[i].x);
	return res;
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

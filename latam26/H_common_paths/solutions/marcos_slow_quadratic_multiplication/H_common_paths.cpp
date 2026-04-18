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

typedef vector<int> Poly;
const int MOD = 998244353;

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

// Quadratic polynomial multiplication, this should be very slow
Poly multiply(const Poly &as, const Poly &bs) {
    int n=SZ(as), m=SZ(bs);
    if(!n||!m) return {};

    Poly ans(n+m-1);
    fore(i,0,n) fore(j,0,m) ans[i+j]=add(ans[i+j], mul(as[i],bs[j]));
    return ans;
}

void addPoly(Poly &p, Poly &q) {
	if(SZ(p) < SZ(q)) p.resize(SZ(q));
	fore(i, 0, SZ(q)) p[i] = add(p[i], q[i]);
}

void subPoly(Poly &p, Poly &q) {
	if(SZ(p) < SZ(q)) p.resize(SZ(q));
	fore(i, 0, SZ(q)) p[i] = sub(p[i], q[i]);
}


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

	void processSubtree(int pos, Poly &pol, int depth, int p) {
		vector<int> sizes;
		for(int x : g[pos]) if(x != p) {
			sizes.pb(getDirectedSubtreeSize(x, pos));
			if(!tk[x]) {
				processSubtree(x, pol, depth + 1, pos);
			}
		}
		int tot = 0, acum = 1;
		for(int x : sizes) {
			tot = add(tot, mul(x, acum));
			acum = add(acum, x);
		}

		tot = mul(tot, 2);

		tot = add(tot, 1);
		
		while(SZ(pol) < depth + 1) pol.pb(0);
		pol[depth] = add(pol[depth], tot);
	}
	
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

		Poly sum2, sumcuads;
		fore(i, 0, k) {
			Poly cuad = multiply(pols[i], pols[i]);
			addPoly(sum2, pols[i]);
			addPoly(sumcuads, cuad);
		}
		
		Poly ans = multiply(sum2, sum2);
		subPoly(ans, sumcuads);
		for(int &x : ans) x = mul(x, MOD / 2 + 1);
		
		int sumSizes = 0, sumCuadSizes = 0;
		fore(i, 0, k) {
			sumSizes = add(sumSizes, sizes[i]);
			sumCuadSizes = add(sumCuadSizes, mul(sizes[i], sizes[i]));
		}
		
		fore(i, 0, k) {
			int tot = 2 * (n - sizes[i] - 1);
			tot = add(tot, 1);

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

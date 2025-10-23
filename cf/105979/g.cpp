#include <bits/stdc++.h>
// Otimizacoes agressivas, pode deixar mais rapido ou mais devagar
#pragma GCC optimize("Ofast")
// Auto explicativo
#pragma GCC optimize("unroll-loops")
// Vetorizacao
#pragma GCC target("avx2")
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define ll __int128_t
#define int int64_t

using namespace std;

using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define sq(x) ((x)*(ll)(x))

struct pt { // ponto
	int x, y;
	pt(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
	bool operator < (const pt p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
	bool operator == (const pt p) const {
		return x == p.x and y == p.y;
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
	pt operator * (const int c) const { return pt(x*c, y*c); }
	ll operator * (const pt p) const { return x*(ll)p.x + y*(ll)p.y; }
	ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};

ll sarea2(pt p, pt q, pt r) { // 2 * area com sinal
	return (q-p)^(r-q);
}

bool col(pt p, pt q, pt r) { // se p, q e r sao colin.
	return sarea2(p, q, r) == 0;
}

bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return sarea2(p, q, r) > 0;
}

vector<pt> convex_hull(vector<pt> v) { // convex hull - O(n log(n))
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	if (v.size() <= 1) return v;
	vector<pt> l, u;
	for (int i = 0; i < v.size(); i++) {
		while (l.size() > 1 and !ccw(l.end()[-2], l.end()[-1], v[i]))
			l.pop_back();
		l.push_back(v[i]);
	}
	for (int i = v.size() - 1; i >= 0; i--) {
		while (u.size() > 1 and !ccw(u.end()[-2], u.end()[-1], v[i]))
			u.pop_back();
		u.push_back(v[i]);
	}
	l.pop_back(); u.pop_back();
	for (pt i : u) l.push_back(i);
	return l;
}

int inpol(vector<pt>& v, pt p) { // O(n)
	int qt = 0;
	for (int i = 0; i < v.size(); i++) {
		if (p == v[i]) return 2;
		int j = (i+1)%v.size();
		if (p.y == v[i].y and p.y == v[j].y) {
			if ((v[i]-p)*(v[j]-p) <= 0) return 2;
			continue;
		}
		bool baixo = v[i].y < p.y;
		if (baixo == (v[j].y < p.y)) continue;
		ll t = (p-v[i])^(v[j]-v[i]);
		if (!t) return 2;
		if (baixo == (t > 0)) qt += baixo ? 1 : -1;
	}
	return qt != 0;
}

int vai() {
	string s; cin >> s;
	s.erase(s.begin() + s.size() - 3);
	return stoll(s);
}

void solve() {
	int n; cin >> n;	

	int h = vai();

	vector<tuple<int, int, int>> a(n);
	int mn = h;
	for (auto &[x, y, z] : a) {
		x = vai();
		y = vai();
		z = vai();

		mn = min(mn, z);
	}

	pt eu; eu.x = vai(), eu.y = vai();

	auto check = [&] (int mid) {
		vector<pt> pts;
		for (auto [x, y, z] : a) {
			if (z >= mid) pts.push_back({x, y});
		}

		bool ok = false;

		auto ch = convex_hull(pts);
		if (inpol(ch, eu) == 1) {
			if (ch.size() != 4) {
				ok = ch.size() > 2;
			} else {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < pts.size(); j++) {
						vector<pt> tri = {ch[i], ch[(i + 1) % 4], pts[j]};
						if (sarea2(tri[0], tri[1], tri[2])) {
							if (inpol(tri, eu) == 1) ok = true;
						}
					}
				}
			}
		}

		return ok;
	};
	
	int lo = mn, hi = h;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		
		if (check(mid)) lo = mid;
		else hi = mid - 1;
	}

	if (!check(lo)) {
		cout << -1 << endl;
		return;
	}
	
	cout << (h - lo) / 100 << "." << ((h - lo) % 100) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

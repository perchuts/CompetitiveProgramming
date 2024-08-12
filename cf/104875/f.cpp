#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

using ll = long long;

const int mod = 998244353;
const int INF = 0x3f3f3f3f;

#define sq(x) ((x) * ll(x))

struct pt {
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
	pt operator * (const int c) const { return pt(x * c, y * c); }
	ll operator * (const pt p) const { return x*(ll)p.x + y*(ll)p.y; }
	ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};

ll sarea2(pt p, pt q, pt r) {
	return (q-p)^(r-q);
}

bool col(pt p, pt q, pt r) {
	return sarea2(p, q, r) == 0;
}

bool ccw(pt p, pt q, pt r) {
	return sarea2(p, q, r) > 0;
}

int quad(pt p) {
	return (p.x < 0)^3*(p.y < 0);
}

struct Compare {
	pt center;
	Compare(pt p) : center(p) {}
	bool operator()(pt p, pt q) {
		if (quad(p) != quad(q)) return quad(p) < quad(q);
		return ccw(q, center, p);
	}
};

int32_t main() {_
	int n; cin >> n;
	vector<pair<pt, pt>> A(n);
	for (auto &[x, y] : A) cin >> x >> y;

	{ // reta vertical
		int l = -INF, r = INF;
		for (auto [p, q] : A) {
			auto [x1, y1] = p;
			auto [x2, y2] = q;
			l = max(l, x1);
			r = min(r, x2);
		}
		if (l <= r) {
			cout << "possible" << endl;
			return 0;
		}
	}
	{ // reta horizontal
		int l = -INF, r = INF;
		for (auto [p, q] : A) {
			auto [x1, y1] = p;
			auto [x2, y2] = q;
			l = max(l, y1);
			r = min(r, y2);
		}
		if (l <= r) {
			cout << "possible" << endl;
			return 0;
		}
	}

	// e agora, josé?	
	function<void(int, int)> guess = [&] (double lo, double hi) {
		if (lo > hi) return;
		double mid = (lo + hi) / 2;

		pt center = {-1, mid};
		Compare cmp(center);

		sort();


	};
	

	cout << "impossible" << endl;
	return 0;
}

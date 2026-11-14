#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

//using ll = __int128_t;
using ll = long long;
using Pt = pair<int, int>;
#define x first
#define y second

using ld = long double;
const ld DINF = 1e18;
const ld pi = acos(-1.0);
const ld eps = 1e-9;

#define sq(x) ((x)*(x))

bool eq(ld a, ld b) {
	return abs(a - b) <= eps;
}

struct pt {
	ld x, y;
	pt(ld x_ = 0, ld y_ = 0) : x(x_), y(y_) {}
	pt(Pt p) : x(p.x), y(p.y) {}
	bool operator < (const pt p) const {
		if (!eq(x, p.x)) return x < p.x;
		if (!eq(y, p.y)) return y < p.y;
		return 0;
	}
	bool operator == (const pt p) const {
		return eq(x, p.x) and eq(y, p.y);
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
	pt operator * (const ld c) const { return pt(x*c, y*c); }
	pt operator / (const ld c) const { return pt(x/c, y/c); }
	ld operator * (const pt p) const { return x*p.x + y*p.y; }
	ld operator ^ (const pt p) const { return x*p.y - y*p.x; }
};

ld sarea(pt p, pt q, pt r) {
	return ((q-p)^(r-q))/2;
}

bool ccw(pt p, pt q, pt r) {
	return sarea(p, q, r) > eps;
}

struct line {
	pt p, q;
	line() {}
	line(pt p_, pt q_) : p(p_), q(q_) {}
};

ld dist(pt p, pt q) {
	return hypot(p.y - q.y, p.x - q.x);
}

ld norm(pt v) {
	return dist(pt(0, 0), v);
}

pt rotate90(pt p) {
	return pt(-p.y, p.x);
}

pt proj(pt p, line r) {
	if (r.p == r.q) return r.p;
	r.q = r.q - r.p; p = p - r.p;
	pt proj = r.q * ((p*r.q) / (r.q*r.q));
	return proj + r.p;
}

int32_t main() {_
	long long n; cin >> n;
	vector<Pt> a(n), b(n);
	for (auto &[x, y] : a) {
		long long _x, _y; cin >> _x >> _y;
		x = _x, y = _y;
	}
	for (auto &[x, y] : b) {
		long long _x, _y; cin >> _x >> _y;
		x = _x, y = _y;
	}

	//cout << "A:" << endl;
	//for (auto [x, y] : a) cout << x << " " << y << endl;
	//cout << "B:" << endl;
	//for (auto [x, y] : b) cout << x << " " << y << endl;

	//cout << "center: " << center.x << " " << center.y << endl;

	vector<Pt> na(n);
	set<Pt> st(b.begin(), b.end());

	int k = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int p = 0; p < k; p++) st.insert(na[p]);

			pt u = a[i], v = b[j];
			pt mid = (u + v) / 2;

			pt vec = (u - v);
			//vec = vec / norm(vec);
			vec = rotate90(vec);

			//cout << "mid: " << mid.x << " " << mid.y << endl;
			//cout << "mid + vec: " << (mid + vec).x << " " << (mid + vec).y << endl;

			line reta(mid, mid + vec);
			bool ok = true;

			for (k = 0; ok && k < n; k++) {
				pt md = proj(a[k], reta);
				pt to = pt(a[k]) + (md - a[k]) * 2;

				Pt rd; rd.x = llround(to.x); rd.y = llround(to.y);
				//cout << "rd: " << rd.x << " " << rd.y << endl;
				if (!(pt(rd) == to)) ok = false;
				else {
					if (!st.count(rd)) ok = false;
					else {
						st.erase(rd);
						na[k] = rd;
					}
				}
			}

			if (!ok) continue;

			bool orient = ccw(mid, mid + vec, na[0]);
			for (auto p : na) {
				ok &= orient == ccw(mid, mid + vec, p);
				if (!ok) break;
			}
	
			//cout << "Ok is " << ok << endl;

			if (!ok) break;

			cout << "possible" << endl;
			return 0;
		}
		break;
	}

	cout << "impossible" << endl;
}

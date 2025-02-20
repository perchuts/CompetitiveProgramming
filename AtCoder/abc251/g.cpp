#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// Geometria

typedef double ld;
const ld DINF = 1e18;
const ld pi = acos(-1.0);
const ld eps = 1e-9;

#define sq(x) ((x)*(x))

bool eq(ld a, ld b) {
	return abs(a - b) <= eps;
}

struct pt { // ponto
	ld x, y;
	pt(ld x_ = 0, ld y_ = 0) : x(x_), y(y_) {}
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
	pt operator * (const ld c) const { return pt(x*c  , y*c  ); }
	pt operator / (const ld c) const { return pt(x/c  , y/c  ); }
	ld operator * (const pt p) const { return x*p.x + y*p.y; }
	ld operator ^ (const pt p) const { return x*p.y - y*p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};

struct line { // reta
	pt p, q;
	line() {}
	line(pt p_, pt q_) : p(p_), q(q_) {}
	friend istream& operator >> (istream& in, line& r) {
		return in >> r.p >> r.q;
	}
};

// PONTO & VETOR

ld dist(pt p, pt q) { // distancia
	return hypot(p.y - q.y, p.x - q.x);
}

ld dist2(pt p, pt q) { // quadrado da distancia
	return sq(p.x - q.x) + sq(p.y - q.y);
}

ld norm(pt v) { // norma do vetor
	return dist(pt(0, 0), v);
}

ld angle(pt v) { // angulo do vetor com o eixo x
	ld ang = atan2(v.y, v.x);
	if (ang < 0) ang += 2*pi;
	return ang;
}

ld sarea(pt p, pt q, pt r) { // area com sinal
	return ((q-p)^(r-q))/2;
}

bool col(pt p, pt q, pt r) { // se p, q e r sao colin.
	return eq(sarea(p, q, r), 0);
}

bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return sarea(p, q, r) > eps;
}

pt rotate(pt p, ld th) { // rotaciona o ponto th radianos
	return pt(p.x * cos(th) - p.y * sin(th),
			p.x * sin(th) + p.y * cos(th));
}

pt rotate90(pt p) { // rotaciona 90 graus
	return pt(-p.y, p.x);
}

// RETA

bool isvert(line r) { // se r eh vertical
	return eq(r.p.x, r.q.x);
}

bool isinseg(pt p, line r) { // se p pertence ao seg de r
	pt a = r.p - p, b = r.q - p;
	return eq((a ^ b), 0) and (a * b) < eps;
}

ld get_t(pt v, line r) { // retorna t tal que t*v pertence a reta r
	return (r.p^r.q) / ((r.p-r.q)^v);
}

pt proj(pt p, line r) { // projecao do ponto p na reta r
	if (r.p == r.q) return r.p;
	r.q = r.q - r.p; p = p - r.p;
	pt proj = r.q * ((p*r.q) / (r.q*r.q));
	return proj + r.p;
}

pt inter(line r, line s) { // r inter s
	if (eq((r.p - r.q) ^ (s.p - s.q), 0)) return pt(DINF, DINF);
	r.q = r.q - r.p, s.p = s.p - r.p, s.q = s.q - r.p;
	return r.q * get_t(r.q, s) + r.p;
}

bool interseg(line r, line s) { // se o seg de r intersecta o seg de s
	if (isinseg(r.p, s) or isinseg(r.q, s)
		or isinseg(s.p, r) or isinseg(s.q, r)) return 1;

	return ccw(r.p, r.q, s.p) != ccw(r.p, r.q, s.q) and
			ccw(s.p, s.q, r.p) != ccw(s.p, s.q, r.q);
}

ld disttoline(pt p, line r) { // distancia do ponto a reta
	return 2 * abs(sarea(p, r.p, r.q)) / dist(r.p, r.q);
}

ld disttoseg(pt p, line r) { // distancia do ponto ao seg
	if ((r.q - r.p)*(p - r.p) < 0) return dist(r.p, p);
	if ((r.p - r.q)*(p - r.q) < 0) return dist(r.q, p);
	return disttoline(p, r);
}

ld distseg(line a, line b) { // distancia entre seg
	if (interseg(a, b)) return 0;

	ld ret = DINF;
	ret = min(ret, disttoseg(a.p, b));
	ret = min(ret, disttoseg(a.q, b));
	ret = min(ret, disttoseg(b.p, a));
	ret = min(ret, disttoseg(b.q, a));

	return ret;
}


// se o ponto ta dentro do poligono: retorna 0 se ta fora,
// 1 se ta no interior e 2 se ta na borda

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

struct convex_pol {
	vector<pt> pol;

	// nao pode ter ponto colinear no convex hull
	convex_pol() {}
	convex_pol(vector<pt> v) : pol(convex_hull(v)) {}

	// se o ponto ta dentro do hull - O(log(n))
	bool is_inside(pt p) {
		if (pol.size() == 0) return false;
		if (pol.size() == 1) return p == pol[0];
		int l = 1, r = pol.size();
		while (l < r) {
			int m = (l+r)/2;
			if (ccw(p, pol[0], pol[m])) l = m+1;
			else r = m;
		}
		if (l == 1) return isinseg(p, line(pol[0], pol[1]));
		if (l == pol.size()) return false;
		return !ccw(p, pol[l], pol[l-1]);
	}
};

const int INF = 1e13;

vector<pt> hp_intersection(vector<line> &v) {

	deque<pt> dq = {{INF, INF}, {-INF, INF}, {-INF, -INF}, {INF, -INF}};

	sort(v.begin(), v.end(), [&](line r, line s) { return angle(r.q-r.p) < angle(s.q-s.p); });

	for(int i = 0; i < v.size() and dq.size() > 1; i++) {
		pt p1 = dq.front(), p2 = dq.back();
		while (dq.size() and !ccw(v[i].p, v[i].q, dq.back()))
			p1 = dq.back(), dq.pop_back();
		while (dq.size() and !ccw(v[i].p, v[i].q, dq.front()))
			p2 = dq.front(), dq.pop_front();

		if (!dq.size()) break;
		if (p1 == dq.front() and p2 == dq.back()) continue;
		dq.push_back(inter(v[i], line(dq.back(), p1)));
		dq.push_front(inter(v[i], line(dq.front(), p2)));

		if (dq.size() > 1 and dq.back() == dq.front()) dq.pop_back();
	}
	return vector<pt>(dq.begin(), dq.end());
}
void solve(){
    int n; cin >> n;
    vector<pt> pol(n);
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        pol[i] = pt(x, y);
    }
    int m; cin >> m;
    vector<pt> pts(m);
    vector<vector<line>> half_planes(n, vector<line>(4));
	const double EPS = 1e-6;
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y;
        pts[i] = pt(x, y);
        for (int j = 0; j < n; ++j) {
            auto p1 = pol[j];
            auto p2 = pol[(j+1)%n];
			auto p3 = p2-p1;
			auto p4 = rotate90(p3);
            auto L = line(p1+pts[i]-p4*EPS, p2+pts[i]-p4*EPS);
            if (i == 0) half_planes[j] = {L, L, L, L};
            if (half_planes[j][0].p.x < L.p.x) half_planes[j][0] = L;
            if (half_planes[j][1].p.x > L.p.x) half_planes[j][1] = L;
            if (half_planes[j][2].p.y < L.p.y) half_planes[j][2] = L;
            if (half_planes[j][3].p.y > L.p.y) half_planes[j][3] = L;
        }
    }
    vector<line> hp;
    for (auto x : half_planes) for (auto y : x) hp.pb(y);
    auto intr = hp_intersection(hp);
    auto cp = convex_pol(intr);
    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        int x, y; cin >> x >> y;
        pt p(x, y);
        cout << (cp.is_inside(p) ? "Yes" : "No") << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

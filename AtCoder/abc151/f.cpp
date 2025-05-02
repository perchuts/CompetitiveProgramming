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
// Minimum Enclosing Circle
//
// O(n) com alta probabilidade

const double EPS = 1e-12;

struct pt {
	double x, y;
	pt(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	pt operator + (const pt& p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt& p) const { return pt(x-p.x, y-p.y); }
	pt operator * (double c) const { return pt(x*c, y*c); }
	pt operator / (double c) const { return pt(x/c, y/c); }
};

double dot(pt p, pt q) { return p.x*q.x+p.y*q.y; }
double cross(pt p, pt q) { return p.x*q.y-p.y*q.x; }
double dist(pt p, pt q) { return sqrt(dot(p-q, p-q)); }

pt center(pt p, pt q, pt r) {
	pt a = p-r, b = q-r;
	pt c = pt(dot(a, p+r)/2, dot(b, q+r)/2);
	return pt(cross(c, pt(a.y, b.y)), cross(pt(a.x, b.x), c)) / cross(a, b);
}

struct circle {
	pt cen;
	double r;
	circle(pt cen_, double r_) : cen(cen_), r(r_) {}
	circle(pt a, pt b, pt c) {
		cen = center(a, b, c);
		r = dist(cen, a);
	}
	bool inside(pt p) { return dist(p, cen) < r+EPS; }
};

circle minCirc(vector<pt> v) {
	shuffle(v.begin(), v.end(), rng);
	circle ret = circle(pt(0, 0), 0);
	for (int i = 0; i < v.size(); i++) if (!ret.inside(v[i])) {
		ret = circle(v[i], 0);
		for (int j = 0; j < i; j++) if (!ret.inside(v[j])) {
			ret = circle((v[i]+v[j])/2, dist(v[i], v[j])/2);
			for (int k = 0; k < j; k++) if (!ret.inside(v[k]))
				ret = circle(v[i], v[j], v[k]);
		}
	}
	return ret;
}
void solve(){
    int n; cin >> n;
    vector<pt> p(n);
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        p[i] = pt(x, y);
    }
    auto ans = minCirc(p);
    cout << fixed << setprecision(11) << ans.r << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

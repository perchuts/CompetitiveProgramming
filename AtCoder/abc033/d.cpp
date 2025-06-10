#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
// Auto explicativo
#pragma GCC optimize("unroll-loops")
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

#define sq(x) ((x)*(ll)(x))

using ld = long double;
const ld pi = acos(-1.0);
ll sarea2(pt p, pt q, pt r) { // 2 * area com sinal
	return (q-p)^(r-q);
}
ld angle(pt v) { // angulo do vetor com o eixo x
	ld ang = atan2(v.y, v.x);
	if (ang < 0) ang += 2*pi;
	return ang;
}
bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return sarea2(p, q, r) > 0;
}

int quad(pt p) { // quadrante de um ponto
	return (p.x<0)^3*(p.y<0);
}

bool compare_angle(pt p, pt q) { // retorna se ang(p) < ang(q)
	if (quad(p) != quad(q)) return quad(p) < quad(q);
	return ccw(q, pt(0, 0), p);
}


ld anglee(pt p, pt q) {
    ld res = angle(q) - angle(p);
    if (res < 0) res += 2*pi;
    return res;
}

void solve(){
    int n; cin >> n;
    int reto = 0, sexo = 0;
    vector<pt> v(n);
    for (auto& x : v) cin >> x;
    for (int i = 0; i < n; ++i) {
        vector<pt> pts;
        for (int j = 0; j < n; ++j) if (i != j) pts.pb(v[j] - v[i]);
        map<ii, int> ap;
        sort(all(pts), compare_angle);
        for (int j = 0; j < n-1; ++j) {
            auto [x, y] = pts[j];
            int g = gcd(x, y);
            x /= g, y /= g;
            int xx = -y, yy = x;
            if (xx < 0) xx *= -1, yy *= -1;
            if (xx == 0) yy = abs(yy);
            if (ap[{xx, yy}]) reto++;
            if (x < 0) x *= -1, y *= -1;
            if (x == 0) y = abs(y);
            ap[{x, y}]++;
            pts.pb(pts[j]);
        }
        int tot = 0, w = 0;
        for (int j = 0; j < 2*n-2; ++j) {
            while (w == j-n+1 or anglee(pts[w], pts[j]) >= pi) w++;
            if (j >= n-1) tot += j-w;
        }
        w = 0;
        for (int j = 0; j < 2*n-2; ++j) {
            while (w == j-n+1 or (anglee(pts[w], pts[j]) > pi/2.0+1e-10)) w++;
            if (j >= n-1) tot -= j-w;
        }
        sexo += tot;
    }
    cout << n*(n-1)*(n-2)/6-sexo-reto << ' ' << reto << ' ' << sexo << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}


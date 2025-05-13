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
	pt operator / (const int c) const { return pt(x/c, y/c); }
	ll operator * (const pt p) const { return x*(ll)p.x + y*(ll)p.y; }
	ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};
ll dist2(pt p, pt q) { // quadrado da distancia
	return sq(p.x - q.x) + sq(p.y - q.y);
}

pt rotate90(pt p) { // rotaciona 90 graus
	return pt(-p.y, p.x);
}
void solve(){
    int n; cin >> n;
    vector<pt> p(n);
    vector<int> val(n);
    for (int i = 0; i < n; ++i) cin >> p[i] >> val[i], p[i] = p[i] * 2;
    int ans = -1;
    for (int __ = 0; __ < 2; ++__) {
        map<pair<pt, pt>, vector<pair<int, pt>>> ids;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (p[i].y == p[j].y) continue;
                pt med = (p[i] + p[j]) / 2;
                pt dif = p[i] - p[j];
                int g = gcd(dif.x, dif.y);
                dif = dif/g;
                if (dif.y < 0) dif.y *= -1, dif.x *= -1;
                pt sexo = p[i];
                int dy = sexo.y / dif.y;
                sexo.y -= dif.y * dy;
                sexo.x -= dif.x * dy;
                if (sexo.y < 0) sexo.y += dif.y, sexo.x += dif.x;
				assert(sexo.y >= 0);
                dif = rotate90(dif);
                dif.y *= -1, dif.x *= -1;
                int dx = med.x / dif.x;
                med.y -= dif.y * dx;
                med.x -= dif.x * dx;
                if (med.x < 0) med.y += dif.y, med.x += dif.x;
				assert(med.x >= 0);
                ids[{dif, med}].pb({val[i] + val[j], sexo});
            }
        }
        for (auto [x, y] : ids) {
            if (sz(y) < 2) continue;
            sort(rbegin(y), rend(y));
            for (int i = 1; i < sz(y); ++i) {
                if (!(y[i-1].second == y[i].second)) ckmax(ans, y[i].first + y[i-1].first);
            }

        }
        for (auto& [x, y] : p) swap(x, y);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

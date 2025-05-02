#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato
//#define debug

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

ll sarea2(pt p, pt q, pt r) { // 2 * area com sinal
	return (q-p)^(r-q);
}
bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return sarea2(p, q, r) > 0;
}

int quad(pt p) { // quadrante de um ponto
	return (p.x<0)^3*(p.y<0);
}

bool compare_angle(pt p, pt q) { // retorna se ang(p) < ang(q)
	return !ccw(q, pt(0, 0), p);
}
int solve(int n, vector<pt> v){
    vector qnt(n+1, vector(n+1, vector(n+1, 0LL)));
    vector<pt> v2; v2.pb(pt(0, 0));
    for (auto x : v) v2.pb(x);
    swap(v, v2);
    for (int i = 1; i <= n; ++i) {
        for (int j = i+1; j <= n; ++j) {
            for (int k = j+1; k <= n; ++k) {
                int A = abs(sarea2(v[i], v[j], v[k]));
                for (int w = 1; w <= n; ++w) {
                    if (w == i or w == j or w == k) continue;
                    int A2 = abs(sarea2(v[w], v[i], v[j])) + abs(sarea2(v[w], v[i], v[k])) + abs(sarea2(v[w], v[j], v[k]));
                    if (A == A2) qnt[i][j][k]++;
                }
                qnt[i][k][j] = qnt[j][i][k] = qnt[j][k][i] = qnt[k][i][j] = qnt[k][j][i] = qnt[i][j][k];
            }
        }
    }
    vector<int> pot(n+1, 1);
    for (int i = 1; i <= n; ++i) pot[i] = 2 * pot[i-1] % mod;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        vector<pt> pts;
        for (int j = 1; j <= n; ++j) {
            if (v[j].x < v[i].x or (v[i].x == v[j].x and v[j].y <= v[i].y)) continue;
            pts.pb(v[j]-v[i]);
        }
        sort(all(pts), compare_angle);
        vector<int> idx;
        for (auto p : pts) {
            for (int j = 1; j <= n; ++j) if (p == v[j]-v[i]) idx.pb(j);
        }
        // dp dois ultimos!
        int m = sz(idx);
        if (!m) continue;
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(m, vector<int>(2)));
        for (int j = 1; j < m; ++j) {
            for (int k = j-1; k >= 0; --k) {
                int par = sarea2(pt(0, 0), pts[j], pts[k])&1;
#ifdef debug
				cout << i << ' ' << idx[j] << ' ' << idx[k] << " paridade: " << par << endl;
#endif
                int q = pot[qnt[i][idx[j]][idx[k]]];
                dp[j][k][par] = q;
                for (int l = k-1; l >= 0; --l) {
					if (ccw(pts[l], pts[k], pts[j])) continue;
#ifdef debug
					cout << "valid transition: ";
					cout << i << " " << idx[k] << ' ' << idx[l] << " to " << i << " " << idx[j] << " " << idx[k] << endl;
#endif
                    for (int w = 0; w < 2; ++w) {
                        dp[j][k][w] = (dp[j][k][w] + dp[k][l][w^par] * q) % mod;
                    }
                }
                ans = (ans + dp[j][k][0]) % mod;
                #ifdef debug
                if (dp[j][k][0] != 0) cout << i << ' ' << idx[j] << ' ' << idx[k] << endl;
                #endif
                //cout << i << ' ' << idx[j] << ' ' << idx[k] << ": " << dp[j][k][0] << endl;
            }
        }
    }
    return ans;
}
bool col(pt p, pt q, pt r) { // se p, q e r sao colin.
	return sarea2(p, q, r) == 0;
}
ll polarea2(vector<pt> v) { // 2 * area do poligono
	ll ret = 0;
	for (int i = 0; i < v.size(); i++)
		ret += sarea2(pt(0, 0), v[i], v[(i + 1) % v.size()]);
	return abs(ret);
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

int brute(int n, vector<pt> v) {
    int ans = 0;
    for (int i = 7; i < (1 << n); ++i) {
        if (__builtin_popcount(i) < 3) continue;
        vector<pt> sexo;
        for (int j = 0; j < n; ++j) if (i >> j & 1) sexo.pb(v[j]);
        auto ch = convex_hull(sexo);
        if (polarea2(ch) % 2 == 0) {
#ifdef debug
            cout << "Valid polygon: ";
            for (auto [x, y] : sexo) cout << x << ' ' << y << endl;
            cout << endl;
#endif
            ans++;
        }
    }
    return ans;
}
int32_t main(){_
#ifndef gato
    int n; cin >> n;
    vector<pt> v(n);
    for (auto& x : v) cin >> x;
    cout << solve(n, v) << endl;
#ifdef debug
    brute(n, v);
#endif
#else
    int t = 1;
    while (true) {
        int n = rnd(3, 15);
        vector<pt> v(n);
        for (auto& [x, y] : v) {
            x = rnd(-100, 100), y = rnd(-100, 100);
        }
        bool ok = 1;
        for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j) for (int k = j+1; k < n; ++k) {
            if (col(v[i], v[j], v[k])) ok = 0;
        }
        if (!ok) continue;
        int ans = brute(n, v), my = solve(n, v);
        if (ans != my) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto [x, y] : v) cout << x << ' ' << y << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

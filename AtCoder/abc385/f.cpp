#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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
	ll operator * (const pt p) const { return x*(ll)p.x + y*(ll)p.y; }
	ll operator ^ (const pt p) const { return x*(ll)p.y - y*(ll)p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};
// PONTO & VETOR

ll dist2(pt p, pt q) { // quadrado da distancia
	return sq(p.x - q.x) + sq(p.y - q.y);
}

ll sarea2(pt p, pt q, pt r) { // 2 * area com sinal
	return (q-p)^(r-q);
}

bool col(pt p, pt q, pt r) { // se p, q e r sao colin.
	return sarea2(p, q, r) == 0;
}

bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return sarea2(p, q, r) > 0;
}
double solve(int n, vector<int> pos, vector<int> h){
    vector<pt> v(n);
    for (int i = 0; i < n; ++i) v[i] = pt(pos[i], h[i]);
    // pra eu ver o predio i do ponto h
    // o segmento (0, h) --- (x[i], pos[i]) nao pode ter intersecao com nenhum outro ponto
    // quando q tem intersecao com o ponto j?
    // se o slope (x[j], pos[j]) --- (x[i], pos[j]) eh <= a slope do segmento, fez o L 
    // a slope eh monotonica
    // busca binaria tem q funcionar ent
    // podemos confirmar com um quadratico
    bool bad = 1;
    for (int i = 1; i < n; ++i) bad &= (h[i] * pos[i-1] > h[i-1] * pos[i]);
    if (bad) return -1;
    double mn = 0;
    vector<pair<int, pt>> hull = {{0, v[0]}};
    vector<int> choice(n);
    for (int i = 1; i < n; ++i) {
        int l = 0, r = sz(hull)-2, x = r+1;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            // eu sou melhor do que o proximo?
            int x1 = hull[md].first, x2 = hull[md+1].first;
            int valx1 = (h[i]-h[x1])*(pos[i]-pos[x2]);
            int valx2 = (h[i]-h[x2])*(pos[i]-pos[x1]);
            if (valx1 <= valx2) x = md, r = md-1;
            else l = md+1;
        }
        choice[i] = hull[x].first;
        while (hull.size() > 1 and ccw(hull.end()[-2].second, hull.end()[-1].second, v[i]))
            hull.pop_back();
        hull.push_back({i, v[i]});
    }
    // (h[i]-H)/pos[i] < (h[i]-h[j])/(pos[i]-pos[j])
    // (h[i]-H)*(pos[i]-pos[j]) < h[i]*pos[i]-h[j]*pos[i]
    // h[i]*pos[i]-h[i]*pos[j]-H*pos[i]+H*pos[j]
    // h[j]*pos[i]-h[i]*pos[j] < H*(pos[i]-pos[j])
    // (h[j]*pos[i]-h[i]*pos[j])/(pos[i]-pos[j])
    // h[i] / pos[i] <= h[j] / pos[j]
    // (hj*pi-hi*pj) / (pi-pj) > (hk*pi-hi*pk) / (pi-pk)
    // (hi+hj) - (hi*pi-hj*pj)/(pi-pj)
    // min (h[i]-h[j])/(p[i]-p[j])

    for (int i = 1; i < n; ++i) {
        int j = choice[i];
        ckmax(mn, (h[j]*pos[i]-h[i]*pos[j]) / (double)(pos[i]-pos[j]));
    }
    return mn;
}

double brute(int n, vector<int> pos, vector<int> h) {
    bool bad = 1;
    for (int i = 1; i < n; ++i) bad &= (h[i] * pos[i-1] > h[i-1] * pos[i]);
    if (bad) return -1;
    double mn = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            ckmax(mn, (h[j]*pos[i]-h[i]*pos[j]) / (double)(pos[i]-pos[j]));
        }
    }
    return mn;
}

int32_t main(){_
#ifndef gato
    int n; cin >> n;
    vector<int> h(n), pos(n);
    for (int i = 0; i < n; ++i) cin >> pos[i] >> h[i];
    double ans = solve(n, pos, h);
    if (ans < -0.5) cout << -1 << endl;
    else cout << fixed << setprecision(15) << ans << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 10);
        vector<int> pos(n), h(n);
        int lst = 0;
        for (auto& x : pos) {
            lst = rnd(lst+1, lst+3);
            x = lst;
        }
        for (auto& x : h) x = rnd(1, lst+10);
        double my = solve(n, pos, h);
        double ans = brute(n, pos, h);
        cout << fixed << setprecision(15) << my << endl;
        cout << fixed << setprecision(15) << ans << endl;
        if (abs(my-ans) > 1e-9) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (int i = 0; i < n; ++i) cout << pos[i] << ' ' << h[i] << endl;
            cout << "Your output: " << fixed << setprecision(15) << my << endl;
            cout << "Answer: " << fixed << setprecision(15) << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

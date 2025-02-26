#include <bits/stdc++.h>
//#define gato
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
bool solve(int n, vector<ii> s, vector<ii> t){
    // funcs
    if (n == 1) return true;
    auto cross = [] (ii b, ii c) { return b.first*c.second-b.second*c.first; };
    auto dot   = [] (ii b, ii c) { return b.first*c.first+b.second*c.second; };
    auto cmp2  = [] (ii a, ii b) {
        auto [x1, y1] = a;
        auto [x2, y2] = b;
        int d1 = x1*x1+y1*y1, d2 = x2*x2+y2*y2, cr = x1*y2 - x2*y1;
        if (cr == 0) return d1 < d2;
        return cr > 0;
    };
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        auto v2 = t; auto v1 = s;
        for (auto& [x, y] : v1) x -= s[i].first, y -= s[i].second;
        for (auto& [x, y] : v2) x -= t[j].first, y -= t[j].second;
        sort(all(v2), cmp2);
        sort(all(v1), cmp2);
        reverse(all(v2)); v2.pop_back(); reverse(all(v2));
        reverse(all(v1)); v1.pop_back(); reverse(all(v1));
        for (int k = 0; k < n-1; ++k) {
            bool nice = 1;
            for (int l = 0; l < n-1; ++l) {
                auto [x1, y1] = v2[(k+l)%(n-1)];
                auto [x2, y2] = v1[l];
                nice &= (x1*x1+y1*y1==x2*x2+y2*y2);
            }
            if (!nice) continue;
            for (int l = 0; l < n-1; ++l) {
                nice &= (cross(v2[(k+l)%(n-1)], v2[(k+l+1)%(n-1)]) == cross(v1[l], v1[(l+1)%(n-1)]));
                nice &= (dot(v2[(k+l)%(n-1)], v2[(k+l+1)%(n-1)]) == dot(v1[l], v1[(l+1)%(n-1)]));
            }
            if (nice) return true;
        }
    }
    return false;
}
bool solve2(int n, vector<ii> s, vector<ii> t){
    if (n == 1) return true;
    if (n == 2) {
        if ((s[0].first-s[1].first)*(s[0].first-s[1].first)+(s[0].second-s[1].second)*(s[0].second-s[1].second) == (t[0].first-t[1].first)*(t[0].first-t[1].first)+(t[0].second-t[1].second)*(t[0].second-t[1].second)) return true;
        return false;
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        int dx = s[i].first - t[j].first, dy = s[i].second - t[j].second;
        auto v2 = t; auto v1 = s;
        for (auto& [x, y] : v2) x += dx, y += dy;
        auto cmp = [&] (ii a, ii b) {
            auto [x1, y1] = a;
            auto [x2, y2] = b;
            int d1 = x1*x1+y1*y1, d2 = x2*x2+y2*y2;
            if (d1 == d2) return x1*y2 - x2*y1 > 0;
            return d1 < d2;
        };
        auto v3 = v1;
        auto v4 = v2;
        sort(all(v2), cmp);
        sort(all(v1), cmp);
        bool ok = 1;
        for (int k = 0; k < n; ++k) {
            if ((v1[k].first*v1[k].first)+(v1[k].second*v1[k].second) != (v2[k].first*v2[k].first)+(v2[k].second*v2[k].second)) {
                ok = 0; break;
            }
        }
        v1 = v3, v2 = v4;
		auto cross = [] (ii a, ii b, ii c) {
			return (b.first-a.first)*(c.second-a.second)-(b.second-a.second)*(c.first-a.first);
		};
		auto dot = [] (ii a, ii b, ii c) {
			return (b.first-a.first)*(c.first-a.first)+(b.second-a.second)*(c.second-a.second);
		};
		if (!ok) continue;
		int cc = 0, dd = 0;
		for (int k = 0; k < n; ++k) { 
			int cz = cross(v1[i], v1[(i==0)], v1[k]);
			int dt = dot(v1[i], v1[(i==0)], v1[k]);
			cc += cz, dd += dt;
		}

		for (int k = 0; k < n; ++k) {
			if (k == j) continue;
			int cc2 = 0, dd2 = 0;
			for (int l = 0; l < n; ++l) {
				int cz = cross(v2[j], v2[k], v2[l]);
				int dt = dot(v2[j], v2[k], v2[l]);
				cc2 += cz, dd2 += dt;
			}
            if (cc2 == cc and dd2 == dd) return true;
		}
    }
    return false;
}

int32_t main(){_
#ifndef gato
    int n; cin >> n;
    vector<ii> v1(n), v2(n);
    for (auto& [x, y] : v1) cin >> x >> y;
    for (auto& [x, y] : v2) cin >> x >> y;
    cout << (solve(n, v1, v2) ? "Yes" : "No") << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 5);
        vector<ii> v1(n), v2(n);
        for (auto& [x, y] : v1) x = rnd(-10, 10), y = rnd(-10, 10);
        for (auto& [x, y] : v2) x = rnd(-10, 10), y = rnd(-10, 10);
        bool ok = 1;
        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
            ok &= (v1[i] != v1[j]);
            ok &= (v2[i] != v2[j]);
        }
        if (!ok) continue;
        if (solve(n, v1, v2) != solve2(n, v1, v2)) {
            cout << "Distinct solutions in test " << t << endl;
            cout << n << endl;
            for (auto [x, y] : v1) cout << x << ' ' << y << endl;
            for (auto [x, y] : v2) cout << x << ' ' << y << endl;
            cout << "solve: " << (solve(n, v1, v2) ? "Yes" : "No") << endl;
            cout << "solve2: " << (solve2(n, v1, v2) ? "Yes" : "No") << endl;
            exit(0);
        }
        cout << "Same answers on test " << t++ << endl;
    }
#endif

}



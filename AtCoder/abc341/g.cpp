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
void solve(){
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    reverse(all(a));
    vector<pt> p; p.pb(pt(0, 0)), p.pb(pt(1, a[0]));
    int s = a[0];
    vector<double> ans;
    vector<int> pr(n+1);
    for (int i = 1; i <= n; ++i) pr[i] = pr[i-1] + a[i-1];
    ans.pb(a[0]);
    for (int i = 1; i < n; ++i) {
        s += a[i];
        pt eu = pt(i+1, s);
        while (sz(p) > 1 and !ccw(p[sz(p)-2], p[sz(p)-1], eu)) p.pop_back();
        int t = i+1-p.back().x;
        ans.pb(double(pr[i+1]-pr[i+1-t])/(double)t);
        p.pb(eu);
    }
    reverse(all(ans));
    cout << fixed << setprecision(10);
    for (auto x : ans) cout << x << endl;
    cout << endl;
}
 
int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

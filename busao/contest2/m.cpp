#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
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

struct pt{
	double x, y, z;
};

double det(pt p, pt v, pt s){

	double T = 0;
	T += p.x*v.y*s.z - p.x*v.z*s.y;
	T += p.y*v.z*s.x - p.y*v.x*s.z;
	T += p.z*v.x*s.y - p.z*v.y*s.x;
	return T;
}

void solve(){

	int n; cin >> n;
	vector<int> x(n), y(n), z(n, 1);
	for(int i=0;i<n;i++){
		cin >> x[i] >> y[i];
	}
	vector<int> px(n), py(n), pz(n);
	vector<int> sx(n), sy(n), sz(n);
	for(int i=1;i<n;i++){
		px[i] = px[i-1] + x[i-1];
		py[i] = py[i-1] + y[i-1];
		pz[i] = pz[i-1] + z[i-1];
	}
	for(int i=n-2;i>=0;i--){
		sx[i] = sx[i+1] + x[i+1];
		sy[i] = sy[i+1] + y[i+1];
		sz[i] = sz[i+1] + z[i+1];
	}
	vector<pt> v(n), p(n), s(n);
	for(int i=0;i<n;i++){
		v[i].x =  x[i], v[i].y =  y[i], v[i].z =  z[i];
		p[i].x = px[i], p[i].y = py[i], p[i].z = pz[i];
		s[i].x = sx[i], s[i].y = sy[i], s[i].z = sz[i];
	}

	double T = 0;
	for(int j=1;j<=n-2;j++){
		// det(pref[j], v[j], suf[j])
		T += det(p[j], v[j], s[j]);
	}
	double A = 0;
	for(int i=1;i<n-1;i++){
		A += det(v[0], v[i], v[i+1]);
	}
	cout << fixed << setprecision(10) << T/A << endl;

	

}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}

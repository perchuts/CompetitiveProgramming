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

void solve(){
	int aa, bb; cin >> bb >> aa;
	double raio = aa, hypo = bb, pi = acos(-1);
	auto get_volume = [&] (double theta) {
		return hypo * ((hypo*sin(theta)+raio)*(hypo*sin(theta)+raio) + (hypo*sin(theta)+raio)*raio + raio*raio) * cos(theta);
	};
	double l = 0, r = pi/2;
	while (r-l > 1e-10) {
		double theta1 = l + (r-l)/3;
		double theta2 = r - (r-l)/3;
		if (get_volume(theta1) <= get_volume(theta2)) l = theta1;
		else r = theta2;
	}
	cout << fixed << setprecision(10) << l+(pi/2) << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}

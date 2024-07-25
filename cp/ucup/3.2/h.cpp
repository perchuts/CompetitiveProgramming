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
const double eps = 1e-5;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

void solve(){
	int n, k; cin >> n >> k;
	vector<double> v(n);
	for (auto& x : v) cin >> x;
	vector<int> bit(n + 1);
	auto insert = [&] (int x, int y) {
		for (; x <= n; x += x&(-x)) ckmax(bit[x], y);	
	};
	auto query = [&] (int x) {
		int ans = 0;
		while (x) {
			ckmax(ans, bit[x]), x -= x&(-x);
		}
		return ans;
	};
	auto possible = [&] (double avg) {
		vector<double> tv = v;
		for (auto& x : tv) x -= avg;
		//for (auto x : tv) cout << x << ' '; 
		//cout << endl;
		for (int i = 1; i < n; ++i) tv[i] += tv[i-1];
		//for (auto x : tv) cout << x << ' '; 
		//cout << endl;
		// basicamente quero splitar tv em k intervalos de soma nao negativa!
		// isso eh equivalente a ver se o maximo de segmentos em que da pra splitar eh >= k
		vector<int> ord(n), pos(n); iota(all(ord), 0);
		sort(all(ord), [&] (int x, int y) {
			if (tv[x] == tv[y]) return x < y;
			return tv[x] < tv[y];
		});
		//for (auto x : ord) cout << x << ' '; 
		//cout << endl;
		for (int i = 0; i < n; ++i) pos[ord[i]] = i+1, bit[i+1] = 0;
		for (int i = 0; i < n; ++i) {
			int my = query(pos[i]) + 1;
			if (my == 1 && tv[i] < 0.0) {
				//cout << "0 ";
				continue;
			}
			//cout << my << ' ';
			if ((i==n-1&&my>=k)||(i<n-1&&my>=k-1&&pos[n-1]>pos[i])) {
				//cout << "deu certo" << endl;
				return true;
			}	
			insert(pos[i], my);
		}
		//cout << endl;
		return false;
	};
	//possible(1.75);
	//return;
	double l = 0, r = 1000;
	while (r-l >= eps) {
		double md = (l + r) / 2;
		if (possible(md)) l = md;
		else r = md;
	}
	cout << fixed << setprecision(5) << r << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}

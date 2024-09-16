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

void solve(){
	int n; cin >> n;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	sort(all(a));
	int cost = a[0] * (n-1) * (n-1);
	for (int i = 1; i < n; ++i) cost += a[i];
	set<ii> tirar, colocar;
	vector<int> qt(n, 1);
	qt[0] = n - 1;
	auto update = [&] (int id) {
		if (qt[id] != 1) tirar.insert({a[id] * (-2*qt[id]+1), id});
		if (qt[id] != n-1) colocar.insert({a[id] * (2*qt[id]+1), id});
	};
	for (int i = 0; i < n; ++i) update(i);
	while (true) {	
		auto [x1, y1] = *begin(tirar);
		auto [x2, y2] = *begin(colocar);
		if (x1 + x2 >= 0) break;
		tirar.erase(begin(tirar)), colocar.erase(begin(colocar));
		qt[y1]--, qt[y2]++;
		cost += x1 + x2;
		update(y1), update(y2);
	}
	cout << cost << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}

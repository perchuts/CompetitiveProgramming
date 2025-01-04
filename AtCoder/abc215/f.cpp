#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
template<class T> struct minqueue {
	deque<pair<T, int>> q;

	void push(T x) {
		int ct = 1;
		while (q.size() and x < q.front().first)
			ct += q.front().second, q.pop_front();
		q.emplace_front(x, ct);
	}
	void pop() {
		if (q.back().second > 1) q.back().second--;
		else q.pop_back();
	}
	T min() { return q.back().first; }
};

void solve(){
	int n; cin >> n;
	vector<ii> v(n);
	for (auto& [x, y] : v) cin >> x >> y;
	sort(all(v));
	auto possible = [&] (int d) {
		vector<iii> ev;
		minqueue<int> setter_desgracado;
		minqueue<int> setter_desgracado2;
		for (int i = 0; i < n; ++i) {
			setter_desgracado.push(v[i].second);
			setter_desgracado2.push(-v[i].second);
		}
		for (int i = 0; i < n; ++i) {
			ev.pb({v[i].first-d, -1, 0});
			ev.pb({v[i].first+d+1, 1, v[i].second});
			ev.pb({v[i].first, 2, v[i].second});
		}
		sort(all(ev));
		for (auto [x, y, z] : ev) {
			if (y == -1) {
				setter_desgracado.pop();
				setter_desgracado2.pop();
			} else if (y == -1) {
				setter_desgracado.push(z);
				setter_desgracado2.push(z);
			} else {
				if (setter_desgracado.q.empty()) continue;
				int X = setter_desgracado.min();
				int Y = -setter_desgracado2.min();
				if (X < z - d or z + d < X) return true; 
				if (Y < z - d or z + d < Y) return true; 
			}
		}
		return false;
	};
	int l = 0, r = 1e9, ans = 0;
	while (l <= r) {
		int md = l + (r-l+1)/2;
		if (possible(md)) ans = md+1, l = md+1;
		else r = md-1;
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define STRESS

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

pair<vector<ii>, vector<int>> solve(int n, vector<int> a){
	int mx = 0, id = 0;
	vector<vector<int>> freq(n+1);
	for (int i = 0; i < n; ++i) {
		if (ckmax(mx, a[i])) id = i;
		freq[a[i]].pb(i);
	}
	vector<ii> ans(n+1);
	vector<int> order, used(n+1), who(n+1), ans2(n+1);
	int zero = -1;
	if (!freq[0].empty()) {
		zero = freq[0][0];	
		if (mx >= n/2) {
			order.pb(zero+1);
			order.pb(id+1);
			for (int i = 1; i <= n; ++i) if (i != zero+1 and i != id+1) order.pb(i);	
			int cur = 1;
			for (auto i : order) {
				if (i == zero+1) {
					ans[i] = {1, n/2+1};
					who[n/2+1] = ans2[i] = zero+1;
					used[n/2+1] = 1;
					continue;
				}
				while (used[cur]) cur++;
				if (a[i-1] >= n/2) {
					ans[i] = {1 + a[i-1] - abs(cur - n/2-1), cur};
					ans2[i] = zero+1;
				} else {
					if (a[i-1] == 0) {
						ans[i] = {1, cur};
						ans2[i] = i;
					} else {
						if (a[i-1] <= used[cur-1]) ans[i] = {used[cur-1]-a[i-1]+1, cur};
						else ans[i] = {used[cur-1]+a[i-1]-1, cur}; 
						ans2[i] = who[cur-1];
					}
				}
				used[cur] = ans[i].first;
				who[cur] = i;
				assert(1 <= used[cur] && used[cur] <= n);
			}
		} else {
			order.resize(n);
			iota(all(order), 1);
			swap(order[zero], order[0]);
			int cur = 1;
			for (auto i : order) {
				while (used[cur]) cur++;
				if (a[i-1] == 0) {
					ans[i] = {1, cur};
					ans2[i] = i;
				} else {
					if (a[i-1] <= used[cur-1]) ans[i] = {used[cur-1]-a[i-1]+1, cur};
					else ans[i] = {used[cur-1]+a[i-1]-1, cur}; 
					ans2[i] = who[cur-1];
				}
				used[cur] = ans[i].first;
				who[cur] = i;
				assert(used[cur] <= n);
			}
		}
	} else {
		int x = -1, y = -1;
		for (int i = 1; i <= n; ++i) {
				if (sz(freq[i]) > 1) {
				x = freq[i][0], y = freq[i][1];
			}
		}
		if (x == -1) {
			if (n == 2) {
				cout << "NO" << endl;
				exit(0);
			}
			for (int i = 1; i <= n; ++i) {
				int j = freq[i][0];
				assert(!freq[i].empty());
				if (i == 1) {
					ans2[j+1] = freq[2][0]+1;
					ans[j+1] = {n, n};
				} else if (i == 2) {
					ans2[j+1] = freq[3][0]+1;
					ans[j+1] = {n,n-1};
				} else { 
					ans[j+1] = {n-1, n-i+1};
					ans2[j+1] = freq[1][0]+1;
				}
			}
			return {ans, ans2};
		}
		assert(x != -1);
		ans[x+1] = {1, n/2+1};
		ans[y+1] = {a[y], n/2};
		ans2[x+1] = y+1, ans2[y+1] = x+1;
		used[n/2+1] = 1, used[n/2] = a[y];
		who[n/2] = y+1, who[n/2+1] = x+1;
		vector<int> falta, esq, dir;
		for (int i = 1; i <= n; ++i) if (i != x+1 and i != y+1) falta.pb(i);
		for (int i = 1; i < n/2; ++i) esq.pb(i);
		for (int i = n; i >= n/2+2; --i) dir.pb(i);
		while (!falta.empty()) {
			int i = falta.back(); falta.pop_back();
			int cur, prv;
			if (!esq.empty()) cur = esq.back(), esq.pop_back(), prv = cur+1;
			else cur = dir.back(), dir.pop_back(), prv = cur-1;
			assert(used[cur] == 0);
			if (a[i-1] >= n/2) {
				ans[i] = {1 + a[i-1] - abs(cur - n/2-1), cur};
				ans2[i] = x+1;
			} else {
				if (a[i-1] == 0) {
					ans[i] = {1, cur};
					ans2[i] = i;
				} else {
					if (a[i-1] <= used[prv]) ans[i] = {used[prv]-a[i-1]+1, cur};
					else ans[i] = {used[prv]+a[i-1]-1, cur}; 
					ans2[i] = who[prv];
				}
			}
			used[cur] = ans[i].first;
			who[cur] = i;

		}
	}
	return make_pair(ans, ans2);
}	

int32_t main(){_
#ifdef STRESS
	int t = 1;
	while (true) {
		int n = rnd(3, 15);
		vector<int> a(n);
		iota(all(a), 1);
		shuffle(all(a), rng);
		auto [pos, ass] = solve(n, a);
		bool ok = 1;
		for (int i = 1; i <= n; ++i) {
			auto [x1, y1] = pos[i];
			auto [x2, y2] = pos[ass[i]];
			if (abs(x1-x2)+abs(y1-y2) != a[i-1]) {
				cout << "Wrong answer on test " << t << endl;
				cout << n << endl;
				for (auto x : a) cout << x << ' ';
				cout << endl;
				cout << "house number " << i << " has a unmatched distance!" << endl;
				cout << "Your output: " << endl;
				for (int i = 1; i <= n; ++i) {
					cout << pos[i].first << ' ' << pos[i].second << endl;
				}
				for (int i = 1; i <= n; ++i) cout << ass[i] << ' ';
				cout << endl;
				exit(0);
			}
		}
		vector<int> used(n+1);
		for (int i = 1; i <= n; ++i) {
			ok &= (used[pos[i].second] == 0);
			used[pos[i].second] = 1;
			ok &= (1 <= pos[i].first && pos[i].first <= n);
			ok &= (1 <= pos[i].second && pos[i].second <= n);
		}
		if (ok == 0) {
				cout << "Wrong answer on test " << t << endl;
				cout << n << endl;
				for (auto x : a) cout << x << ' ';
				cout << endl;
				cout << "Output in wrong format!!" << endl;
				cout << "Your output: " << endl;
				for (int i = 1; i <= n; ++i) {
					cout << pos[i].first << ' ' << pos[i].second << endl;
				}
				for (int i = 1; i <= n; ++i) cout << ass[i] << ' ';
				cout << endl;
				exit(0);

		}
		cout << "Accepted on test " << t++ << endl;
	}
#endif
	int n; cin >> n;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	auto [pos, ass] = solve(n, a);
	if (pos.empty()) {
		cout << "NO" << endl;
		exit(0);
	}		
	cout << "YES" << endl;
	for (int i = 1; i <= n; ++i) {
		cout << pos[i].second << ' ' << pos[i].first << endl;
	}
	for (int i = 1; i <= n; ++i) cout << ass[i] << ' ';
	cout << endl;
}

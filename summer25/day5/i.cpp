#include <bits/stdc++.h>
using namespace std;
//#define stress
#define fast_io cin.tie(0)->sync_with_stdio(0);
//#define endl '\n'
typedef long long ll;

vector<int> solve(int n, int m, vector<int> p, vector<pair<int, int>> qry) {
	vector<int> cnt(n+1);
	vector<vector<tuple<int, int, int>>> queries(4*n+5);
	vector<pair<int, int>> bigs(m);
	vector<vector<int>> freq(n+1), get(n+1);
	vector<int> ans(m);
	const int MAGIC = 200;
	for (int i = 0; i < n; ++i) freq[p[i]].push_back(i);
	for (int i = 0; i < m; ++i) {
		auto& [l, r] = qry[i];
		--l, --r;
		if (r-l+1 <= MAGIC) {
			int big = 0;
			for (int j = l; j <= r; ++j) {
				cnt[p[j]]++;
				if (big < cnt[p[j]]) ans[i] = p[j], big = cnt[p[j]];
			}
			if (2*big <= r-l+1) ans[i] = 0;
			for (int j = l; j <= r; ++j) cnt[p[j]] = 0;
			continue;
		}
		int lx = 0, rx = n-1, id = 1;
		while (true) {
			int mid = (lx+rx)/2;
			if (l <= mid and mid <= r) {
				queries[id].push_back({l, r, i});	
				break;
			}
			if (r <= mid) rx = mid, id = 2*id;
			else lx = mid+1, id = 2*id+1; 
		}
	}
	auto conquer = [&] (auto&& self, int id, int l, int r) -> void {
		if (r-l+1 <= MAGIC) return;
		int mid = (l+r)/2;
		for (auto [a, b, id_q] : queries[id]) {
			//cout << "pergunta: " << id << ' ' << a << ' ' << b << ' ' << id_q << endl;
			assert(l <= a and a <= mid and mid <= b and b <= r);
			get[a].push_back(id_q);
			get[b].push_back(id_q);
		}
		pair<int, int> best = {cnt[p[mid]], p[mid]};
		for (int i = mid; i >= l; --i) {
			cnt[p[i]]++;	
			if (cnt[p[i]] > best.first) best = {cnt[p[i]], p[i]};
			for (auto id_q : get[i]) bigs[id_q].first = best.second;
		}
		for (int i = l; i <= mid; ++i) cnt[p[i]] = 0;
		best = {cnt[p[mid+1]], p[mid+1]};
		for (int i = mid+1; i <= r; ++i) {
			cnt[p[i]]++;	
			if (cnt[p[i]] > best.first) best = {cnt[p[i]], p[i]};
			for (auto id_q : get[i]) bigs[id_q].second = best.second;
		}
		for (int i = l; i <= r; ++i) get[i].clear(), cnt[p[i]] = 0;
		self(self, 2*id, l, mid), self(self, 2*id+1, mid+1, r);
	};
	conquer(conquer, 1, 0, n-1);
	auto qt_range = [&] (int x, int l, int r) {
		return upper_bound(begin(freq[x]), end(freq[x]), r) - lower_bound(begin(freq[x]), end(freq[x]), l);
	};
	for (int i = 0; i < m; ++i) {
		auto [l, r] = qry[i];
		if (r-l+1 <= MAGIC) continue;
		int x1 = qt_range(bigs[i].first, l, r), x2 = qt_range(bigs[i].second, l, r);
		if (2*x1 > r-l+1) ans[i] = bigs[i].first;
		else if (2*x2 > r-l+1) ans[i] = bigs[i].second;
	}
	return ans;
}
mt19937 rng(time(0));
int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

vector<int> brute(int n, int m, vector<int> p, vector<pair<int, int>> qry) {
	vector<int> ans;
	vector<int> cnt(n+1);
	for (auto [x, y] : qry) {
		--x, --y;
		int big = 0, id = -1;
		for (int i = x; i <= y; ++i) {
			cnt[p[i]]++;
			if (cnt[p[i]] > big) big = cnt[p[i]], id = p[i];
		}
		for (int i = x; i <= y; ++i) cnt[p[i]] = 0;
		if (2*big > y-x+1) ans.push_back(id);
		else ans.push_back(0);
	}
	return ans;
}

int main() {
	fast_io;
#ifdef stress
	int t = 1;
	while (true) {
		int n = rnd(1, 2000), m = rnd(1, 100);
		vector<int> p(n);
		for (auto& x : p) x = rnd(1, min(2, n));
		vector<pair<int, int>> qry(m);
		for (auto& [x, y] : qry) x = rnd(1, n), y = rnd(x, n);
		auto my = solve(n, m, p, qry);
		auto br = brute(n, m, p, qry);
		if (my != br) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << ' ' << m << endl;
			for (auto x : p) cout << x << ' ';
			cout << endl;
			for (auto [x, y] : qry) cout << x << ' ' << y << endl;
			cout << "Your output: " << endl;
			for (auto x : my) cout << x << ' ';
			cout << "Answer: " << endl;
			for (auto x : br) cout << x << ' ';
			cout << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#else
	int n, m; cin >> n >> m;
	vector<int> p(n);
	vector<pair<int, int>> qry(m);
	for (auto& x : p) cin >> x;
	for (auto& [x, y] : qry) cin >> x >> y;
	auto ans = solve(n, m, p, qry);
	for (auto x : ans) cout << x << endl;
#endif
}


#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
//#define endl '\n'
//#define gato
typedef long long ll;

const int INF = 2e18;

template<typename T> struct color {
	set<tuple<int, int, T>> se;

	vector<tuple<int, int, T>> update(int l, int r, T val) {
		auto it = se.upper_bound({r, INF, val});
		if (it != begin(se) and get<1>(*prev(it)) > r) {
			auto [L, R, V] = *--it;
			se.erase(it);
			se.emplace(L, r, V), se.emplace(r+1, R, V);
		}
		it = se.lower_bound({l, -INF, val});
		if (it != begin(se) and get<1>(*prev(it)) >= l) {
			auto [L, R, V] = *--it;
			se.erase(it);
			se.emplace(L, l-1, V), it = se.emplace(l, R, V).first;
		}
		vector<tuple<int, int, T>> ret;
		for (; it != end(se) and get<0>(*it) <= r; it = se.erase(it))
			ret.push_back(*it);
		se.emplace(l, r, val);
		return ret;
	}
};

int solve(int n, vector<tuple<int, int, int>> v) {
	auto v2 = v;
	for (auto& [x, y, z] : v2) {
		swap(x, z);
		swap(y, z);
	}
	v = v2;
	sort(rbegin(v), rend(v));
	color<int> E;
	E.update(0, INF, INF);
	for (auto [tam, l, r] : v) E.update(l, r-tam, tam);
	auto stt = E.se;
	int ans = 0, pos = 0;
	vector<tuple<int, int, int>> st(begin(stt), end(stt));
	int ptr = 0;
	while (ptr < st.size()) {
		auto [l, r, tam] = st[ptr];
		if (tam == INF or r < pos) {
			ptr++;
			continue;
		}
		pos = max(pos, l);
		int qt = (r-pos)/tam;
		pos += qt * tam, ans += qt;
		int ok = 0;
		for (int j = ptr+1; j < st.size(); ++j) {
			auto [l2, r2, tam2] = st[j];
			if (tam2 == INF) continue;
			if (pos + tam < l2) {
				ok = 1;
				pos += tam;
				ans++;
				break;
			}
			if (l2 + tam2 <= pos + tam) {
				ok = 1;
				ptr = j;
				break;
			}
		}
		if (!ok) {
			ans++;
			pos += tam;
		}
	}
	return ans;
}

int brute(int n, vector<tuple<int, int, int>> v) {
	auto v2 = v;
	for (auto& [x, y, z] : v2) {
		swap(x, z);
		swap(y, z);
	}
	v = v2;
	sort(rbegin(v), rend(v));
	color<int> E;
	E.update(0, INF, INF);
	for (auto [tam, l, r] : v) E.update(l, r-tam, tam);
	vector<int> dp(1000);
	auto stt = E.se;
	vector<tuple<int, int, int>> st(begin(stt), end(stt));
	int ptr = st.size()-1;
	for (int i = 998; i >= 1; --i) {
		if (i < get<0>(st[ptr])) ptr--;
		auto [x, y, z] = st[ptr];
		dp[i] = dp[i+1];
		if (i <= y and i + z < 1000) dp[i] = max(dp[i], dp[i+z] + 1);
		
	}
	return dp[1];
}

int32_t main() {
	fast_io;
#ifdef gato
	int t = 1;
	while (true) {
		srand(t);
		int n = rand() % 10 + 1;
		vector<tuple<int, int, int>> v(n);
		for (auto& [x, y, z] : v) {
			x = rand() % 100 + 1;
			z = rand() % 100 + 1;
			y = rand() % 100 + x + z;
		}
		//if (t == 4) {

		//	cout << "Wrong answer on test " << t << endl;
		//	cout << n << endl;
		//	for (auto [x, y, z] : v) {
		//		cout << x << ' ' << y << ' ' << z << endl;
		//	}
		//	exit(0);

		//}
		int my = solve(n, v);
		int ans = brute(n, v);
		if (my != ans) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << endl;
			for (auto [x, y, z] : v) {
				cout << x << ' ' << y << ' ' << z << endl;
			}
			cout << "Your output: " << my << endl;
			cout << "Answer: " << ans << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#else
	int n; cin >> n;
	vector<tuple<int, int, int>> v(n);
	for (auto& [x, y, z] : v) cin >> x >> y >> z;
	brute(n, v);
	cout << solve(n, v) << endl;
#endif
}

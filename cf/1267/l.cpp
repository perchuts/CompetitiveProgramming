#include <bits/stdc++.h>
using namespace std;
//#define gato
#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
//#define endl '\n'
typedef long long ll;

vector<string> solve(int n, int l, int k, string s) {
	sort(begin(s), end(s));
	vector<string> ans(n);
	int used = 0, ptr = 0;
	while (ans[k-1].size() < l) {
		for (int i = ptr; i < k; ++i) ans[i] += s[used++];
		int nptr = -1;
		for (int j = k-1; j >= ptr; --j) {
			if (ans[j].back() != ans[k-1].back()) break;
			nptr = j;
		}
		ptr = nptr;
	}
	for (int i = 0; i < n; ++i) while (ans[i].size() < l) ans[i] += s[used++];
	return ans;
}

string brute(int n, int l, int k, string s) {
	sort(begin(s), end(s));
	string ans = "zzzzzzzzzzzzzzzzzzzzzzzzzzzz";
	do {
		vector<string> cur;
		for (int i = 0; i < l*n; i += l) {
			cur.push_back("");
			for (int j = i; j < i + l; ++j) cur.back() += s[j];
		}
		sort(begin(cur), end(cur));
		ans = min(ans, cur[k-1]);
	} while (next_permutation(begin(s), end(s)));
	return ans;
}
int32_t main() {
	fast_io;
#ifdef gato
	int t = 1;
	while (true) {
		srand(t);
		int n = rand() % 3 + 1, l = rand() % 3 + 1, k = rand() % n + 1;
		string s(n*l, 'a');
		for (auto& x : s) x = char('a' + rand() % 26);
		auto my = solve(n, l, k, s);
		auto my_resp = my[k-1];
		auto ans = brute(n, l, k, s);
		if (my_resp != ans) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << ' ' << l << ' ' << k << endl;
			cout << s << endl;
			cout << "Your output: " << my_resp << endl;
			cout << "Answer: " << ans << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#else
	int n, l, k; cin >> n >> l >> k;
	string s; cin >> s;
	auto ans = solve(n, l, k, s);
	for (auto x : ans) cout << x << endl;
#endif
}

#include <bits/stdc++.h>
using namespace std;

#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io
	int n; cin >> n;
	string s; cin >> s;
	vector<int> cnt(2);
	vector<char> ex(10);
	for (auto x : s) cnt[x-'0']++;
	vector<int> possible;
	for (int i = 'a'; i <= 'z'; ++i) possible.push_back(__builtin_popcount(i)), ex[__builtin_popcount(i)] = char(i);
	sort(begin(possible), end(possible));
	possible.erase(unique(begin(possible), end(possible)), end(possible));
	if (cnt[1] < 3*n or 6*n < cnt[1]) {
		cout << "NIE" << endl;
		return 0;
	}
	string ans(n, ex[3]);
	cnt[1] -= 3*n;
	int cur = 0;
	while (cnt[1] != 0) {
		int go = min(3, cnt[1]);
		cnt[1] -= go;
		ans[cur++] = ex[go+3];
	}
	cout << ans << endl;

}

#include <bits/stdc++.h>
//#define GATO
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int solve(int n, vector<int> a) {
	int ans = n;
	map<int, int> mp;
	for (int i = 0; i < n; i++) {
		ans += 2*mp[a[i] + i];
		//cout << i << " " << a[i] << " += " << 2*mp.count(a[i] + i) << endl;
		mp[a[i] + i]++;
	}

	mp.clear();
	//reverse(a.begin(), a.end());
	for (int i = 0; i < n; i++) {
		// a[i] - a[j] = n - i + j
		// a[i] + i - n = a[j] + j
		ans += 2*mp[a[i] + i - n];
		//cout << "+= " << 2*mp.count(a[i] + i) << endl;
		mp[a[i] + i]++;
	}

	return ans;
}

int brute(int n, vector<int> a) {
	int ans = 0;
	for (int it = 0; it < n; it++) {
		for (int i = 0; i < n; i++) ans += a[a[i]] == i;

		int x = a.front();
		a.erase(a.begin());
		a.push_back(x);
	}
	return ans;
}

int32_t main() {
#ifndef GATO
	fast_io;

	int n; cin >> n;
	vector<int> a(n);
	for (auto &i : a) cin >> i, --i;

	cout << solve(n, a) << endl;
#else

	srand(2);
	int t = 0;

	while (true) {
		int n = rand() % 10 + 1;
		vector<int> a(n);
		iota(a.begin(), a.end(), 0);
		random_shuffle(a.begin(), a.end());

		auto ans1 = solve(n, a);
		auto ans2 = brute(n, a);
		if (ans1 != ans2) {
			cout << n << endl;
			for (int i : a) cout << i+1 << " ";
			cout << endl;
			cout << ans1 << " " << ans2 << endl;

			break;
		}
		cout << "AC " << t++ << endl;
	}
#endif
}

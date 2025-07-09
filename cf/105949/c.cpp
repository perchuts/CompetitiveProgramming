#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;

	int n, q; cin >> n >> q;
	vector<double> e(n + 1);
	iota(e.begin(), e.end(), 0);

	vector<int> cnt(n + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 2*i; j <= n; j += i) {
			cnt[i]++;
			cnt[j]++;
		}
		cnt[i]++;
	}

	for (int it = 0; it < 100; it++) {
		vector<double> ne(n + 1, 0);
		for (int i = 1; i <= n; i++) {
			for (int j = 2*i; j <= n; j += i) {
				ne[j] += e[i - 1];
				ne[i] += e[j - 1];
			}
			ne[i] += e[i - 1];
			ne[i] /= cnt[i];
			ne[i] = min(ne[i], e[i - 1]);
			ne[i] += 1;
		}
		swap(e, ne);
	}

	//for (int i = 0; i <= n; i++) cout << e[i] << endl;
	
	while (q--) {
		int x; cin >> x;
		cout << fixed << setprecision(8) << e[x] << endl;
	}

}

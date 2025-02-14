#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int t; cin >> t;
	while (t--) {

		int n;
		cin >> n;

		vector<int> l(n), a(n), b(n);
		for (int i = 0; i < n; i++) {
			cin >> l[i] >> a[i] >> b[i];
		}

		vector<int> ob(n);
		iota(ob.begin(), ob.end(), 0);
		vector<int> oa = ob;

		sort(ob.begin(), ob.end(), [&] (int i, int j) {
			return b[i] > b[j];
		});

		sort(oa.begin(), oa.end(), [&] (int i, int j) {
			return a[i] > a[j];
		});

		bool ok = true;
		int j = 0;
		int tot = 0;
		for (int i = 0; i < n; i++) {
			tot -= b[ob[i]] * l[ob[i]];
			cout << "-" << l[ob[i]] << " " << b[ob[i]] << endl;
			while (j < n && a[oa[j]] >= b[ob[i]]) {
				tot += a[oa[j]] * l[oa[j]];
				cout << "+" << l[oa[j]] << " " << a[oa[j]] << endl;
				j++;
			}

			cout << i << " " << tot << endl;

			ok &= tot >= 0;
		}

		cout << (ok ? "TAK" : "NIE") << endl;
	}
}

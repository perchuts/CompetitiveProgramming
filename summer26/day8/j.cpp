#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

int32_t main() {_
	int n, p, q; cin >> n >> p >> q;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
	double l = 0, r = 1;
	auto get = [&] (double x1) {
		double mn = (1.0 - a[0]*x1)/(double)b[0];
		for (int i = 1; i < n; ++i) mn = min(mn, (1.0 - a[i]*x1)/(double)b[i]);
		double ans = (double)p * x1 + (double) q * mn;
		return ans;
	};
	for (int i = 0; i < n; ++i) r = min(r, 1.0/(double)a[i]);
	for (int i = 0; i < 100; ++i) {
		double m1 = l + (r-l)/3, m2 = r - (r-l)/3;
		if (get(m1) > get(m2)) r = m2;
		else l = m1;
	}
	cout << fixed << setprecision(8) << get(l) << endl;
}

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;
using ld = long double;

int32_t main() {_
	
	int n, k; cin >> k >> n;

	vector<int> a(k), b(n);
	int mx = -1e10;
	for(auto& x : a) cin >> x, mx = max(mx, x);
	for(auto& x : b) cin >> x;
	sort(begin(a), end(a)), sort(begin(b), end(b));
	vector<ld> m(n+1);
	ld y = a[k-1];
	vector<int> suf(n+1);
	suf[n-1] = b[n-1];
	for (int i = n-2; i >= 0; --i) suf[i] = suf[i+1] + b[i];
	cout << fixed << setprecision(10);
	if (k == 1) {
		ld opt = max<ld>(a[0], ld(suf[0])/n);
		cout << opt << endl;
		exit(0);
	}
	m[n-1] = ld(k-1)/ld(n);
	ld p = m[n-1];
	for (int i = n-2; i >= 0; --i) {
		m[i] = m[i+1]*ld(i-k+3)/ld(i+1);
		p += m[i];
	}
	ld ans = 0;
	for (int i = n-1; ~i; --i) {
		ld opt = max<ld>(y, ld((i-k+2)*b[i] + suf[i+1])/(n-k+1));
		ans += opt * m[i];
	}
	cout << fixed << setprecision(10) << ans << endl;


}

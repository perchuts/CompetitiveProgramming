#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	int a, b, c, n; cin >> a >> b >> c >> n;
	int A = a, B = b, C = c;
	int g = gcd(a, n);
	a /= g, n /= g;
	g = gcd(b, n);
	b /= g, n /= g;
	g = gcd(c, n);
	c /= g, n /= g;
	if (n != 1) {
		cout << -1 << endl;
		exit(0);
	}
	cout << (A/a)-1 << " " << (B/b)-1 << " " << (C/c)-1 << endl;
}

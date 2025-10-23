#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int v, e; cin >> v >> e;
	int f = - v + e + 2;
	if(3*f == 2*e) cout << "YES" << endl;
	else cout << "NO" << endl;

}

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
using namespace std;

using ll = long long;

int32_t main() {_ 
	int n; cin >> n;
	int p = 0, i = 0;
	for (int j = 0; j < n; ++j) {
		int x; cin >> x;
		if (x & 1) i += (x+1)/2;
		else p += x/2;
	}
	cout << (p > i ? "Duke" : "Alice") << endl;

}

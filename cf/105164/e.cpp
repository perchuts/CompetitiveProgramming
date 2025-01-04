#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int k, a, b;
	cin >> a >> b >> k;

	for (int i = 1; i <= k; i++)
		cout << a * i + b << " \n"[i == k];
}

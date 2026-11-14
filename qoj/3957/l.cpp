#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

int32_t main() {_
	int n, k;
	cin >> n >> k;
	string s(n, 'd');
	for (int i = k; i < n; i++) {
		s[i] = 'a' + (i - k) % 3;
	}
	cout << s << endl;
}

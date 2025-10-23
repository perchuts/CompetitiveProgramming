#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;

	string s; cin >> s;

	bool ok = false;
	for (int i = 0; i <= s.size(); i++) {
	for (int j = i; j <= s.size(); j++) {
	for (int k = j; k <= s.size(); k++) {
		ok |= s[i] == 'T' && s[j] == 'A' && s[k] == 'P';
	}
	}
	}

	cout << (ok ? "S" : "N") << endl;
}

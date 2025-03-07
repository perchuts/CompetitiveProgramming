#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

bool isop(char x) {
	return x == '+' || x == '-' || x == '=';
}

bool eval(string s) {
	int n = s.size();

	bool ok = true;
	ok &= !(s[0] == '0' && !isop(s[1]));
	ok &= !isop(s[0]);
	for (int j = 0; j < n; j++) {
		if (s[j] == '=') ok &= j != n - 1;
		if (j + 1 < n && isop(s[j]) && isop(s[j + 1])) ok = false;
		if (j + 2 < n) {
			if (isop(s[j]) && s[j + 1] == '0' && !isop(s[j + 2])) ok = false;
		}
	}
	if (!ok) return false;

	int tot = 0;

	bool after = 0;
	for (int l = 0, r = 0; l < n; l = r) {
		while (r < n && isop(s[l]) == isop(s[r])) r++;
		after |= s[l] == '=';

		if (isop(s[l])) continue;
		
		if (r - l > 10) return false;

		bool plus = true;
		if (l > 0 && s[l - 1] == '-') plus = false;	
		
		tot += (after ^ plus ? 1 : -1) * stoll(s.substr(l, r - l));
	}

	return tot == 0;
}

int32_t main() {
	fast_io;
	
	string s; cin >> s;
	if (eval(s)) {
		cout << "Correct" << endl;
	} else {

		int n = s.size();
		for (int i = 0; i < n; i++) {
			if (isop(s[i])) continue;

			string t = s; 
			t.erase(t.begin() + i);
			for (int j = 0; j <= t.size(); j++) {
				string nt = t.substr(0, j);
				nt += s[i];
				nt += t.substr(j);

				if (eval(nt)) {
					cout << nt << endl;
					return 0;
				}
			}
		}

		cout << "Impossible" << endl;
	} 
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

int32_t main() {
	fast_io;

	//using T = array<int, 3>; // {#A, #C, parity}

	string s; cin >> s;
	int n = s.size();

	vector<int> qt;
	vector<int> parity;

	for (int i = 0; i < n; i++) if (s[i] == 'B') {
		int l = i - 1, r = i + 1;
		while (l >= 0 && r < n && s[l] == 'A' && s[r] == 'C') l--, r++;

		if (i - l - 1 > 0) { qt.push_back(i - l - 1); parity.push_back(i % 2); }
	}
	int ans = 0, matei = 0;
	for (int i = 0; i < qt.size(); ++i) {
		//cout << qt[i] << ' ' << parity[i] << ' ' << matei << endl;
		if (parity[i] == 0) {// ruim
			ans += min(matei, qt[i]-1);
			matei++;
		} else {
			if (qt[i] == 1) {
				if (matei != 0) matei++;
				else ans++;
			} else {
				ans += min(matei + 1, qt[i]-1);
				matei++;
			}
			
		}
	}
	cout << ans + matei << endl;
	return 0;
}


#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;

	int n; cin >> n;
	map<string, int> mp;
	string x;	
	for (int i = 0; i < n; i++) {
		string s; cin >> s; mp[s]++;
		if (x.empty()) x = s;
		else if (mp[s] > mp[x]) x = s;
	}

	cout << x << endl;
}

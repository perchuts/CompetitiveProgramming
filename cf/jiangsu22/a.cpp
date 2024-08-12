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
	
	int n; cin >> n;
	map<string, vector<string>> mp;
	for (int i = 0; i < n; i++) {
		string a, b; cin >> a >> b;
		mp[a].emplace_back(b);
	}

	bool ok = false;
	for (auto [_, v] : mp) {
		for (int i = 0; i + 5 <= v.size(); i++) {
			set<string> st;
			for (int j = i; j < i + 5; j++)
				st.insert(v[j]);
			if (st.size() == 5) {
				ok = true;
				break;
			}
		}
	}

	cout << (ok ? "PENTA KILL!" : "SAD:(") << endl;

	return 0;
}

#include <bits/stdc++.h>
using namespace std;

//#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<vector<int>> sexo(1, vector<int>(26));
	int h = 1;
	for (int i = 0; i < n; ++i) {
		string s; cin >> s;
		reverse(begin(s), end(s));
		int cur = 0;
		for (auto x : s) {
			if (sexo[cur][x-'a'] == 0) {
				sexo[cur][x-'a'] = h++;
				sexo.push_back(vector<int>(26));
			}
			cur = sexo[cur][x-'a'];
		}
	}
	cout << h-1 << endl;
}

#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<string> grid(n);
	for (auto& x : grid) cin >> x;
	string s; cin >> s;
	vector<vector<char>> ans(n, vector<char>(n, '.'));
	int ptr = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				if (grid[j][k] != 'X') {
					if (ptr == n*n or ans[j][k] != '.') {
						cout << "invalid grille" << endl;
						exit(0);
					}
					ans[j][k] = s[ptr++];
				}
			}
		}
		vector<string> ngrid(n);
		for (auto& x : ngrid) {
			x = string(n, '.');
		}
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				ngrid[k][n-1-j] = grid[j][k];
			}
		}
		grid = ngrid;
	}
	if (ptr != n*n) {
		cout << "invalid grille" << endl;
		exit(0);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << ans[i][j];
		}
	}
	cout << endl;
}

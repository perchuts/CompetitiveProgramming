#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

int32_t main() {_
	int n = 14;
	vector<vector<int>> c(n, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			c[i][j] = rand() + 1;
			c[j][i] = c[i][j];
		}
	}
	vector<int> p(n);
	for (int i = 0; i < n; ++i) p[i] = rand();
	vector<int> ord(n); iota(begin(ord), end(ord), 0);
	sort(begin(ord), end(ord), [&] (int x, int y) {
			return p[x] < p[y];
			});
	int L = 0;
	for (int i = 0; i < n; ++i) L += c[ord[i]][ord[(i+1)%n]];
	cout << n << " " << L << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
}

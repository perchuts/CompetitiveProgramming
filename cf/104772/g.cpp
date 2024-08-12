#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define pb push_back
#define int long long

using namespace std;

using ll = long long;

int m;
int add(int a, int b) {
	a += b;
	if (a > m) a -= m;
	return a;
}

const int MAX = 2049;
int dp[MAX][MAX];

int32_t main() {_
	int n, p;
	cin >> n >> p >> m;

	int MX = n;
	while (MX&(MX-1)) MX++;

	dp[0][0] = 1;
	for (int l = 1; l <= n - p; l++) {
		for (int i = 0; i <= n - p - l; i++) {
			for (int x = 0; x < MX; x++) {
				dp[i + l][x ^ l] = add(dp[i + l][x ^ l], dp[i][x]);
			}
		}
		//for (int i = 0; i <= n - p; i++) {
		//	for (int x = 0; x < MX; x++)
		//		cout << dp[i][x] << " ";
		//	cout << endl;
		//}
		//cout << endl;
	}

	cout << dp[n - p][p] << endl;
}

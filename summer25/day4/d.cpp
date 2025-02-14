#include <bits/stdc++.h>
#define stirling string
#define sz(x) (int) x.size()
#define matrix vector<vector<int>>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io
	int n, M; cin >> n >> M;
	vector<string> s(n);
	for (auto& x : s) cin >> x;
	auto pi = [] (string ss) {
		int N = sz(ss);
		vector<int> p(N);
		for (int i = 1; i < N; ++i) {
			int j = p[i-1];
			while (j and ss[j] != ss[i]) j = p[j-1];
			if (ss[j] == ss[i]) j++;
			p[i] = j;
		}
		return p;
	};
	vector<vector<int>> kmp(n, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			// kmp[i][j] = maior sufixo de s[i] q eh prefixo de s[j]
			stirling NaimSS = s[j] + "#" + s[i];
			auto p = pi(NaimSS);
			if (i == j) kmp[i][j] = p[p.back()-1];
			else kmp[i][j] = p.back();
		};
	}
	auto printMatrix = [&] (matrix z) {
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cout << z[i][j] << " \n"[j==n-1];
	};
	matrix ans(n, vector<int>(n, 1e18)), m = ans;	
	int sexo = 0;
	ans[0][0] = -69420;
	auto mult = [&] (matrix a, matrix b) {
		if (a[0][0] == -69420) return b;
		matrix resp(n, vector<int>(n, 1e18));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < n; ++k) {
					resp[i][j] = min(a[i][k] + b[k][j] - (int)s[k].size(), resp[i][j]);	
				}
			}
		}
		matrix resp2(n, vector<int>(n, 1e18));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < n; ++k) {
					resp2[i][k] = min(resp2[i][k], resp[i][j] + (int) s[k].size() - kmp[j][k]);
				}
			}
		}
		return resp2;
	};
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) m[i][j] = 1e18;
	for (int i = 0; i < 30; ++i) {
		if (i == 0) {
			for (int j = 0; j < n; ++j) m[j][j] = s[j].size();
		} else if (i == 1) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < n; ++k) {
					m[j][k] = (int) s[j].size() + (int) s[k].size() - kmp[j][k];
				}
			}
		}
		if (M >> i & 1) ans = mult(ans, m); 
		if (i >= 1) m = mult(m, m);
	}
	int mvkaio = 1e18;
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) mvkaio = min(mvkaio, ans[i][j]);
	cout << mvkaio << endl;
}

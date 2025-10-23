#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

void no() {
	cout << -1 << endl;
	exit(0);
}

const int MAXN = 61;
const int MAXK = 1010;
int mn[2][MAXK][MAXK];
int mx[2][MAXK][MAXK];
int ndp[MAXK][MAXK];
const int INF = 1e18;

bool chmin(int& a, int b) {
	if (a > b) { a = b; return true; }
	return false;
}

bool chmax(int& a, int b) {
	if (a < b) { a = b; return true; }
	return false;
}

int32_t main() {
	fast_io;

	int n, k, p; cin >> n >> k >> p;
	vector<int> c(n), w(n);
	for (int i = 0; i < n; i++) {
		cin >> c[i] >> w[i];
	}

	if (p % c[0]) no();
	p /= c[0];
	for (int i = 1; i < n; i++) c[i] /= c[0];
	c[0] /= c[0];

	auto reset = [&] (int id) {
		for (int j = 0; j <= k; j++) for (int qt = 0; qt <= k; qt++) mn[id][j][qt] = INF;
		for (int j = 0; j <= k; j++) for (int qt = 0; qt <= k; qt++) mx[id][j][qt] = -INF;
	};
	reset(0);
	mn[0][0][0] = 0;
	mx[0][0][0] = 0;

	vector<int> res;

	vector<int> a, b;
	for (int i = 0; i < n; i++) {
		int prv = i&1, nxt = 1-prv;
		reset(nxt);
		for (int diag = 0; diag <= k; diag++) {
			{
				int best = INF;
				for (int j = 0; diag + j <= k; j++) {
					int qt = diag + j;
					best = min(best, mn[prv][j][qt] - j*w[i]);
					chmin(mn[nxt][j][qt], best + j * w[i]);
				}
			}
			{
				int best = -INF;
				for (int j = 0; diag + j <= k; j++) {
					int qt = diag + j;
					best = max(best, mx[prv][j][qt] - j*w[i]);
					chmax(mx[nxt][j][qt], best + j * w[i]);
				}
			}
		}

		if (i + 1 < n) { // minplus
			int np = p % c[i + 1];
			for (int j = 0; j <= k; j++) for (int qt = 0; qt <= k; qt++) ndp[j][qt] = INF;
			for (int j = 0, nj = 0; j <= k; j++) {
				for (int qt = 0; qt <= k; qt++) {
					int dx = c[i + 1] / c[i];
					if (nj == np) if ((j/dx) <= k) chmin(ndp[j / dx][qt], mn[nxt][j][qt]);
				}
				nj += c[i];
				if (nj >= c[i + 1]) nj -= c[i + 1];
			}
			for (int j = 0; j <= k; j++) {
				for (int qt = 0; qt <= k; qt++) {
					mn[nxt][j][qt] = ndp[j][qt];
				}
			}
		}


		if (i + 1 < n) { // maxplus
			int np = p % c[i + 1];
			for (int j = 0; j <= k; j++) for (int qt = 0; qt <= k; qt++) ndp[j][qt] = -INF;
			for (int j = 0, nj = 0; j <= k; j++) {
				for (int qt = 0; qt <= k; qt++) {
					int dx = c[i + 1] / c[i];
					if (nj == np)
						if ((j/dx) <= k) chmax(ndp[j / dx][qt], mx[nxt][j][qt]);
				}
				nj += c[i];
				if (nj >= c[i + 1]) nj -= c[i + 1];
			}
			for (int j = 0; j <= k; j++) {
				for (int qt = 0; qt <= k; qt++) {
					mx[nxt][j][qt] = ndp[j][qt];
				}
			}
			p -= (p % c[i + 1]);
		}
	}
	int fim = p / c[n - 1];
	if (fim > k) no();

	//cout << fim << endl;
	//for (int i = 0; i <= k; i++) {
	//for (int j = 0; j <= k; j++) {
	//	if (mn[n][i][j] >= INF) cout << "-\t";
	//	else cout << mn[n][i][j] << "\t";
	//}
	//cout << endl;
	//}

	if (mx[n&1][fim][k] < 0) no();

	cout << mn[n&1][fim][k] << " " << mx[n&1][fim][k] << endl;
}

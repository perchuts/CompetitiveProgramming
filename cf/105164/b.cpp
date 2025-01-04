#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;
const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}
int mul(int a, int b) { return a * b % MOD; }

struct Mat : vector<vector<int>> {
	int n, m;
	Mat(int _n, int _m, bool id=false) : n(_n), m(_m) {
		this->resize(n, vector<int>(m, 0));
		if (id) {
			for (int j = 0; j < m; j++) {
				(*this)[j][j] = 1;
			}
		}
	}
	Mat operator *(const Mat& ot) const {
		Mat ans(n, ot.m);
		for (int k = 0; k < ot.m; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					ans[i][k] = add(ans[i][k], mul((*this)[i][j], ot[j][k]));
		return ans;
	}
	Mat pot(int e) {
		Mat ans(n, n, true);
		Mat a = (*this);
		while (e) {
			if (e & 1)
				ans = ans * a;
			a = a * a;
			e /= 2;
		}
		return ans;
	}
};

void solve() {
	ll n; cin >> n;

	Mat A(20, 20);
	
	for (int i = 5; i < 20; i+=4) {
		A[0][i] = 3;
	}
	for (int i = 1; i < 20; i++) {
		A[i][i-1] = 1;
	}

	//for (int i = 0; i < 20; i++) {
	//	for (int j = 0; j < 20; j++) {
	//		cerr << A[i][j] << ' ';
	//	}
	//	cerr << endl;
	//}

	Mat v(20, 1);
	v[0][0] = 1;
	A = A.pot(n);
	v = A*v;
	ll ans = 0;
	for (int i = 0; i < 20; i++)
		ans = add(ans, v[i][0]);

	cout << ans << endl;
}

int32_t main() {
	fast_io;

	int ttt; cin >> ttt;
	while(ttt--) solve();
}

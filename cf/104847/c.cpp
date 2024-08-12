
#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int mex(vector<int> &A) {
	int n = A.size();
	vector<int> mark(n + 1, 0);
	int ans = 0;
	for (int x : A) {
		if (x <= n) {
			mark[x] = true;
		}
	}
	while (ans <= n && mark[ans]) ans++;

	return ans;
}

int32_t main() {
	fast_io;

	int n, k;
	cin >> n >> k;

	vector<int> A(n);
	for (auto &x : A) cin >> x;
	int cnt0 = count(A.begin(), A.end(), 0);
	int cnt1 = count(A.begin(), A.end(), 1);
	int cnt2 = count(A.begin(), A.end(), 2);

	//if (k == n) {
	//	vector<int> v;
	//	for (int x : A) v.push_back(x == 0 ? 1 : 0);
	//	cout << mex(v) << endl;
	//} else
	if (cnt0 >= k) {
		cout << 0 << endl;
	//} else if (cnt2) {
	//	cout << 1 << endl;
	} else if (cnt0 == 0) {
		cout << 1 << endl;
	} else if (cnt1 == 0) {
		cout << 2 << endl;
	}else {
		// k eh diferente de n
		// tem menos que k zeros
		// nao tem 2
		// tem 1
		// tem 0
		vector<vector<int>> occ(n + 1);	
		for (int i = 0; i < n; i++) {
			occ[A[i]].push_back(i);
		}

		int livres = 0;

		{
			int p1 = occ[1][0];
			int p0 = occ[0][0];
			if (p0 < p1) livres += p0;
			else livres += p1;
		}
		{
			int p1 = occ[1].back();
			int p0 = occ[0].back();
			if (p1 < p0) livres += n - p0 - 1;
			else livres += n - p1 - 1;
		}

		for (int i = 0; i + 1 < occ[1].size(); i++) {
			int l = occ[1][i];
			int r = occ[1][i + 1];
			int gap = 0, mx = 0;
			for (int j = l + 1; j < r; ++j) {
				if (A[j] == 0) gap = 0;
				else gap++;
				mx = max(mx, gap);
			}
			livres += mx;
		}
		if (livres + cnt1 >= k) cout << 1 << endl;
		else cout << 2 << endl;
	}
}


#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define pb push_back
#define int long long

using namespace std;

using ll = long long;

int solve(vector<int> A, vector<int> B) {
	int n = A.size();
	set<int> s(B.begin(), B.end());

	int ans = 0;
	for (int i = 0; i < n; i++, ans++) {
		auto it = s.upper_bound(A[i]);
		if (it == s.end()) break;
		s.erase(it);
	}

	return ans;
}


int32_t main() {_

	int n; cin >> n;
	vector<int> A(n), B(n);
	for (auto &x : A) cin >> x;
	for (auto &x : B) cin >> x;

	int r1 = n, l1 = n - solve(A, B);
	int l2 = 0, r2 = solve(B, A);
	int l = max(l1, l2);
	int r = min(r1, r2);

	cout << r - l + 1 << endl;
	for (int i = l; i <= r; i++)
		cout << i << " \n"[i == r];
}

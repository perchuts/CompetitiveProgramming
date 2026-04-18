#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

int32_t main() {_
	int n, d; cin >> n >> d;
	vector<int> a(n), b(n);
	for (auto& x : a) cin >> x, --x;
	for (auto& x : b) cin >> x, --x;
	vector<int> onde_a(n), onde_b(n);
	for (int i = 0; i < n; ++i) onde_a[a[i]] = i, onde_b[b[i]] = i;
	--d;
	int K = 0;
	for (int i = 0; i < n-1; ++i) {
		if (onde_a[b[i]] > onde_a[b[i+1]]) ++K;
	}
	auto undo = [&] (int pos) {
		if (pos == n-1) return;
		if (pos < 0) return;
		if (onde_a[b[pos]] > onde_a[b[pos+1]]) --K;	
	};
	auto redo = [&] (int pos) {
		if (pos == n-1) return;
		if (pos < 0) return;
		if (onde_a[b[pos]] > onde_a[b[pos+1]]) ++K;
	};
	int ans = onde_a[b[n-1]] + 1 + K*n - n;
	//cout << K << " ";
	cout << ans << endl;
	while (d--) {
		int c, x, y; cin >> c >> x >> y; --x, --y;
		if (c == 1) {
			// swappar a[x], a[y]
			// undoar tudo que envolve x, y	
			int p1 = onde_b[a[x]], p2 = onde_b[a[y]];
			//cout << "p1 = " << p1 << " p2 = " << p2 << endl;
			vector<int> penis = {p1-1, p1, p2-1, p2}; sort(begin(penis), end(penis)), penis.erase(unique(begin(penis), end(penis)), end(penis));
			for (auto i : penis) undo(i);
			//cout << "after undo: K = " << K << endl;
			swap(onde_a[a[x]], onde_a[a[y]]), swap(a[x], a[y]);
			for (auto i : penis) redo(i);
		} else {
			int p1 = x, p2 = y;
			vector<int> penis = {p1-1, p1, p2-1, p2}; sort(begin(penis), end(penis)), penis.erase(unique(begin(penis), end(penis)), end(penis));
			for (auto i : penis) undo(i);
			swap(onde_b[b[x]], onde_b[b[y]]), swap(b[x], b[y]);
			for (auto i : penis) redo(i);
		}
		ans = onde_a[b[n-1]] + 1 + K*n - n;
		//for (int i = 0; i < n; ++i) cout << a[i] << " ";
		//cout << endl;
		//for (int i = 0; i < n; ++i) cout << b[i] << " ";
		//cout << endl;
		cout << ans << endl;
	}
}

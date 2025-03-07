#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;

	int n; cin >> n;
	vector<int> a(n);
	for (auto &i : a) cin >> i;

	vector<int> nxt(n), prv(n);
	iota(nxt.begin(), nxt.end(), 1);
	iota(prv.begin(), prv.end(), -1);

	for (int i = 0; i < n; i++) {
		while (prv[i] >= 0 && a[prv[i]] <= a[i]) prv[i] = prv[prv[i]];
	}
	for (int i = n - 1; i >= 0; --i) {
		while (nxt[i] < n && a[nxt[i]] <= a[i]) nxt[i] = nxt[nxt[i]];
	}

	int ans = 0;
	int mx = *max_element(a.begin(), a.end());
	for (int i = 0; i < n; i++) {
		if (a[i] == mx) continue;
		if (prv[i] == -1) ans += nxt[i] - i;
		else if (nxt[i] == n) ans += i - prv[i];
		else ans += min(i-prv[i],nxt[i]-i);
	}
	cout << ans << endl;
}

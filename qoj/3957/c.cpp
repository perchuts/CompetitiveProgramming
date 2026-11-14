#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	const int cx = 30, cy = 30;
	cout << cx << " " << cy << endl;
	int x1, y1; cin >> x1 >> y1;
	int dx = 1, dy = 1;
	if (max(abs(cx-x1), abs(cy-y1)) > 2) {}
	else {
		if (x1 < cx) dx = 1;
		else dx = -1;
		if (y1 < cy) dy = 1;
		else dy = -1;
	}
	cout << cx + 2 * dx << " " << cy + 2 * dy << endl;
	int x2, y2; cin >> x2 >> y2;
	if (cx + dx != x2 or cy + dy != y2) {
		cout << cx + dx << " " << cy + dy << endl;
		int a, b; cin >> a >> b;
		assert(a == 0);
		return 0;
	}
	cout << cx << " " << cy + 2 * dy << endl;
	int x3, y3; cin >> x3 >> y3;
	if (x3 != cx or y3 != cy + dy) {
		cout << cx << " " << cy+dy << endl;
		int a, b; cin >> a >> b;
		assert(a == 0);
		return 0;
	} else {
		assert(x3 != cx + dx or y3 != cy + 2 * dy);
		cout << cx + dx << " " << cy + 2 * dy << endl;
		int a, b; cin >> a >> b;
		assert(a == 0);
		return 0;
	}
}

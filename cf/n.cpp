#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;
	array<int, 4> sexo;
	sexo[0] = sexo[2] = 1e9;
	for (int i = 0; i < n; ++i) {
		int xx, yy; cin >> xx >> yy;
		for (int dx : {-1, 1}) {
			for (int dy : {-1, 1}) {
				int x = dx + xx;
				int y = dy + yy;
				sexo[0] = min(sexo[0], x);
				sexo[2] = min(sexo[2], y);
				sexo[1] = max(sexo[1], x);
				sexo[3] = max(sexo[3], y);
			}
		}
	}
	cout << 2 * (sexo[3] - sexo[2] + sexo[1] - sexo[0]) << endl;
}

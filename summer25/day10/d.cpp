#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int t; cin >> t;
	while (t--) {
		map<int, int> vis;
		int n, m; cin >> n >> m;
		queue<int> q;
		if (n % 3) {
			cout << (n == m ? "YES" : "NO") << endl;
			continue;
		}
		if (n == m) {
			cout << "YES" << endl;
			continue;
		}
		q.push(n);
		bool ok = 0;
		while (!q.empty()) {
			auto u = q.front(); q.pop();
			int sexo = u/3;
			if (sexo == m or 2 * sexo == m) {
				ok = 1; break;
			}
			if (sexo % 3) continue;
			if (vis[sexo] == false) q.push(sexo), vis[sexo] = 1;
			if (vis[2*sexo] == false) q.push(2*sexo), vis[2*sexo] = 1;
		}
		cout << (ok ? "YES" : "NO") << endl;
	}
}

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
using namespace std;

int main(){_
	int n; cin >> n;
	int bichos = 0;
	while (n--) {
		char op; cin >> op;
		int x; cin >> x;
		if (op == 'B') {
			if (x > bichos) cout << "YES" << endl;
			else cout << "NO" << endl;
			bichos = max(0, bichos - x);
		} else {
			bichos += x;
		}
	}
}

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define pb push_back
#define int long long

using namespace std;

using ll = long long;

int32_t main() {_

	int a[4];
	int x, y, z, w;
	cin >> x >> y >> z >> w;
	a[0] = x; a[1] = y; a[2] = z; a[3] = w;
	int mx = -1;
	for(int j=1; j<4;j++){
		for(int k=1;k<4;k++){
			if(k==j) continue;
			for(int l=1;l<4;l++){
				if(l==k || l==j) continue;
				mx = max(mx, min(a[0], a[j])*min(a[k], a[l]));
			}
		}
	}
	cout << mx << "\n";
}

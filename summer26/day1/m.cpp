#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using ll = long long;
using namespace std;

int32_t main() {_
	int n; cin >> n;
	int cnt = 0;
	for(int i=0;i<n;i++){
		int x; cin >> x;
		if((x+i)%2 == 0) break;
		cnt++;
	}
	cout << n-cnt << endl;
}

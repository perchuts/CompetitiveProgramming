#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

int32_t main() {_
	int t; cin >> t;
	while (t--){
	int n; cin >> n;
	set<int> pres;
	int ma = 0;
	for (int i = 0; i < n; ++i){
		int x; cin >> x;
		pres.insert(x);
		ma = max(ma,x);
	}

	int w = 1;
	int i = 1;
	for (; ; ++i){
		if (!pres.count(i)) break;
		w ^= 1;
	}

	if (i == ma+1){
		if (pres.size()%2 == 0) cout << "Bob" << endl;
		else cout << "Alice" << endl;
		continue;
	}

	if (w) cout << "Alice" << endl;
	else cout << "Bob" << endl;
	}
	
}

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
using ll = long long;
using namespace std;

int main(){_
	int n, k; cin >> n >> k;
	vector<int> a(n);
	for(int i=0; i<n; i++) cin >> a[i];
	vector<int> b(n);
	for(int i=0; i<n; i++) cin >> b[i];

	ll tot = 0;
	for(int i=0; i<n; i++) tot += a[i]/b[i];
	if(tot < k){
		for(int i=0; i<n; i++) cout << 0 << ' '; cout << endl;
		return 0;
	}

	ll rest = k;
	for(int i=0; i<n; i++){
		ll sum = 0;
		for(int j=i+1; j<n; j++) sum += a[j]/b[j];
		int c = max(0ll, rest - sum);
		rest -= c;
		cout << c << ' ';
	}
	cout << endl;
}


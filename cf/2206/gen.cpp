#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

mt19937 rng(time(0));

int uniform(int l, int r){
	return uniform_int_distribution<int>(l,r)(rng);
}

int32_t main() {_
	int n = 200000, m = 10000;
	cout << n << " " << m << endl;
	for (int i = 0; i < n-m+1; ++i){
		cout << uniform(1,100000) << " ";
	}
	cout << endl;

	int q = 100000;
	cout << q << endl;
	while (q--){
		int l = uniform(1,n);
		int r = uniform(l,n);
		cout << l << " " << r << endl;
	}
}

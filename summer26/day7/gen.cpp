#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
using namespace std;

using ll = long long;

mt19937 rng(time(0));

int uniform(int l, int r){
	return uniform_int_distribution<int>(l,r)(rng);
}

int32_t main() {_
	int n = uniform(1,14), b = 1000, c = 100;
	cout << n << " " << b << " " << c << endl;
	for (int i = 0; i < n; ++i){
		cout << uniform(1,100) << " ";
	}
	cout << endl;

}

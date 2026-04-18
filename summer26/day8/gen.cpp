#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int uniform(int l, int r){
	return uniform_int_distribution<int>(l,r)(rng);
}

int32_t main() {_
	int n = 20, m = 20;
	cout << n << " " << m << endl;
	for (int i = 0; i < n+m; ++i){
		int le = uniform(1,20);
		string x = "";
		while (le--){
			x += uniform(0,25)+'a';
		}
		cout << x << endl;
	}
}

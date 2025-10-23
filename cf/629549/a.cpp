#include <bits/stdc++.h>
using namespace std;

#define int ll
//#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector grid(n, vector<int>(n));
	for(auto& l : grid) for(auto& c : l) cin >> c;

	using T = __int128;

	vector<T> a(n), b(n);
	for(int i=1;i<n-1;i++){
		a[i] = (grid[0][i-1] + grid[0][i+1] - 2*grid[0][i]) / 2;
	}
	for(int i=1;i<n-1;i++){
		b[i] = (grid[i-1][0] + grid[i+1][0] - 2*grid[i][0]) / 2;
	}

	a[0] = b[0] = (-2*grid[0][0] + grid[1][0] + grid[0][1]) / 2;


	// falta a[n-1] e b[n-1]
	{
		T aux = grid[0][n-1];
		for(int i=0;i<n-1;i++) aux -= a[i] * (n-1-i);
		for(int i=1;i<n-1;i++) aux -= b[i] * (n-1+i);
		assert(aux % (2*n-2) == 0);
		b[n-1] = aux/(2*n-2);
	}
	{
		T aux = grid[n-1][0];
		for(int i=0;i<n-1;i++) aux -= b[i] * (n-1-i);
		for(int i=1;i<n-1;i++) aux -= a[i] * (n-1+i);
		assert(aux % (2*n-2) == 0);
		a[n-1] = aux/(2*n-2);
	}

	vector ans(n, vector<int>(n));

	for(int i=1;i<n;i++){
		assert(a[i] >= 0);
		assert(b[i] >= 0);
		ans[0][i] = a[i];
		ans[i][0] = b[i];
	}
	ans[0][0] = a[0];
	

	for(int i=1;i<n;i++){
		for(int j=1;j<n;j++){
			T k = min({ans[0][i], ans[j][0], max<int>(0, -ans[0][0])});
			ans[0][0] += k;
			ans[0][i] -= k;
			ans[j][0] -= k;
			ans[j][i] += k;
		}
	}

	for(auto l : ans){
		for(auto c : l) cout << c << " ";
		cout << endl;
	}


}

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_

	int n, m; cin >> n >> m;
	if(n == 1 && m == 1){
		cout << "YES" << endl;
		cout << 1 << endl;
		return 0;
	}
	if(n == 3 && m == 3){
		cout << "YES" << endl;
		cout << "6 1 8" << endl;
		cout << "7 5 3" << endl;
		cout << "2 9 4" << endl;
		return 0;
	}
	if(max(n, m) <= 3){
		cout << "NO" << endl;
		return 0;
	};
	
	cout << "YES" << endl;
	int sw = 0;
	if(n > m){
		swap(n, m);
		sw = 1;
	}

	vector ans(n, vector<int>(m));

	if(m == 4){
		vector<int> c = {1, 3, 0, 2};
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				ans[i][j] = i*m + c[j];
			}
		}
		for(int i=0;i<n;i+=2){
			vector<int> tmp(m);
			for(int j=0;j<m;j++) tmp[j] = ans[i][m-1-j];
			swap(ans[i], tmp);
		}
	}
	else{
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				ans[i][j] = i*m + (2*j) % m + (m % 2 == 0) * (2*j >= m);
			}
		}

		if(m % 2 == 1){
			for(int i=0;i<n;i+=2){
				vector<int> tmp(m);
				for(int j=0;j<m;j++) tmp[j] = ans[i][(j+1)%m];
				swap(ans[i], tmp);
			}
		}
		else{

			for(int i=0;i<n;i+=2){
				vector<int> tmp(m);
				for(int j=0;j<m;j++) tmp[j] = ans[i][m-1-j];
				swap(ans[i], tmp);
			}

		}
	}

	if(sw){
		vector<vector<int>> tmp(m, vector<int>(n));
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				int x = ans[i][j];
				int xx = x / m;
				int xy = x % m;
				tmp[j][i] = xy * n + xx;
			}
		}
		swap(ans, tmp);
		swap(n, m);
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) cout << ans[i][j]+1 << " ";
		cout << endl;
	}
}

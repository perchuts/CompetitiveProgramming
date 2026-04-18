#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;
const int INF = 1e4;

array<int,2> dp[5100][5100];

int lca(int a, int b){
	if(a % 2 == 0 && b % 2 == 0 && a - b >= 4){
		a /= 2; b /= 2;
		if(a > 0 && b < 0) return 0;
		if(b >= 0) return 2*(b+1);
		if(a <= 0) return 2*(a-1);
		assert(0);
	}
	if(a % 2 == 0 && b % 2 == 0){
		assert(a > b);
		return (a+b)/2;
	}
	assert(a - b >= 2);
	if(a > 0 && b < 0) return 0;
	if(b >= 0){
		if(b&1) return b+1;
		return b + 2;
	}
	if(a <= 0){
		if(a&1) return a-1;
		return a-2;
	}
	assert(0);
}

int32_t main() {_
	
	int n, m; cin >> n >> m;
	// i: posicao do r
	// j: posicao do l
	for(int i=0;i<m;i++){
		for(int j=m-1;j>=0;j--){
			if(j == i) continue;
			array<int,2> a = {INF, 0}; // jogada do l (min de coisas, > b)
			array<int,2> b = {-INF, 0};

			if(j < m-1 && j+1 != i) a = dp[i][j+1];
			if(j < m-1 && j+1 == i && j+2 <= m-1) a = dp[i][j+2];

			if(i > 0 && i-1 != j) b = dp[i-1][j];
			if(i > 0 && i-1 == j && i-2 >= 0) b = dp[i-2][j];
			//cout << "calculando dp[" << i << "][" << j << "]" << endl;
			//cout << "opcoes: " << a[0] << "/" << a[1] << " " << b[0] << "/" << b[1] << endl;
			//cout << flush;
			if(a[0] > b[0]){
				dp[i][j] = {lca(a[0], b[0]), 0};
			}
			else{
				//cout << i << " " << j << endl;
				//cout << "AAAAAAAAAAAAAAAAAAAAAAA" << endl;
				assert(a[0] == b[0]);
				dp[i][j] = {a[0], 1};
			}
			//cout << "dp deu: " << dp[i][j][0] << "/" << dp[i][j][1] << endl;
			
		}
	}

	vector<int> ans(n), star(n);
	for(int i=0;i<n;i++){
		string s; cin >> s;
		int l = 0, r = 0;
		for(int j=0;j<m;j++){
			if(s[j] == 'b') l = j;
			if(s[j] == 'g') r = j;
		}

		ans[i] = dp[l][r][0];
		star[i] = dp[l][r][1];
	}

	for(int bm=0;bm<(1<<n);bm++){

		int a=0, b=0;
		for(int i=0;i<n;i++){
			if((bm>>i)&1) a += ans[i], b ^= star[i];
		}
		if(a > 0){
			cout << "bb";
		}
		if(a < 0){
			cout << "gg";
		}
		if(a == 0 && b == 0){
			cout << "bg";
		}
		if(a == 0 && b == 1){
			cout << "gb";
		}
	}
	cout << endl;
}

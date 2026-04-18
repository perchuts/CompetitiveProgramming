#include <bits/stdc++.h>
using namespace std;
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int long long

typedef long double ld;

const int lim = 101;
ld dp[110][110][110];
ld pref[110][110][110];
ld suf[110][110][110];
ld bino[220][220];

using T = array<ld,128>;

void limpa(T& c){

	for(int i=0;i<128;i++) c[i] = 0;
}
T conv(T a, T b){
	T c;
	limpa(c);
	for(int i=0;i<128;i++){
		for(int j=0;j<128;j++){
			c[i^j] += a[i] * b[j];
		}
	}
	return c;
}

int32_t main() {_
	cout << fixed << setprecision(6);
	bino[0][0] = 1;
	for(int i=1;i<2*lim;i++){
		bino[i][0] = 1;
		for(int j=1;j<2*lim;j++){
			bino[i][j] = bino[i-1][j-1] + bino[i-1][j];
		}
	}


	for(int b=0;b<lim;b++){
		dp[b][0][b] += 1;
	}
	for(int b=0;b<lim;b++){
		for(int l=1;l<=lim;l++){
			pref[b][0][l] = pref[b][0][l-1] + dp[b][0][l-1];
		}
		for(int l=lim-1;l>=0;l--){
			suf[b][0][l] = suf[b][0][l+1] + dp[b][0][l+1];
		}
	}
	for(int p=1;p<lim;p++){

		for(int b=0;b<lim;b++){

			for(int l=0;l<=b;l++){

				dp[b][p][l] += suf[b-l][p-1][l];
			}
			for(int l=0;l<=b-1;l++){
				dp[b][p][l] += pref[b-1-l][p-1][l];
			}

			for(int l=1;l<=lim;l++){
				pref[b][p][l] = pref[b][p][l-1] + dp[b][p][l-1];
			}
			for(int l=lim-1;l>=0;l--){
				suf[b][p][l] = suf[b][p][l+1] + dp[b][p][l+1];
			}
		}
	}

	for(int p=0;p<lim;p++){
		for(int b=0;b<lim;b++){
			for(int l=0;l<lim;l++){
				dp[b][p][l] /= bino[b+p][b];
			}
		}
	}

	int t; cin >> t;

	

	while(t--){
		int n; cin >> n;
		vector<int> p(n), b(n);
		for(auto& x : p) cin >> x;
		for(auto& x : b) cin >> x;

		T c;
		limpa(c);
		for(int i=0;i<n;i++){
			T d; limpa(d);
			for(int j=0;j<lim;j++){
				d[j] = dp[b[i]][p[i]][j];
			}
			T e = conv(c, d);
			swap(c, e);
		}
		cout << c[0] << endl;


	}


}

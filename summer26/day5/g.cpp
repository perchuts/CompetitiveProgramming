#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_
	int n, kk; cin >> n >> kk;
	int s, b; cin >> s >> b;
	auto ff = [&] (double i, double j){
		return i*s / (i*s + j*b);	
	};

	vector<int> v(n), w(n), g(n), h(n);
	for(int i=0;i<n;i++){
		int p, t; cin >> p >> t;
a		if(t == 0) v[p]++;
		else w[p]++;
	}
	for(int i=1;i<=n;i++){
		g[i] = g[i-1] + v[i-1];
		h[i] = h[i-1] + w[i-1];
	}

	int t0 = g[n], u0 = h[n];
	vector<double> f(kk+1);
	for(int p=0;p<=kk;p++){
		int m = kk-p;
		if(p > t0) continue;
		if(m > u0) continue;
		vector z(p+1, vector<double>(m+1));
		z[0][0] = 1;
		for(int x=0;x<=p;x++){
			for(int y=0;y<=m;y++){
				if(x>0) z[x][y] += z[x-1][y] * ff(t0-p+x, u0-m+y);
				if(y>0) z[x][y] += z[x][y-1] * (1-ff(t0-p+x, u0-m+y));
			}
		}
		f[p] = z[p][m];
	}

}

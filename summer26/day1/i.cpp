#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using ll = long long;
using namespace std;



int32_t main() {_

	int n, f; cin >> n >> f;
	
	vector<int> x(n), y(n);
	for(int i=0;i<n;i++){
		cin >> x[i] >> y[i];
	}

	double C = 0;
	for(int i=0;i<n;i++){
		C += x[i] * y[(i+1)%n] - x[(i+1)%n] * y[i];
	}
	cout << fixed << setprecision(12) ;
	double lb = -10000000, ub = 10000000;
	for(int ii=0;ii<80;ii++){
		double m = (ub + lb) / 2;
		vector<double> xx(n), yy(n);
		for(int i=0;i<n;i++) xx[i] = x[i] - m, yy[i] = y[i];

		double A = 0.0;
		for(int k=0;k<n;k++){
			int l = (k+1)%n;
			double x1 = xx[k], y1 = yy[k];
			double x2 = xx[l], y2 = yy[l];

			double B = x1*y2 - y1*x2;
			if(x1 == x2){
				if(x1 > 0) A += B;
				else A -= f*B;
			}
			else{
				A += x1 / (x1 - x2) * B * (x1 > 0 ? 1 : -f);
				A -= x2 / (x1 - x2) * B * (x2 > 0 ? 1 : -f);
			}
		}
		if(A*C<0) ub = m;
		else lb = m;
	}
	cout << fixed << setprecision(12) << lb << endl;
}

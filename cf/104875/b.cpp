#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

using ll = long long;

const int mod = 998244353;
const int inf = 2e9 + 100;
int h, r, A, W;

double f(double x){
	int L = 2*A*h;
	int T = A*h*h;
	int K = W - A;
	return (T+K*x*x)/(L+K*x);
}

int32_t main() {_
	
	cin >> h >> r >> A >> W;
	int L = 2*A*h;
	int T = A*h*h;
	int K = W - A;
	int del = L*L-4*K*(-T);
	if(del < 0){
		cout << fixed << setprecision(20) << 0.0 << endl;
		return 0;
	}
	double sqdel = sqrt(del);
	double x1 = (- L + sqdel)/(((double)K)*2);
	double x2 = (- L - sqdel)/(((double)K)*2);
//	cout << x1 <<  " " << x2 << endl;
	if(x1 > (double) h || x1 < 0.0){
		if(x2 > (double) h || x2 < 0.0){
			cout << 0.0 << endl;
			return 0;
		}
		cout << fixed << setprecision(20) << x2 << endl;
	}
		if(x2 > (double) h || x2 < 0.0){
			
			cout << fixed << setprecision(20) << x1 << endl;
			return 0;
		}
	if(f(x1) > f(x2)){
			cout << fixed << setprecision(20) << x1 << endl;
			return 0;
	}
	else 
			cout << fixed << setprecision(20) << x2 << endl;



	

}

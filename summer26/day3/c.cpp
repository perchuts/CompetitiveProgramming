#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define endl '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

#define P 998244353

using namespace std;

using ll = long long;

int pot(int b, int e){
	int r = 1;
	while(e){
		if(e&1) r = r * b % P;
		e /= 2; b = b * b % P;
	}
	return r;
}

void solve(){

	int d, k; cin >> d >> k;
	if(k == 0){
		if(d == 1) cout << 1 << endl;
		else cout << 0 << endl;
	}
	if(k == 1){
		if(d <= 2) cout << d << endl;
		else cout << 0 << endl;
	}
	if(k == 2){
		cout << d << endl;
	}
	if(k >= 3){
		if(d == 1){
			cout << 1 << endl;
		}
		else if( d % 2 == 0){
			int e = d/2;
			int f = k-1;
			cout << (2 * (pot(f, e) +P-1) * pot(f+P-1, P-2)) % P << endl;
		}
		else{
			int e = (d-1)/2;
			int f = k-1;
			cout << (1 + ((f+1) *(pot(f, e) +P-1) %P * pot(f+P-1, P-2))) % P << endl;
		}
	}
}

int32_t main() {_
	int t; cin >> t;
	while(t--) solve();
}

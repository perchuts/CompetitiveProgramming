#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
//#define endl '\n'
#define int long long
const int INF = 1e18;

int32_t main(){

	int n; cin >> n;
	n *= 8000000;
	int k=0;
	n--;
	while(n){
		k++;
		n /= 2;
	}
	cout << k << endl;
}

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

vector<int> a, b;
void solve(int n){
	if(n <=2){
		for(int i=1;i<=n;i++) a.push_back(i);
		for(int i=n;i>=1;i--) b.push_back(i);
		return;
	}
	for(int i=1;;i++){
		int m = n+i;
		int ok = 1;
		for(int j=2;j*j<=m;j++){
			if(m%j == 0){
				ok = 0;
				break;
			}
		}
		if(ok){
			for(int k=i;k<=n;k++) a.push_back(k);
			for(int k=n;k>=i;k--) b.push_back(k);
			solve(i-1);
			return;
		}
	}
}
int32_t main() {_
	int n; cin >> n;
	solve(n);
	for(auto x : a) cout << x << " ";
	cout << endl;
	for(auto x : b) cout << x << " ";
	cout << endl;
}

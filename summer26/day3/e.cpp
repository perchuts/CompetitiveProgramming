#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define endl '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

using ll = long long;
#define P 998244353

int lb;
int ans = 0;


map<array<int,3>, int> m; 

int solve(int suf, int falta,  int ult){
	array<int,3> c = {suf,falta,ult};
	auto p = m.find(c);
	if (p != m.end()) return p->second;
	int ans = 0;
	if(falta == 1) {
		//cout << suf << " " << ult << endl;
		if(suf <= ult) return 1;
		return 0;
	}
	for(int i=2;i <= suf;i++){
		if((suf/i*(falta-1)) < lb) break;
		if(suf % i) continue;
		if(suf/i > ult) continue;
		ans += solve(suf - suf/i, falta-1, suf/i);
	}
	return m[c] = ans;
	
}

int32_t main() {_
	int n, k; cin >> n >> k;
	if(k == 1){
		cout << 1 << endl;
		return 0;
	}
	lb = n / 1100;
	cout <<  solve(n, k, 2*n) << endl;
}

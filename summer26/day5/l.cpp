#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_
	vector<int> v(10000);
	for(int i=0;i<10000;i++) cin >> v[i];
	for(int b=64;b>=10;b-=2){
		vector<int> r(b-1);
		for(int i=0;i<b-1;i++){
			r[(i*i)%(b-1)]++;
		} 
		int cnt = 0;
		for(int i=0;i<b-1;i++) if(r[i]) cnt++;
		int ok = 1;
		vector<int> aparece(b-1);
		for(int i=0;i<10000;i++){
			if(r[v[i] % (b-1)] == 0) ok = 0;
			aparece[v[i] % (b-1)] = 1;
		}
		int sm = 0;
		for(auto x : aparece) sm++;
		if(ok){

			cout << b << endl;
			return 0;
		}
	}
}

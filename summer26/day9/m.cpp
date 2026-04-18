#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
using namespace std;

using ll = long long;
int e[200];
int32_t main() {_ 

	int b, d; cin >> b >> d;

	vector<int> pr;
	for(int bb=b, i=2; bb > 1;i++){
		while(bb % i == 0) pr.push_back(i), e[i]++, bb/=i;
	}

	if((b-1) % d == 0){
		cout << "3-type" << endl;
		return 0;
	}
	if((b+1) % d == 0){
		cout << "11-type" << endl;
		return 0;
	}
	int dd = d;
	int mx = 0;
	for(auto x : pr){
		int i = 0;
		while(dd % x == 0) dd /= x, i++;
		mx = max(mx, (i+e[x]-1)/e[x]);
	}
	if(dd == 1){
		cout << "2-type" << endl;
		cout << mx << endl;
		return 0;
	}
	if(lcm(b-1, b+1) % dd == 0){
		cout << "6-type" << endl;
		return 0;
	}
	cout << "7-type" << endl;
	return 0;


}

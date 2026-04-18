#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using ll = long long;
using namespace std;

int32_t main() {_

	int t; cin >> t;
	while(t--){
	vector<char> mcxi, dlv;
	for(int i=0;i<7;i++){
		char c = 'a' + i;
		cout << "? " << c << c << endl;
		int x; cin >> x;
		if(x) mcxi.push_back(c);
		else dlv.push_back(c);
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<3-i;j++){
			// comparar o j com o j+1
			char c1 = mcxi[j], c2 = mcxi[j+1];
			cout << "? " << c1 << c1 << c2 << endl;
			int x; cin >> x;
			if(!x) swap(mcxi[j], mcxi[j+1]);
		}
	}
	for(int i=0;i<2;i++){
		for(int j=0;j<2-i;j++){
			// comparar o j com o j+1
			char c1 = dlv[j], c2 = dlv[j+1];
			cout << "? " << c1 << c2 << endl;
			int x; cin >> x;
			if(!x) swap(dlv[j], dlv[j+1]);
		}
	}

	cout << "! " << mcxi[0] << dlv[0] << mcxi[1] << dlv[1] << mcxi[2] << dlv[2] << mcxi[3] << endl;
}
}

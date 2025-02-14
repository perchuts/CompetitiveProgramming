#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io

	int k; cin >> k;

	vector<vector<int>> edg(101);
	for(int i=47;i>=2;i--){
		if(i-1 >= 2) edg[i].push_back(i-1);
		if(i-2 >= 2) edg[i].push_back(i-2);
	}
	vector<int> fibs = {1, 1};
	for(int i=0;i<=45;i++){
		fibs.push_back(fibs.back() + fibs.end()[-2]);
	}
	vector<int> coisos;
	while(k){
		int t = fibs.size() - 1;
		while(fibs[t] > k) t--;
		coisos.push_back(t);
		k -= fibs[t];
	}
	reverse(coisos.begin(), coisos.end());

	int act = 1;
	int nxt = 48;
	for(int i=0;i<coisos.size();i++){
		edg[act].push_back(nxt);
		edg[nxt].push_back(coisos[i] + 2);
		act = nxt;
		nxt++;
	}

	edg[2].push_back(nxt);

	cout << nxt << endl;
	for(int i=1;i<=nxt;i++){
		int x = 2;
		for(auto y : edg[i]) cout << y << " ", x--;
		while(x--) cout << -1 << " " ;
		cout << endl;
	}


}

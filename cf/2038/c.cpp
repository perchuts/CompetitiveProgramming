#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
using namespace std;

int main(){_
	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		map<int,int> cnt;
		for(int i=0; i<n; i++){
			int x; cin >> x;
			cnt[x]++;
		}

		vector<int> vec;
		for(auto [x,y] : cnt) for(int i=1; i<y; i+=2) vec.push_back(x);

		if(vec.size() < 4){
			cout << "NO" << endl;
			continue;
		}

		int m = vec.size();
		int x = vec[0], y = vec[1], z = vec[m-2], w = vec[m-1];

		cout << "YES" << endl;
		cout << x << ' ' << y << ' ' << x << ' ' << w << ' ' << z << ' ' << y << ' ' << z << ' ' << w << endl;
	}
}

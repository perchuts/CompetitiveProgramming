#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
using namespace std;

using ll = long long;

int32_t main() {_ 
	int n; cin >> n;
	vector<vector<string>> st(1001);
	for (int i = 0; i < n; ++i){
		string x; cin >> x;
		int s = x.size();
		st[s].pb(x);
	}


	vector<pair<string,int>> seen;
	int ans = 0;

	for (int i = 1; i <= 1000; ++i){
		vector<int> vv;
		for (auto x : st[i]){
			int v = 1;
			for (auto [y,d] : seen){
				int s = y.size();
				for (int a = 0; a+s <= i; ++a){
					string z = x.substr(a,s);
					if (z == y){
						v = max(v, d+1);
						break;
					}
				}
			}	
			vv.pb(v);
			ans = max(ans,v);
		}

		for (int a = 0; a < st[i].size(); ++a){
			pair<string,int> cc = {st[i][a], vv[a]};
			seen.pb(cc);
		}
	}

	cout << ans << endl;

}

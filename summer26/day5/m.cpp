#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_
	vector<int> d;
	const int C = 900;
	map<int,int> rev;
	for(int i=1;i<=C;i++) if(C%i == 0) d.push_back(i), rev[i] = (d.size()-1);
	string s; cin >> s;
	if(s[0] == 'e'){

		string t; cin >> t;
		if(t.size() == C){
			cout << t << endl;
			cout << "#" << endl;
			return 0;
		}

		int x = t[C]-'a'+1;
		// vamos ter d[x] blocos
		for(int i=0;i<d[x];i++){
			for(int j=i*(C/d[x]);j<(i+1)*(C/d[x]);j++) cout << t[j];
			cout << endl;
		}
		cout << "#" << endl;
	}
	else{
		vector<string> v;
		string ans;
		while(1){
			string t; cin >> t;
			if(t[0] == '#') break;
			v.push_back(t);
			ans += t;
		}
		if(v.size() == 1){
			cout << ans << endl;
			return 0;
		}
		ans += (char) ('a' + rev[v.size()] - 1);
		cout << ans << endl;
	}
}

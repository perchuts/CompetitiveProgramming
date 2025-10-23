#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int n, m; cin >> n >> m;
	//vector<tuple<int, string,
	//map<string, vector<tuple<int, string, int, string>> mp;
	map<string, int> ans;
	set<string> tudo;
	int q0 = 0, q1 = 0;
	map<string,int> prev;
	map<string,int> prevdir;
	set<string> apareceu;
	int ult = 0, dirult = 0;
	for (int i = 1; i <= n+m; ++i) {
		int v; string p;
		int w; string q;
		cin >> v >> p >> w >> q;
		tudo.insert(p); tudo.insert(q);
		if(p == q){
			if(v > w) q0++;
			else q1++;

			if(!dirult) q0 += i - ult - 1;
			ult = i;
			dirult = w > v;

			for(auto s : apareceu){
				if(!prevdir[s]){
					ans[s] += (i - prev[s] - 1);
					ans[s] -= i - ult - 1;
				}
				prevdir[s] = w > v;
				prev[s] = i;
				//cout << "prev " << s << " = " << i << endl;
			}
			// Resetou!!
			// os bichos que nao apareceram eu somo: i - ult - 1
			apareceu.clear();
		}
		else{
			for(auto pp : {p, q}){
				int d = (prev[pp] >= ult ?  prevdir[pp] : dirult);
				int ant = max(ult, prev[pp]);
				if(!d) ans[pp] += (i - ant - 1);
				prev[pp] = i;
				prevdir[pp] = (pp == q);
				if(pp == p) ans[pp]++;
				apareceu.insert(pp);
			}
		}
	}
	cout << q0 << endl;
	cout << "ans " << endl;
	for(auto [s, v] : ans){
		cout << s << " " << v << endl;
	}
	cout << "ult: " << ult << endl;
	cout << "prev: " << endl;
	for(auto s : tudo){
		cout << s << " " << prev[s] << endl;
	}
	{
		for(auto s : tudo){
			if(!prevdir[s]) ans[s] += (n+m - max(ult, prev[s]));
		}
	}
	for(auto s : tudo){
		ans[s] += q0;
	}
	cout << "ans " << endl;
	for(auto [s, v] : ans){
		cout << s << " " << v << endl;
	}
}

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

int32_t main() {_
	int n, m; cin >> n >> m;
	set<string> st;
	vector<string> va(n), vb(m);
	for (int i = 0; i < n; ++i) cin >> va[i];
	for (int i = 0; i < m; ++i) cin >> vb[i];

	for (auto a : va)
		for (auto b : vb){
			for (int i = 1; i <= a.size(); ++i)
				for (int j = 0; j < b.size(); ++j){
					string pa = a.substr(0,i);
					string sb = b.substr(j,-1);
					string c = pa+sb;
					st.insert(c);
				}
		}

	cout << st.size() << endl;
	
	
}

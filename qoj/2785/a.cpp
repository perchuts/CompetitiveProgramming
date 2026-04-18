#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	int n, m; cin >> n >> m;

	array<int,26> tot = {};
	array<int,26> act = {};
	vector<array<int,26>> lets;
	for (int a = 0; a < n; ++a){
		array<int,26> w = {};
		string x; cin >> x;
		for (int i = 0; i < x.size(); ++i) w[x[i]-'A']++;
		lets.pb(w);
		for (int i = 0; i < 26; ++i) tot[i] += m*w[i], act[i] += w[i];
	}

	for (int a = 0; a < n; ++a){
		array<int,26> w = lets[a];
		array<int,26> cur = tot;
	
		for (int i = 0; i < 26; ++i) cur[i] -= m*w[i], act[i] -= w[i];

		bool ok = true;
		for (int i = 0; i < 26; ++i){
			if (w[i] > cur[i]) ok = false;
			else cur[i] -= w[i];
		}

		if (!ok) cout << -1 << " ";
		else{
			int ma = m;
			for (int i = 0; i < 26; ++i) if (act[i]){
				int k = cur[i]/act[i];
				ma = min(ma,k);
			}
			cout << ma << " ";
		}

		for (int i = 0; i < 26; ++i) act[i] += w[i];
	}
	cout << endl;

}

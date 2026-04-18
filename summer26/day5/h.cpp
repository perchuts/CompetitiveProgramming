#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_
	int t; cin >> t;
	while (t--){

	string n; cin >> n;

	reverse(n.begin(), n.end());
	int m = n.size();

	if (m == 1){
		int x = stoi(n);
		if (x == 3 or x == 6 or x == 9) cout << "1 0" << endl;
		else cout << "0 0" << endl;
		continue;
	}

	vector<int> freq(10);
	for (int a = 0; a < m; ++a) freq[n[a]-'0']++;

	int sum = 0;
	for (auto v : n) sum += (v-'0');

	int m3 = (sum%3 == 0);
	if (m3 == 0){
		cout << "0 0" << endl;
		continue;
	}

	int best = m3, mi = 0;

	vector<int> tests;
	if (n[1] == '0'){
		for (int i = 0; i < 10; ++i) tests.pb(i);
		for (int i = 1; i <= 9; ++i) tests.pb(10*i);
	} else{
		for (int i = 0; i < 100; ++i) tests.pb(i);
	}	

	for (auto i : tests){
		int c1 = (i%10), c2 = (i/10);
		vector<int> used(10);
		used[c1]++, used[c2]++;
		bool wks = true;
		for (int a = 0; a < 10; ++a) if (used[a] > freq[a]) wks = false;
		if (!wks) continue;
	
		if (n[0] == '0' and c1) continue; 

		int sw = 0;
		if (c1 != n[0]-'0') sw++;
		if (c2 != n[1]-'0') sw++;
		if (n[0]-'0' == c2 and n[1]-'0' == c1) sw = min(sw,1ll);

		int gg = m3 + (i%4 == 0) + (i%5 == 0);

		if (best == gg) mi = min(mi, sw);
		else if (gg > best) best = gg, mi = sw;
	}

	cout << best << " " << mi << endl;
	}
}

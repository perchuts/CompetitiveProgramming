#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define endl '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

using ll = long long;

void solve(){
	string a, b; cin >> a >> b;
	
	int n = b.size();
	vector<int> pi(n);
	for (int i = 1; i < n; ++i){
		int j = pi[i-1];
		while (j and b[i] != b[j]) j = pi[j-1];
		if (b[i] == b[j]) j++;
		pi[i] = j;
	}

	string s = b+"#"+a;
	int m = s.size();
	vector<int> z(m);
	int l = 0, r = 0;
	for (int i = 1; i < m; ++i){
		if (i <= r) z[i] = min(r-i+1, z[i-l]);
		while (i+z[i] < m and s[z[i]] == s[i+z[i]]) z[i]++;
		if (i + z[i] - 1 > r) l = i, r = i+z[i]-1;
	}
	
	vector<int> occ(n+1);
	for (int i = n+1; i < m; ++i){
		occ[z[i]]++;
	}
	
	for (int i = n-1; i >= 0; --i) occ[i] += occ[i+1];

	vector<int> respabv(n);
	for (int i = 0; i < n; ++i){
		if (pi[i]){
			respabv[i] = respabv[pi[i]-1];
		} else{
			int cur = occ[i+1] * (occ[i+1] - 1) / 2 + occ[i+1];
			respabv[i] += cur * (i+1);
		}
	}

	for (int i = 0; i < n; ++i) cout << respabv[i] << " ";
	cout << endl;

}	

int32_t main() {_
	int t; cin >> t;
	while (t--){
		solve();
	}
}

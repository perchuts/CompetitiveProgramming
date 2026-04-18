#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
using namespace std;

using ll = long long;

int32_t main() {_ 

	int n; cin >> n;
	vector<int> c(1100);
	vector<int> v(256);
	v['W'] = 1, v['B'] = -1;
	for(int i=0;i<n;i++){
		string s; cin >> s;
		char e = s[0];
		int foi = 0;
		for(int j=0;j<s.size();j++){
			if(!foi && s[j] == e){
				c[0] += v[s[j]];
			}
			else if(!foi && s[j] != e){
				foi++;
				c[foi] += v[s[j]];
			}
			else{
				foi++;
				c[foi] += v[s[j]];
			}
		}
	}

	for(int i=1050;i>=1;i--){
		int carry = c[i] / 2;
		c[i-1] += carry;
		c[i] %= 2;
	}
	//for(int i=0;i<20;i++){
	//	cout << c[i] << " ";
	//}
	//cout << endl;

	for(int i=0;i<1050;i++){
		if(c[i] > 0){
			cout << "Loss" << endl;
			return 0;
		}
		if(c[i] < 0){
			cout << "Win" << endl;
			return 0;
		}
	}
	cout << "Loss" << endl;
}

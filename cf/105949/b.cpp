#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

string ask(vector<int> a, vector<int> b) {
	cout << "? ";
	for(int i=0;i<n;i++) cout << a[i];
	cout << " ";
	for(int i=0;i<n;i++) cout << b[i];
	cout << endl;
	string c; cin >> c;
	return c;
}

void solve(){
	int n; cin >> n;
	cout << "? ";
	for(int i=0;i<n;i++) cout << "0";
	cout << " ";
	for(int i=0;i<n;i++) cout << "1";
	cout << endl;
	string c; cin >> c;
	vector<int> q0(n);
	int ov = 0;
	for(int i=0;i<n;i++){
		c[i] -= ov;
		ov = 0;
		if(c[i] == '0'){
			q0[i] = 1;
		}
		if(c[i] == '2'){
			q0[i] = 2;
			ov = 1;
		}
	}




}

int32_t main() {
	fast_io;
	int t; cin >> t;
	while(t--) solve();

}

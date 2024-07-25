#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define pb push_back
#define int long long
#define MAX 5e18
using namespace std;

using ll = long long;
int dibase(int n, int b){

	int cnt = 0;
	while(n){
		int di = n%b;
		if(di==0) cnt++;
		n/=b;
	}

	return cnt;
}
int pot(int a, int b){
	int r=1;
	for(int i=0;i<b;i++){
		if(MAX/b >= r){
			r*=a;
		}
		else return MAX;
	}
	return r;
}
map<int,vector<int>> memo1;
map<int,int> memo2;

void solve(){
	int n; cin >> n;
     if(memo1.find(n)!=memo1.end()){
		 //cout << "entrei\n";
		 vector<int> a = memo1[n];
		cout << memo2[n] << " " << a.size() << endl;
		for(auto b : a){
			cout << b << " ";
		}
		cout << "\n";
		return;
	}

		int mx = 1;

		vector<int> ans;
		for(int b=2;pot(b, mx)<=n;b++){
			//cout << "testando " << b << "\n";
			int t = dibase(n, b);
			if(t>mx){
				ans.clear();
				ans.push_back(b);
				mx = t;
			}
			else if(t==mx){
				ans.push_back(b);
			}
		}
		memo2[n] = mx;
		memo1[n] = ans;
		cout << mx << " " << ans.size() << endl;
		for(auto b : ans){
			cout << b << " ";
		}
		cout << "\n";
}

int32_t main() {_
	int t; cin >> t;
	while(t--) solve();
	
}

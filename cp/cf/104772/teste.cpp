#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define pb push_back
#define int long long

using namespace std;

int dibase(int n, int b){

	int cnt = 0;
	while(n){
		int di = n%b;
		if(di==0) cnt++;
		n/=b;
	}

	return cnt;
}

int tlixo(int n){
	int mx  = -1;
	for(int b=2;b<=110;b++){
		mx = max(mx, dibase(n, b));
	}
	return mx;
}

vector<int> tbom3(int n){
	vector<int> ans;
	for(int b=2;b<=110;b++){
		if(dibase(n, b)==3) {
			ans.push_back(b);
		}
	}
	return ans;
}


pair<int, vector<int>> solve(int n){

		int mx = -1;

		vector<int> ans;
		for(int b=2;b*b*b<=n;b++){// funciona se a resposta for >= 3
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

	return {mx, ans};
}
using ll = long long;

int32_t main() {_
	
	int t=0;
	vector<pair<int, vector<int>>> ans;
	vector<int> ruim;
	for(int a=3;a<=60;a++){
		for(int b=0;b<a-1;b++){
			for(int c=0;c<b;c++){
				for(int d=0;d<c;d++){
					int n = (1LL<<a)-(1LL<<b)-(1LL<<c)-(1LL<<d)-1;
					if(n>=1e12&&tlixo(n)<=3){
						
						
						ruim.push_back(n);
						ans.push_back(solve(n));
					}
				}
			}
		}
	}
	for(int a=3;a<=60;a++){
		for(int b=0;b<a-1;b++){
			for(int c=0;c<b;c++){
					int n = (1LL<<a)-(1LL<<b)-(1LL<<c)-1;
					if(n>=1e12&&tlixo(n)<=2){
						ruim.push_back(n);
						ans.push_back(solve(n));
					}
			}
		}
	}
	cout << "total: " <<  t << "\n";

	cout << ans.back().second.size() << "\n";
}

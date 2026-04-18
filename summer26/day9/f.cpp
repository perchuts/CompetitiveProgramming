#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
using namespace std;

using ll = long long;

void solve(){

	int n, k; cin >> n >> k;
	vector<int> f(7);
	int qmod2 = 0, qmod1 = 0;
	int qbom = 0;
	for(int i=0;i<n;i++){
		int x; cin >> x;
		if(x < 7) f[x]++;
		if(x > 1 && x%3 ==1) qmod1++;
		if(x%3 == 2) qmod2++;
		if(x >= 7) qbom++;
	}

	auto A = [&] (){
		cout << "Ana" << endl;
	};
	auto B = [&] (){
		cout << "Bob" << endl;
	};

	if(f[1] || f[2] >= 2){
		B();
		return;
	}

	if(k >= 4){
		A();
		return;
	}

	if(k == 3){
		
		f[5] %= 2;
		if(f[2] == 0 && f[3] == 0 && f[5] == 0 && f[6] == 0 && qbom == 0){
			B();
			return;
		}
		if(f[2] == 0){
			A();
			return;
		}
		if(f[5] == 0){
			A();
			return;
		}
		if(f[6] >= 2 || qbom){
			A();
			return;
		}
		B();
		return;
	}
	if(k == 2){

		if(qmod2 == 1 && qmod1 == 0){
			A();
			return;
		}
		else{
			B();
			return;
		}
	}

}

int32_t main() {_ 

	int t; cin >> t;
	while(t--) solve();

}

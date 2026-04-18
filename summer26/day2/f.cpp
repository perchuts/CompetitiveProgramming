#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

bool sq(int x){
	int c = sqrt(x) - 2;
	for(int e=0;e<5;e++){
		if(c*c == x) return true;
		c++;
	}
	return false;
}

int f(int x){
	int ans = 0;
	if(x >= 5 && (x % 2 == 1)) ans++;
	if(x % 4 == 0) ans++;
	if(x % 2 == 1){

		//if(x >= 2 && sq(x-1)) ans++;
		if(x >= 2 && sq(x+1)) ans++;
	}
	{
		//if(x >= 10 && sq(2*x-1)) ans++;
		if(x >= 10 && sq(2*x+1)) ans++;
	}

	return ans;
}

int32_t main() {_
	int n; cin >> n;

	int ans = 0;
	for(int i=1;i*i<=n;i++){
		if(n % i) continue;

		ans += f(i);
		if(i*i < n){
			ans += f(n/i);
		}
	}
	cout << ans << endl;
}

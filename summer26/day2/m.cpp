#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	string s; cin >> s;
	int n = s.size();
	int sm = 0;
	for(int i=0;i<n;i++){
		sm += s[i] - 'A' + 10;
	}

	if(sm % 15 == 0 && s[n-1] == 'C'){
		cout << "OK" << endl;
		return 0;
	}

	string ans;

	if(s[n-1] != 'C'){
		ans += 'C';
		sm += 12;
	}

	sm %= 15;
	while(sm > 5){
		ans +=  "A";
		sm -= 5;
	}
	if(sm > 0){
		ans += ((char)('F' - sm)); 
	}


	sort(ans.begin(), ans.end());
	cout << ans << endl;
	return 0;
}

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

int main(){_
	int tt; cin >> tt;
	while (tt--) {
		int n; cin >> n;
		auto query = [&](string t){
			cout << "1 " << t << endl;
			int res; cin >> res;
			if(res == -1) exit(0);
			return res;
		};
		auto answer = [&](int i, char c){
			cout << "0 " << i+1 << ' ' << c << endl;
			int res; cin >> res;
		};
		int _1 = query("1");
		int _01 = query("01");
		int _11 = query("11");
		int comp = _1 - _11;
		if(comp == _01) answer(0, '0');
		else if(comp == _01 + 1) answer(0, '1');
		else assert(false);
	}
	exit(0);
}


#include <bits/stdc++.h>

using namespace std;

int main(){
	int t; cin >> t;
	while(t--){
		char a, b, c; cin >> a >> b >> c;
		int n1 = a-'0', n2 = c-'0';
		if(n1 < n2) b = '<';
		else if(n1 > n2) b = '>';
		else b ='=';

		cout << n1 << b << n2 << endl;
	}
}

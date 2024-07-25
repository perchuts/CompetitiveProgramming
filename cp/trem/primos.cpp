#include <bits/stdc++.h>

using namespace std;

int main() {
	int x; cin >> x;
	if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0) cout << "N";
	else {
		int k = sqrt(x);
		cout << (k*k+2*k==x?"S":"N");
	}	
}

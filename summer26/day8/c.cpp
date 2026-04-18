#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;
int P(int x) {return (x+1)/2;}

int32_t main() {_
	int t; cin >> t;
	int tc = 0;
	while(t--){
		tc++;
		int a1, a2, b1, b2, c1, c2;
		cin >> a1 >> a2 >> b1 >> b2 >> c1 >> c2;
		a2++, b2++, c2++;
		cout << "Case " << tc << ": " << (b2 - b1) * ((P(a2) - P(a1)) * (P(c2) - P(c1))) << endl;
	}
}

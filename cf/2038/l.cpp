#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
using namespace std;

int main(){_
	vector<int> ans = {0, 2, 3, 4, 5, 6};
	int n; cin >> n;
	cout << n/6 * 7 + ans[n%6] << endl;
}


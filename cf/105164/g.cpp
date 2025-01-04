#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int n; cin >> n;
	vector<int> a(n);
	for (auto &x : a) cin >> x;

	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());

	vector<int> dif = {a[0]};
	for (int i = 1; i < a.size(); i++)
		dif.push_back(a[i] - a[i - 1]);

	int who = 0, i = 0;
	while (i < dif.size() && dif[i] == 1) {
		who = !who;
		i = i + 1;
	}

	//for (auto x : dif) cout << x << " ";
	//cout << endl;

	if (i == dif.size()) cout << (who ? "Alicius" : "Bobius") << endl;
	else {
		cout << (!who ? "Alicius" : "Bobius") << endl;
	}

}

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	string t; cin >> t;

	string a = "", b = "", c = ""; 

	int i = 0;
	while (t[i] != '='){
		a += t[i];
		i++;
	}
	++i;

	while (t[i] != '+'){
		b += t[i];
		i++;
	}
	++i;

	int n = t.size();
	while (i < n){
		c += t[i];
		++i;
	}

	auto conv = [&](string x){
		string res = "";
		int k = x.size();
		for (int j = k-1, cc = 1; j >= 0; --j, ++cc){
			res += x[j];
			if (cc%3 == 0 and j) res += "\'";
		}
		reverse(res.begin(), res.end());
		return res;
	};

	set<char> digs = {'0','1','2','3','4','5','6','7','8','9'};

	auto isnum = [&](string x){
		if (x[0] == '0') return false;
		for (auto v : x) if (!digs.count(v)) return false;
		return true;
	};

	if (isnum(a)) a = conv(a);
	if (isnum(b)) b = conv(b);
	if (isnum(c)) c = conv(c);

	cout << a << "=" << b << "+" << c << endl;
}

#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;
string s10[3628800];
string s5[120];
string s7[5040];
tuple<string, string, string> tuplas[3628800];
int32_t main() {_
	string sexo = "ABCDE";
	map<tuple<string, string, string>, int> zz;
	int t = 0;
	do {
		s5[t++] = sexo;
	} while (next_permutation(begin(sexo), end(sexo)));
	sexo = "ABCDEFG", t = 0;
	do {
		s7[t++] = sexo;
	} while (next_permutation(begin(sexo), end(sexo)));
	sexo = "ABCDEFGHIJ", t = 0;
	do {
		s10[t++] = sexo;
	} while (next_permutation(begin(sexo), end(sexo)));
	t = 0;
	for (int i = 0; i < 120; ++i) {
		for (int j = 0; j < 5040; ++j) {
			tuplas[t++] = {s5[i], s7[j], "A"};
			tuplas[t++] = {s7[j], s5[i], "A"};
			tuplas[t++] = {s5[i], "A", s7[j]};
			tuplas[t++] = {s7[j], "A", s5[i]};
			tuplas[t++] = {"A", s7[j], s5[i]};
			tuplas[t++] = {"A", s5[i], s7[j]};
		}
	}
	for (int i = 0; i < t; ++i) zz[tuplas[i]] = i;
	string s; cin >> s;
	cin >> t;
	if (s == "coach") {
		while (t--) {
			cin >> s;
			int l = 0, r = 3628800-1, ans = 0;
			while (l <= r) {
				int md = l + (r-l+1)/2;
				if (s <= s10[md]) ans = md, r = md-1;
				else l = md+1;
			}
			auto [a, b, c] = tuplas[ans];
			cout << a << " " << b << " " << c << endl;
		}
	} else {
		while (t--) {
			string a, b, c; cin >> a >> b >> c;
			auto z = make_tuple(a, b, c);
			cout << s10[zz[z]] << endl;
		}
	}
}

#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;
const int mod = 998244353;

int32_t main() {_
	vector<vector<string>> strs = {
		{"", "M", "MM", "MMM"},
		{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
		{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
		{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"}
	};
		
	int MAX = 4000;
	map<string, int> rf;
	vector<string> vals(MAX);
	vector<int> le(MAX);
	for (int a = 0; a <= 3; ++a){
		for (int b = 0; b <= 9; ++b){
			for (int c = 0; c <= 9; ++c)
				for (int d = 0; d <= 9; ++d){
					int x = a*1000+b*100+c*10+d;
					string cur = strs[0][a]+strs[1][b]+strs[2][c]+strs[3][d];
					vals[x] = cur;
					rf[cur] = x;
					le[x] = cur.size();
				}
		}
	}

	string lets = "IVXLCDM";
	
	vector<vector<int>> to(MAX, vector<int>(lets.size()));
	for (int i = 0; i < MAX; ++i){
		for (int c = 0; c < lets.size(); ++c){
			char ch = lets[c];
			string nex = vals[i]+ch;
			for (int k = 0; k < nex.size(); ++k){
				string test = nex.substr(k, -1);
				auto p = rf.find(test);
				if (p != rf.end()){
					to[i][c] = p->second;
					break;
				}	
			}
		}	
	}

	/*
	int n; cin >> n;
	int sz = lets.size();
	cout << "n : " << vals[n] << endl;
	for (int i = 0; i < sz; ++i) cout << to[n][i] << " " << vals[to[n][i]] << endl;
	*/

	int W = 16;
	vector<vector<int>> dp0(W, vector<int>(MAX));
	dp0[0][0] = 1;
	int n; cin >> n;

	for (int i = 0; i < n; ++i){
		vector<vector<int>> dp1(W, vector<int>(MAX));
		for (int r = 0; r < W; ++r)
		for (int x = 0; x < MAX; ++x) if (dp0[r][x]){
			for (int c = 0; c < lets.size(); ++c){
				int y = to[x][c];
				int s = max(le[y],r);
				dp1[s][y] = (dp1[s][y] + dp0[r][x]) % mod;
			}
		}
		dp0 = dp1;
	}

	int ans = 0;
	int tot = 0;
	for (int r = 0; r < W; ++r){
		int sum = 0;
		for (int x = 0; x < MAX; ++x) sum = (sum + dp0[r][x]) % mod;
		tot = (tot + sum) % mod;
		sum = sum * r % mod;
		ans = (ans + sum) % mod;
	}

	auto binexp = [&](int a, int b){
		int res = 1;
		while (b){
			if (b&1) res = res * a % mod;
			a = a * a % mod;
			b >>= 1;
		}
		return res;
	};

	auto inv = [&](int x){
		return binexp(x, mod-2);
	};	

	ans = ans * inv(tot) % mod;
	cout << ans << endl;
}

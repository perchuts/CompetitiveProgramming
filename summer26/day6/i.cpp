#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

int fim = 2;
int trie[801001][26];
int qt[800101][2];


int32_t main() {_
	int n; cin >> n;
	vector<vector<int>> quem(801001);
	for(int i=0;i<2*n;i++){
		string s; cin >> s;
		int at = 1; qt[at][i/n]++;
		for(int j=0;j<s.size();j++){
			if(trie[at][s[j]-'a'] == 0){
				trie[at][s[j]-'a'] = fim++;
			}
			at = trie[at][s[j]-'a'];
			qt[at][i/n]++;
		}
		quem[at].push_back(i);
	}

	int ans = 0;
	vector<array<int,2>> cc;
	auto dfs = [&] (auto&& self, int p, vector<int>& A, vector<int>& B) -> int {
		int aa = A.size(), bb = B.size();
		for(auto x : quem[p]){
			if(x < n) A.push_back(x);
			else B.push_back(x);
		}
		for(int i=0;i<26;i++) if(trie[p][i]){
			self(self, trie[p][i], A, B);
		}
		int na = A.size() - aa, nb = B.size() - bb;
		for(int i=0;i<min(na, nb);i++){
			int k = A.back(); A.pop_back();
			int l = B.back(); B.pop_back();
			cc.push_back({k, l});
		}
		ans += min(qt[p][0], qt[p][1]); // que matches sao esses?
		return ans;
	};
	vector<int> aa, bb;
	dfs(dfs, 1, aa, bb);
	cout << ans - n << endl;
	for(auto x : cc) cout << x[0]+1 << " "<< x[1]-n+1 << endl;
}

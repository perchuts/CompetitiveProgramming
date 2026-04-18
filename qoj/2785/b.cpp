#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	int t; cin >> t;
	while (t--){
		int n, m; cin >> n >> m;
		multiset<int> sa;
		multiset<int> sb;
		for (int i = 0; i < n; ++i){
			int x; cin >> x;
			sa.insert(x);
		}
		for (int i = 0; i < m; ++i){
			int x; cin >> x;
			sb.insert(x);
		}
	
		int p = 0;
		vector<multiset<int>> s = {sa,sb};
		while (1){
			int a = *s[p].rbegin();
			int b = *s[!p].rbegin();
			if (a >= b){
				s[!p].erase(s[!p].find(b));
				if (s[!p].empty()){
					if (p) cout << "Bob" << endl;
					else cout << "Alice" << endl;
					break;
				}
			} else{
				s[!p].erase(s[!p].find(b));
				s[!p].insert(b-a);
			}
			p = !p;
		}
		
	}
}

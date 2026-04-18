#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
#define f first
#define s second
using namespace std;

using ll = long long;

int32_t main() {_
	int t; cin >> t;
	while (t--){
		int n; cin >> n;
		map<int,int> freq;
		for (int i = 0; i < n; ++i){
			int x; cin >> x;
			if (x == 0) continue;
			freq[x]++;
		}

		if (freq.empty()){
			cout << 0 << endl;
			continue;
		}
	
		auto p = freq.rbegin();
		if ((p->s&1) == 0){
			cout << 0 << endl;
		}
		else if (p->s > 1){
			cout << p->s * p->f << endl;
		} else{
			if (p->f == freq.begin()->f) cout << 1 << endl;
			else{
				freq.erase(freq.find(p->f));
				auto q = freq.rbegin();

				if (q->s&1) cout << 1 << endl;
				else cout << q->f << endl;
			}	
		}	
	}
}

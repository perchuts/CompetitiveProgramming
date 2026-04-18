#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define endl '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

using ll = long long;

const int maxn = 3e5+10;
vector<int> divs[maxn];

void solve(){
	int x, y, n, m, k, s; cin >> x >> y >> n >> m >> k >> s;
	s--;
	int tot = (1<<(k+1))-1; 

	for (int i = 0; i <= x; ++i) divs[i].clear();

	while (n--){
		int d; cin >> d;
		for (int a = d; a <= x; a += d) divs[a].pb(d);
	}

	vector<int> bs(m);
	for (int i = 0; i < m; ++i) cin >> bs[i]; 

	vector<vector<int>> dp(x+1, vector<int>(20));
	dp[x][0] = 1;

	for (int i = x; i > y; --i){
		for (int a = 0; a < 20; ++a) if (dp[i][a]){
			for (auto d : divs[i]){
				int j = i/d;
				if (a+1 < 20) dp[j][a+1] = dp[j][a+1] | dp[i][a];
			}	

			for (auto b : bs) if (i > b){
				int j = i-b;
				int val = (dp[i][a]<<1) & tot;
				dp[j][a] = dp[j][a] | val;
			}
		}
	}

	for (int i = 1; i <= y; ++i){
		for (int a = 0; a < 20; ++a){
			for (int u = 0; u <= k and a+u <= s; ++u){
				if (a+u == s and (dp[i][a]>>u&1)){
					cout << "Yes\n";
					return;
				}
			}
		}
	}

	for (int i = y+1; i <= x; ++i) if (divs[i].empty()){
		bool f = false;
		for (auto b : bs) if (i > b) f = true;
		if (f){
			for (int a = 0; a < 20; ++a) if (a+k == s and (dp[i][a]>>k&1)){
					cout << "Yes\n";
					return;
			}
		} else{
		for (int a = 0; a < 20; ++a){
			for (int u = 0; u <= k and a+u <= s; ++u){
				if (a+u == s and (dp[i][a]>>u&1)){
					cout << "Yes\n";
					return;
				}
			}
		}
		}	
	}
	cout << "No\n";
}

int32_t main() {_
	int t; cin >> t;
	while (t--){
		solve();
	}
}

#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define int long long
#define PI pair<int,int>
#define f first
#define s second
#define pb push_back
#define szo(x) ((int)x.size())

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--){
		int n, q; cin >> n >> q;
		vector<int> as(n);
		for (int i = 0; i < n; ++i) cin >> as[i];
		sort(as.begin(), as.end());

		multiset<int> st;
		for (auto a : as) st.insert(a);

		while (q--){
	 		int c; cin >> c;

			int ans = 0;
			vector<pair<bool,int>> history;
			while (c){
				int x = *st.rbegin();
				if (x >= c){
					c = 0;
					break;
				}
				int y = x^c;
				int b = 63 - __builtin_clzll(y);
				
				if (x >= (1ll<<b)){
					history.pb({0,x});
					st.erase(st.find(x));

					int z = (x>>b)<<b;
					c ^= z;
					x -= z;
					history.pb({1,x});
					st.insert(x);
				} else{
	 				history.pb({0,x});
					history.pb({1,0});
					st.erase(st.find(x));
					st.insert(0);
					c -= (1ll<<b);
					ans += (1ll<<b)-x;
				}
			}

			while (!history.empty()){
	 			auto [b, op] = history.back(); history.pop_back();
				if (b) st.erase(st.find(op));
				else st.insert(op);
			}

			cout << ans << '\n';
		}
	}
    return 0;
}


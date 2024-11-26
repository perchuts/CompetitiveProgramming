#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
using namespace std;


const int mod = (119<<23)+1;

int main(){_
	int n; cin >> n;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	vector<vector<int>> lst(n+1, vector<int>(30, 0));
	vector<tuple<int, int, int, int>> items;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 30; ++j) {
			if (v[i-1]>>j&1) lst[i][j] = i;
			else lst[i][j] = lst[i-1][j];
		}
		int cur = v[i-1], ptr = i-1;
		while (true) {
			int other = 0;
			for (int j = 0; j < 30; ++j) {
				if (cur>>j&1) continue;
				other = max(other, lst[ptr][j]);	
			}
			items.push_back({cur, other, ptr, i}); 
			if (other == 0) break;
			cur |= v[other-1];
			ptr = other-1;
		}
	}
	vector<int> bit(n+1);
	auto insert = [&] (int x, int k) {
		while (x <= n) {
			bit[x] += k;
			if (bit[x] >= mod) bit[x] -= mod;
			x += x&(-x);
		}
	};
	auto query = [&] (int x) {
		if (x < 0) return 0;
		int ans = 0;
		while (x) {
			ans += bit[x]; 
			if (ans >= mod) ans -= mod;
			x -= x&(-x);
		}
		return ans;
	};
	auto query_range = [&] (int l, int r) {
		int w = (l == 0);
		return (query(r) - query(l-1) + mod + w) % mod;
	};
	sort(begin(items), end(items));
	for (auto [val, lx, rx, pos] : items) {
		//cout << "val = " << val << " lx = " << lx << " rx = " << rx << " pos = " << pos << endl;
		int my = query_range(lx, rx);
		//cout << "valor computado = " << my << endl;
		insert(pos, my);
	}
	cout << query_range(n, n) << endl;
}


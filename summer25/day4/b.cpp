#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io
	int n; cin >> n;
	int k = 1e9 + 7; k *= 2;
	vector<int> a(n);
	vector<int> vals = {0, k-1};
	int sum = 0;
	for (auto& x : a) {
		cin >> x;
		sum += x;
		sum %= k;
		vals.push_back((sum + k/2) % k);		
		vals.push_back(sum);
	}
	sort(begin(vals), end(vals));
	vals.erase(unique(begin(vals), end(vals)), end(vals));
	int N = vals.size();
	vector<vector<int>> bit(2, vector<int>(N+1)); 
	const int mod = 1e9+7;
	auto insert = [&] (int i, int x, int z) {
		while (x <= N) bit[i][x] = (bit[i][x] + z) % mod, x += x & (-x);
	};
	auto query = [&] (int i, int x) {
		int ans = 0;
		while (x) {
			ans = (ans + bit[i][x]) % mod;
			x -= x & (-x);
		}
		return ans;
	};
	auto get_id = [&] (int x) {
		x %= k;
		x = (x + k) % k;
		int ret = lower_bound(begin(vals), end(vals), x) - begin(vals);
		assert(vals[ret] == x);
		return ret+1;
	};
	auto query2 = [&] (int i, int l, int r) {
		if (l > r) return 0LL;
		return query(i, r) - (l == 1 ? 0LL : query(i, l-1));
	};
	insert(0, get_id(0), 1);
	sum = 0;
	for (int i = 0; i < n; ++i) {
		int my = 0; sum = (a[i] + sum) % k;
		int l = get_id(sum-mod), r = get_id(sum);
		if (l > r) swap(l, r);
		if (sum >= mod) {
			my = query((sum+1)%2, N) + query2((sum)%2, l, r) - query2((sum+1)%2, l+1, r-1);
		} else {
			my = query((sum)%2, N) + query2((sum+1)%2, l, r) - query2((sum)%2, l+1, r-1);

		}
		my %= mod;
		my = (my + mod) % mod;
		insert(sum%2, get_id(sum), my);
		if (i == n-1) cout << my << endl;
	}
}

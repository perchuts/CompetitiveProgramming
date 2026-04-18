#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

void solve() {
	int n; cin >> n;
	if (n == 0) exit(0);
	vector<int> a(n), opt_esq(n), bit(n+1);
	for (auto& x : a) cin >> x;
	auto insert = [&] (int x, int k) { while (x <= n) bit[x] = max(bit[x], k), x += x & (-x); };
	auto query = [&] (int x) {
		int ans = 0;
		while (x) {
			ans = max(ans, bit[x]);
			x -= x & (-x);
		}
		return ans;
	};
	int lis = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] == 0) continue;
		opt_esq[i] = query(a[i]-1) + 1;
		insert(a[i], opt_esq[i]);
		lis = max(lis, opt_esq[i]);
	}
	for (int i = 0; i <= n; ++i) bit[i] = 0;
	vector<int> opt_dir(n);
	vector<vector<int>> vals(n+1);
	vector<int> sweep(n+5), prox_zero(n, n);
	vector<set<int>> ids_opt(n+1);
	for (int i = n-1; ~i; --i) {
		if (a[i] == 0) continue;
		opt_dir[i] = query(n-a[i]) + 1;
		insert(n-a[i]+1, opt_dir[i]);
		vals[a[i]].push_back(i);
	}
	for (int i = n-1; ~i; --i) {
		if (i != n-1) prox_zero[i] = prox_zero[i+1];
		if (a[i] == 0) prox_zero[i] = i;
	}
	vector<int> foi(n+1);
	for (int i = n; i >= 1; --i) {
		for (auto idx_esq : vals[i]) {
			int pode = prox_zero[idx_esq];
			if (pode == n) continue;
			int need = lis - opt_esq[idx_esq];
			auto it = lower_bound(begin(ids_opt[need]), end(ids_opt[need]), pode);
			if (it != end(ids_opt[need])) {
				int val = a[*it];
				// soh inserir o cara mais a direita com certo valor de opt
				sweep[i+1]++;
				sweep[val]--;
			}
		}
		sort(rbegin(vals[i]), rend(vals[i]));
		for (auto idx_dir : vals[i]) {
			int tam_lis = opt_dir[idx_dir];
			if (foi[tam_lis] == i) continue;
			foi[tam_lis] = i;
			ids_opt[tam_lis].insert(idx_dir);
		}
	}
	int ans = 0, ev = 0;
	// pode ser que o meu zero esteja antes de todos os elementos!!
	int z = prox_zero[0];
	if (z != n) {
		for (int i = z+1; i < n; ++i) {
			if (a[i] != 0 and opt_dir[i] == lis) {
				sweep[1]++;
				sweep[a[i]]--;
				break;
			}
		}
	}
	int ult_zero = -1;
	for (int i = 0; i < n; ++i) {
		if (a[i] == 0) ult_zero = i;
	}
	if (ult_zero != -1) {
		for (int i = ult_zero-1; i >= 0; --i) {
			if (a[i] != 0 and opt_esq[i] == lis) {
				sweep[a[i]+1]++;
				break;
			}
		}
	}
	lis = max(lis, 1LL);
	for (int i = 1; i <= n; ++i) {
		ev += sweep[i];
		ans += lis * i;
		if (ev != 0) ans += i;
	}
	cout << ans << endl;
}

int32_t main() {_
	while (true) solve();
}

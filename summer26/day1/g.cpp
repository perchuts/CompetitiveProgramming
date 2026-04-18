#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using ord_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
//#define endl '\n'
#define int ll
#define pb push_back
//#define gato

using ll = long long;

struct ST {
	vector<int> sum, lz, atv, seg;
	ST(int n) {
		sum.resize(4*n);
		seg.resize(4*n);
		lz = vector<int>(4*n, -1);
		atv.resize(4*n);
	}
	void push(int i, int l, int r) {
		if (lz[i] == -1) return;
		sum[i] = atv[i] * lz[i];
		seg[i] = lz[i];
		if (l != r) lz[2*i] = lz[2*i+1] = lz[i];
		lz[i] = -1;
	}
	void add_point (int i, int l, int r, int x) {
		push(i, l, r);
		if (r < x or x < l) return;
		if (l == r) {
			atv[i] = 1;
			sum[i] = seg[i];
			return;
		}
		int md = (l+r)/2;
		add_point(2*i, l, md, x);
		add_point(2*i+1, md+1, r, x);
		atv[i] = atv[2*i] + atv[2*i+1];
		sum[i] = sum[2*i] + sum[2*i+1];
	}
	void upd (int i, int l, int r, int x, int y, int k) {
		push(i, l, r);
		if (r < x or y < l) return;
		if (x <= l and r <= y) {
			lz[i] = k;
			push(i, l, r);
			return;
		}
		int md = (l+r)/2;
		upd(2*i, l, md, x, y, k);
		upd(2*i+1, md+1, r, x, y, k);
		atv[i] = atv[2*i] + atv[2*i+1];
		sum[i] = sum[2*i] + sum[2*i+1];
	}
	int query (int i, int l, int r, int x, int y) {
		push(i, l, r);
		if (x <= l and r <= y) return sum[i];
		if (r < x or y < l) return 0;
		int md = (l+r)/2;
		return query(2*i, l, md, x, y) + query(2*i+1, md+1, r, x, y);
	}
};
vector<int> brute(int n, int q, vector<int> a, vector<int> bichos) {
	vector<int> ans;
	auto calc = [&] (vector<int> b) {
		int m = b.size();
		int tot = 0;
		for (int i = 0; i < m; ++i) {
			int mn = 1000001, mx = 0;
			for (int j = 0; j <= i; ++j) {
				mn = min(mn, b[j]);
			}
			for (int j = m-1; j >= i; --j) {
				mx = max(mx, b[j]);
			}
			tot += mn * mx;
		}
		return tot;
	};
	ans.pb(calc(a));
	for (auto i : bichos) {
		a.erase(begin(a) + i);
		ans.pb(calc(a));
	}
	return ans;
}

vector<int> solve(int n, int q, vector<int> a, vector<int> bichos) {
	vector<int> morre(n);
	ord_set<int> ooo;
	for (int i = 0; i < n; ++i) ooo.insert(i);
	vector<int> real_bichos;
	for (auto x : bichos) {
		int k = *ooo.find_by_order(x);
		morre[k] = 1;
		ooo.erase(k);
		real_bichos.push_back(k);
	}
	swap(bichos, real_bichos);
	ST seg_min(n), seg_max(n);
	reverse(begin(bichos), end(bichos));
	set<tuple<int, int, int>> min_ranges, max_ranges;	
	min_ranges.insert({n-1, 0, 1000500});
	max_ranges.insert({n-1, 0, 0});
	int cur_ans = 0, bound = -1;
	seg_min.upd(1, 0, n-1, 0, n-1, 1000500);
	seg_max.upd(1, 0, n-1, 0, n-1, 0);
	auto upd_min = [&] (int idx) {
		// insere o cara idx no array
		auto it = min_ranges.lower_bound({idx, -1, -1});
		int r_max = -1;
		bound = -1;
		vector<tuple<int, int, int>> adc;
		while (it != end(min_ranges)) {
			auto [rx, lx, vx] = *it;
			if (vx < a[idx]) break;
			if (vx == 1000500) bound = rx;
			it = next(it);
			min_ranges.erase({rx, lx, vx});
			// remove contribuicao desse intervalo na minha segtree
			int S = seg_max.query(1, 0, n-1, lx, rx);
			cur_ans -= S * vx;
			// eh possivel que esse intervalo ainda exista no futuro
			if (lx < idx) adc.push_back({lx, idx-1, vx});
			r_max = rx;
		}
		for (auto [lx, rx, vx] : adc) {
			int S_add = seg_max.query(1, 0, n-1, lx, rx);
			cur_ans += S_add * vx;
			min_ranges.insert({rx, lx, vx});
		}
		if (r_max != -1) {
			min_ranges.insert({r_max, idx, a[idx]});
			int S_add = seg_max.query(1, 0, n-1, idx, r_max);
			cur_ans += S_add * a[idx];
			seg_min.upd(1, 0, n-1, idx, r_max, a[idx]);
		}
	};
	auto upd_max = [&] (int idx) {
		// insere o cara idx no array
		auto it = max_ranges.lower_bound({idx, -1, -1});
		int l_min = -1;
		vector<tuple<int, int, int>> adc;
		while (true) {
			auto [rx, lx, vx] = *it;
			int foi = 0;
			if (it != begin(max_ranges)) it = prev(it);
			else foi = 1;
			if (vx > a[idx]) break;
			max_ranges.erase({rx, lx, vx});
			// remove contribuicao desse intervalo na minha segtree
			int S = seg_min.query(1, 0, n-1, lx, rx);
			cur_ans -= S * vx;
			// eh possivel que esse intervalo ainda exista no futuro
			if (idx < rx) adc.pb({idx+1, rx, vx});
			l_min = lx;
			if (foi) break;
		}
		for (auto [lx, rx, vx] : adc) {
			int S_add = seg_min.query(1, 0, n-1, lx, rx);
			cur_ans += S_add * vx;
			max_ranges.insert({rx, lx, vx});
		}
		if (l_min != -1) {
			max_ranges.insert({idx, l_min, a[idx]});
			int S_add = seg_min.query(1, 0, n-1, l_min, idx);
			cur_ans += S_add * a[idx];
			seg_max.upd(1, 0, n-1, l_min, idx, a[idx]);
		} 	
	};
	for (int i = 0; i < n; ++i) {
		if (!morre[i]) {
			seg_min.add_point(1, 0, n-1, i);
			seg_max.add_point(1, 0, n-1, i);
			cur_ans += seg_min.query(1, 0, n-1, i, i) * seg_max.query(1, 0, n-1, i, i);
			upd_min(i);
			upd_max(i);
		}
	}
	vector<int> ans;
	ans.push_back(cur_ans);
	for (auto i : bichos) {
		seg_min.add_point(1, 0, n-1, i);
		seg_max.add_point(1, 0, n-1, i);
		cur_ans += seg_min.query(1, 0, n-1, i, i) * seg_max.query(1, 0, n-1, i, i);
		upd_min(i);
		upd_max(i);
		ans.push_back(cur_ans);
	}
	reverse(begin(ans), end(ans));
	return ans;
}
mt19937 rng(time(0));

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}



int32_t main() {_
#ifndef gato
	int n, q; cin >> n >> q;
	vector<int> bichos, a(n), morre(n);
	ord_set<int> ooo;
	for (auto& x : a) cin >> x;
	for (int i = 0; i < q; ++i) {
		int x; cin >> x; --x;
		bichos.push_back(x);
	}
	auto ans = solve(n, q, a, bichos);
	for (auto x : ans) cout << x << " ";
	cout << endl;
#else
	int t = 1;
	while (true) {
		int n = rnd(1, 10), q = rnd(0, n-1);
		vector<int> bichos, a(n);
		for (auto& x : a) x = rnd(1, 5);
		for (int i = 0; i < q; ++i) {
			bichos.pb(rnd(0, n-1-i));
		}
		auto my = solve(n, q, a, bichos);
		auto ans = brute(n, q, a, bichos);
		if (ans != my) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << ' ' << q << endl;
			for (auto x : a) cout << x << " ";
			cout << endl;
			for (auto x : bichos) cout << x+1 << " ";
			cout << endl;
			cout << "solve: ";
			for (auto x : my) cout << x << " ";
			cout << endl;
			cout << "brute: ";
			for (auto x : ans) cout << x << " ";
			cout << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}

#endif
}

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

ii solve(int n, vector<int> a, vector<int> b){
	vector<vector<iii>> ans(n+1);
	for (int i = n - 1; i >= 0; --i) {
		int cur_a = a[i], cur_b = b[i], cur_fim = i;
		for (auto [val_a, val_b, fim] : ans[i+1]) {
			int nb = gcd(cur_b, val_b), na = gcd(cur_a, val_a);
			if (nb != cur_b or na != cur_a) ans[i].pb({cur_a, cur_b, cur_fim});
			cur_b = nb, cur_a = na, cur_fim = fim;
		}
		ans[i].pb({cur_a, cur_b, cur_fim});
	}
	vector<iii> suffix;
	int ca = 0, cb = 0;
	suffix.pb({0, 0, n});
	for (int i = n-1; i >= 0; --i) {
		int na = gcd(ca, a[i]), nb = gcd(cb, b[i]);
		if (na != ca or nb != cb) {
			ca = na, cb = nb;
			suffix.pb({ca, cb, i});
		}
	}
	reverse(all(suffix));
	//cout << "suffix:" << endl;
	//for (auto [x, y, z] : suffix) cout << x << ' ' << y << ' ' << z << endl;
	int mx = 0, pre_a = 0, pre_b = 0, j_s = 0;
	ll qnt_ans = 0;
	for (int i = 0; i < n; ++i) {
		if (get<2>(suffix[j_s]) <= i) j_s++;	
		//cout << "ans[" << i << "]:" << endl;
		for (auto [x, y, z] : ans[i]) cout << x << ' ' << y << ' ' << z << endl;
		int j = j_s, k = 0, id = i;
		while (k != sz(ans[i])) {
			auto [x1, x2, x3] = ans[i][k];
			auto [y1, y2, y3] = suffix[j];
			if (y3 <= id) { j++; continue; }	
			int lim = min(x3, y3-1);
			int ga = gcd(gcd(x2, pre_a), y1);
			int gb = gcd(gcd(x1, pre_b), y2);
			int val = ga+gb;
			if (ckmax(mx, val)) qnt_ans = lim-id+1;
			else if (mx == val) qnt_ans += lim-id+1;
			//cout << "k: " << k << " j: " << j << " id: " << id << " lim: " << lim << ' ' << "Gs: " <<ga << ' ' << gb << " ans: " << mx << ' ' << qnt_ans << endl;
			id = lim+1;
			if (lim == x3) k++;
		}
		pre_a = gcd(pre_a, a[i]), pre_b = gcd(pre_b, b[i]);
	}
	return make_pair(mx, qnt_ans);
}

mt19937 rng(time(0));

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

int32_t main(){_
	int tt = 1;
	while (true) {
		int n = rnd(1, 10);
		vector<int> a(n), b(n);
		int mxv = 1001110;
		for (auto& x : a) x = rnd(1, mxv);
		for (auto& x : b) x = rnd(1, mxv);
		auto [my_ans, my_qnt] = solve(n, a, b);
		int ans = 0, freq = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				int ga = 0, gb = 0;
				for (int k = 0; k < n; ++k) {
					if (k < i or j < k) ga = gcd(ga, a[k]), gb = gcd(gb, b[k]);
					else ga = gcd(ga, b[k]), gb = gcd(gb, a[k]);
				}
				if (ckmax(ans, ga+gb)) freq = 1;
				else if (ga+gb == ans) freq++;
			}	
		}
		if (my_ans != ans or my_qnt != freq) {
			cout << "Wrong answer on test " << tt << endl;
			cout << n << endl;
			for (auto x : a) cout << x << ' ';
			cout << endl;
			for (auto x : b) cout << x << ' ';
			cout << endl;
			cout << "Your output: " << my_ans << ' ' << my_qnt << endl;
			cout << "Correct answer: " << ans << ' ' << freq << endl;
			exit(0);
		}
		cout << "Accepted on test " << tt++ << endl;
	}
}

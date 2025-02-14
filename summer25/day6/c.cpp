#include <bits/stdc++.h>
//#define gato
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;
const int MAX = 2e5+10, UPD = 2e5+10, LOG = 19;
const int MAXS = 2*MAX+UPD*LOG;
namespace perseg {
	pair<int, int> seg[MAXS];
	int rt[UPD], L[MAXS], R[MAXS], cnt, t;
	int n;
	void build(int p, int l, int r) {
		if (l == r) {
			seg[p] = {0, 0};
			return;
		}
		L[p] = cnt++, R[p] = cnt++;
		int m = (l+r)/2;
		build(L[p], l, m), build(R[p], m+1, r);
	}
	void build(int n2) {
		n = n2;
		rt[0] = cnt++;
		build(0, 0, n-1);
	}
	pair<int, int> query(int a, int b, int p, int l, int r) {
		if (b < l or r < a) return make_pair(0, 0);
		if (a <= l and r <= b) return seg[p];
		int m = (l+r)/2;
		auto [x1, y1] = query(a, b, L[p], l, m);
		auto [x2, y2] = query(a, b, R[p], m+1, r);
		return make_pair(x1+x2, y1+y2);
	}
	pair<int, int> query(int a, int b, int tt) {
		return query(a, b, rt[tt], 0, n-1);
	}
	pair<int, int> update(int a, int x, int lp, int p, int l, int r) {
		//cout << a << ' ' << x << ' ' << l << ' ' << r << endl;
		//cout.flush();
		if (l == r) {
			//cout << "+" << l << ' ' << x << ' ' << 1 << endl;
			return seg[p] = {x, 1};
		}
		int m = (l+r)/2;
		if (a <= m) {
			auto [u, v] = update(a, x, L[lp], L[p]=cnt++, l, m);
			auto [w, z] = seg[R[p]=R[lp]];
			//cout << u << ' ' << v << " junta com " << w << ' ' << z << endl;
			//cout << l << ' ' << r << endl;
			return seg[p] = {u+w, v+z};
		} 
		auto [u, v] = seg[L[p]=L[lp]];
		auto [w, z] = update(a, x, R[lp], R[p]=cnt++, m+1, r);
		return seg[p] = {u+w, v+z};
	}
	int update(int a, int x, int tt=t) {
		update(a, x, rt[tt], rt[++t]=cnt++, 0, n-1);
		return t;
	}
};

vector<int> solve(int n, int k, int q, vector<int> a, vector<pair<int, int>> qu) {
	vector<int> pr(n), diff(n);
	for (int i = 0; i < n; ++i) pr[i] = (i?pr[i-1]:0) + a[i];
	for (int i = 0; i < n; ++i) diff[i] = a[n-i-1] - a[i]; 
	int last_ans = 0, max_id = -1;
	vector<int> ord(n); iota(begin(ord), end(ord), 0);
	vector<int> roots(n);
	sort(begin(ord), end(ord), [&] (int x, int y) {
		return diff[x] > diff[y];
	});
	perseg::build(n);
	//cout << "perseg: " << endl;
	for (int j = 0; j < n; ++j) {
		int i = ord[j]; 
		if (diff[i] < 0) break;
		max_id = j;
		//cout.flush();
		roots[j] = perseg::update(i, diff[i]);
	}
	assert(max_id >= 0);
	// do segtree things
	vector<int> resp;
	for (auto [l, r] : qu) {
		l ^= last_ans, r ^= last_ans;
		int ans = pr[r] - (l?pr[l-1]:0), best = ans;
		//cout << "intervalo: ";
		//cout << l << ' ' << r << endl;
		//cout.flush();
		// resolver os intervalos
		if (n&1) {
			if (r < n/2 or l > n/2) {}
			else {
				int d1 = n/2-l, d2 = r-n/2;
				if (d1 <= d2) l += 2*d1+1;
				else r -= 2*d2+1;
			}
		} else {
			if (r < n/2 or l > n/2) {}
			else {
				int d1 = n/2-1-l, d2 = r-n/2;
				//cout << "entrei";
				//cout << d1 << ' ' << d2 << endl;
				if (d1 <= d2) l += 2*d1+2;
				else r -= 2*d2+2;
			}
		}
		//cout << "Atualizei pra " << l << ' ' << r << endl;
		//cout.flush();
		int lx = 0, rx = max_id;
		while (lx <= rx) {
			int md = lx + (rx-lx+1)/2;
			//cout.flush();
			auto [soma, freq] = perseg::query(l, r, roots[md]);
			//cout << "nos " << md << " maiores tem soma " << soma << " e freq " << freq << endl;
			if (freq <= k) best = ans + soma, lx = md+1;
			else rx = md-1;
		}
		resp.push_back(best);
		//cout << "respondi: " << best << endl;
		//cout.flush();
		last_ans = best;
	}
	return resp;
}

mt19937 rng(time(0));

int rnd(int l, int r) {
	//uniform_int_distribution<int> uid(l, r);
	//return uid(rng);
	return rand() % (r - l+1) + l;
}

int32_t main() {
	fast_io;
#ifdef gato
	int t = 1;
	for (int seed = 0; ; seed++) {
		srand(seed);
		int n = rnd(1, 5), q = 2, k = rnd(0, n);
		vector<int> a(n);
		for (auto& x : a) x = rnd(1, 5);
		vector<pair<int, int>> qu(q);
		auto responder = [&] (int l, int r) {
			priority_queue<int> pq;
			int ans = 0;
			for (int i = l; i <= r; ++i) {
				ans += a[i];
				if (n-1-i > r or n-1-i < l) pq.push(a[n-1-i]-a[i]);
			}
			for (int i = 0; i < k and !pq.empty(); ++i) {
				int x = pq.top();
				pq.pop();
				if (x <= 0) return ans;
				ans += x;
			}
			return ans;
		};
		int lst = 0;
		vector<int> resp;
		for (auto& [x, y] : qu) {
			x = rnd(0, n-1), y = rnd(x, n-1);
			resp.push_back(responder(x, y));
			x ^= lst, y ^= lst;
			lst = resp.back();
		}
		auto my = solve(n, k, q, a, qu);
		cout << n << ' ' << k << ' ' << q << endl;
		for (auto x : a) cout << x << ' ';
		cout << endl;
		for (auto [x, y] : qu) cout << x << ' ' << y << endl;
		cout.flush();
		if (my != resp) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << ' ' << k << ' ' << q << endl;
			for (auto x : a) cout << x << ' ';
			cout << endl;
			for (auto [x, y] : qu) cout << x << ' ' << y << endl;
			cout << "your output: ";
			for (auto x : my) cout << x << ' ';
			cout << endl;
			cout << "correct: ";
			for (auto x : resp) cout << x << ' ';
			cout << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#else
	int n, k, q; cin >> n >> k >> q;
	vector<int> a(n);
	vector<pair<int, int>> qu(q);
	for (auto& x : a) cin >> x;
	for (auto& [x, y] : qu) cin >> x >> y;
	auto my = solve(n, k, q, a, qu);
	for (auto x : my) cout << x << endl;
#endif
}

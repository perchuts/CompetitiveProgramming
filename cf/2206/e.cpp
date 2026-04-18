#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define endl '\n'

using namespace std;
using ll = long long;

const int MAX = 2e5+10;
inline ll hilbert(int x, int y){
	static int N = 1 << (__builtin_clz(0) - __builtin_clz(MAX));
	int rx, ry, s;
	ll d = 0;
	for (s = N/2; s > 0; s /= 2){
		rx = (x&s) > 0, ry = (y&s) > 0;
		d += s * ll(s) * ((3*rx)^ry);
		if (ry == 0){
			if (rx == 1) x = N-1-x, y = N-1-y;
			swap(x,y);
		}
	}
	return d;	
}

#define int ll

struct rmq{
	int D, n;
	vector<vector<int>> st;
	rmq(vector<int> v){
		n = v.size(), D = 63 - __builtin_clzll(n) + 1;
		st = vector<vector<int>>(D, vector<int>(n));
		
		for (int i = 0; i < n; ++i) st[0][i] = v[i];
		for (int u = 1; u < D; ++u)
			for (int i = 0; i+(1<<(u-1)) < n; ++i){
				st[u][i] = max(st[u-1][i], st[u-1][i+(1<<(u-1))]);
			}
	}

	int query(int l, int r){
		if (r < l) return 0ll;
		int le = r-l+1;
		int b = 63 - __builtin_clzll(le);
		return max(st[b][l], st[b][r-(1<<b)+1]);
	}
};



const int SQ = 400;

int32_t main() {_
	int n, m; cin >> n >> m;
	int sz = n-m+1;
	vector<int> vals(sz);
	for (int i = 0; i < sz; ++i) cin >> vals[i];

	vector<int> md(n+1);
	for (int i = 1; i <= n; ++i){
		md[i] = md[i-1] + 1;
		if (md[i] == m) md[i] = 0;
	}	

	vector<int> ds(n);
	for (int i = m; i < n; ++i){
		int id = i-m+1;
		assert(id < sz);
		ds[i] = ds[i-m] + vals[id] - vals[id-1]; 
	}

	vector<rmq> sts;
	for (int i = 0; i < m; ++i){
		vector<int> cur;
		for (int j = i; j < n; j += m) cur.pb(ds[j]);
		sts.pb(rmq(cur));
	}
	
	int q; cin >> q;
	vector<pair<int,int>> qs;
	for (int i = 0; i < q; ++i){
		int l, r; cin >> l >> r;
		l--; r--;
		qs.pb({l,r});
	}
	vector<int> ord(q);
	iota(ord.begin(), ord.end(), 0);

		/*
	sort(ord.begin(), ord.end(), [&](int l, int r) {
			if (qs[l].first / SQ != qs[r].first / SQ) return qs[l].first < qs[r].first;
			return qs[l].second < qs[r].second;
			});
		*/
	vector<int> h(q);
	for (int i = 0; i < q; ++i) h[i] = hilbert(qs[i].first, qs[i].second);
	sort(ord.begin(), ord.end(), [&](int l, int r) {return h[l] < h[r];});

	vector<int> ret(q);

	int sum = 0;

	auto nex = [&](int x, int c){
		int d = md[x];
		if (d <= c) return x+c-d;
		return x+m-d+c;
	};

	auto pr = [&](int x, int c){
		int d = md[x];
		if (c <= d) return x-d+c;
		return x-d-m+c;
	};

	auto op = [&](int c, int oldl, int oldr, int newl, int newr){
		if (oldl <= oldr){
			int a = nex(oldl, c);
			int b = pr(oldr, c);
			if (a < n and b < n and a >= 0 and b >= 0) sum -= sts[c].query(a/m,b/m);
		}

		if (newl <= newr){
			int a = nex(newl, c);
			int b = pr(newr, c);
			if (a < n and b < n and a >= 0 and b >= 0) sum += sts[c].query(a/m,b/m);
		}
	};	

	const int INF = 1e18;
	auto teto = [&](int v){
		return (v + INF/m * m + m - 1) / m - INF / m;	
	};

	int l = 0, r = -1;
	for (int qid : ord){
		auto [ql, qr] = qs[qid];
		while (r < qr) op(md[r+1], l, r, l, r+1), r++;
		while (l > ql) op(md[l-1], l, r, l-1, r), l--;
		while (l < ql) op(md[l], l, r, l+1, r), l++;
		while (r > qr) op(md[r], l, r, l, r-1), r--;

		int v = vals[0] + sum;
		ret[qid] = teto(v);
	}

	for (int i = 0; i < q; ++i){
		auto [ql, qr] = qs[i];
		int le = qr-ql+1;
		if (le < m) cout << "unbounded" << endl;
		else cout << ret[i] << endl;
	}
}

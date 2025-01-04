#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

const int MAX = 1e4 + 10;
const int SQ = sqrt(MAX);
int v[MAX];

int ans = 0;
multiset<int> st, dif;

void consider(multiset<int>::iterator& a, multiset<int>::iterator& b, bool ins=true) {
	if (a != b && a != st.end() && b != st.end()) {
		if (ins) dif.insert(*b - *a);
		else dif.extract(*b - *a);
	}
}

inline void insert(int p) {
	int o = v[p];
	
	auto it = st.lower_bound(o);

	if (it != st.end()) {
		auto prv = prev(it);
		consider(prv, it, false);
	}

	st.insert(o);
	it = st.lower_bound(o);
	auto prv = prev(it);
	auto nxt = next(it);
	consider(prv, it, true);
	consider(it, nxt, true);

	ans = *dif.begin();
}

inline void erase(int p) {
	int o = v[p];
	
	auto it = st.lower_bound(o);
	auto prv = prev(it);
	auto nxt = next(it);

	consider(prv, it, false);
	consider(it, nxt, false);

	st.extract(*it);

	it = st.lower_bound(o);
	if (it != st.end()) {
		prv = prev(it);
		consider(prv, it, true);
	}
	ans = *dif.begin();
}

vector<int> MO(vector<pair<int, int>> &q) {
	ans = 0;
	int m = q.size();
	vector<int> ord(m);
	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&] (int l, int r) {
		if (q[l].first / SQ != q[r].first / SQ) return q[l].first < q[r].first;
		if ((q[l].first/SQ) % 2) return q[l].second > q[r].second;
		return q[l].second < q[r].second;
	});

	vector<int> ret(m);
	int l = 0, r = -1;
	for (int i : ord) {
		int ql, qr;
		tie(ql, qr) = q[i];
		while (r < qr) insert(++r);
		while (l > ql) insert(--l);
		while (l < ql) erase(l++);
		while (r > qr) erase(r--);

		//cout << ql << " " << qr << endl;
		//for (auto x : st) cout << x << " ";
		//cout << endl;
		//for (auto d : dif) cout << d << " ";
		//cout << endl;
		ret[i] = ans;
	}
	return ret;
}

int32_t main() {
	fast_io;

	int n; cin >> n;
	for (int i = 0; i < n; i++)
		cin >> v[i];

	int q; cin >> q;
	vector<pair<int, int>> a(q);
	for (auto &[l, r] : a) {
		cin >> l >> r;
		--l, --r;
	}

	auto ret = MO(a);
	for (int i = 0; i < q; i++)
		cout << ret[i] << endl;
}

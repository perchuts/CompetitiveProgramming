#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

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

int lazy[4*maxn], seg[4*maxn];

void push(int i, int l, int r) {
	seg[i] += lazy[i];
	if (l != r) lazy[2*i] += lazy[i], lazy[2*i+1] += lazy[i];
	lazy[i] = 0;
}

void upd(int i, int l, int r, int x, int y, int k) {
	push(i, l, r);
	if (r < x || y < l) return;
	if (x <= l && r <= y) {
		lazy[i] += k;
		push(i, l, r);
		return;
	}
	int md = (l + r) / 2;
	upd(2*i, l, md, x, y, k), upd(2*i+1, md+1, r, x, y, k);
	seg[i] = max(seg[2*i], seg[2*i+1]);
}

int query(int i, int l, int r, int x, int y) {
	push(i, l, r);
	if (r < x || y < l) return -1e18;
	if (x <= l && r <= y) return seg[i];
	int md = (l + r) / 2;
	return max(query(2*i, l, md, x, y), query(2*i+1, md+1, r, x, y));
}	

void solve(){
	int n, m; cin >> n >> m;
	vector<iii> intervals(m);
	vector<iii> events;
	for (auto [l, r, a] : intervals) {
		cin >> l >> r >> a;
		events.push_back({l, a, 0});
		events.push_back({r+1, a, l});
	}
	sort(all(events));
	int cur_penalty = 0, act = 0, ans = 0;
	for (int i = 1; i <= n; ++i) {
		while (act < 2 * m && get<0>(events[act]) <= i) {
			auto [a, b, c] = events[act++];
			if (c == 0) {
				cur_penalty += b;
			} else {
				cur_penalty -= b;
				upd(1, 1, n, c, a-1, b);
			}
		}
		int my = max(0ll, query(1, 1, n, 1, i-1));
		ckmax(ans, my + cur_penalty);
		upd(1, 1, n, i, i, my);
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}

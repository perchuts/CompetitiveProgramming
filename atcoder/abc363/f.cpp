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

void solve() {
	int n; cin >> n;
	if (n == 1) {
		cout << 1 << endl;
		return;
	}
	vector<int> divs, rev, divs2, pode;	
	for (int i = 1; i * i <= n; ++i) {
		if (n % i == 0) divs.pb(i);
		if (i * i != n) divs.pb(n/i);
	}
	sort(all(divs));
	map<int, int> vis, quem;
	for (auto x : divs) {
		pode.pb(1);
		while (x) pode.back() &= (x % 10 != 0), x /= 10;
	}
	queue<int> q;
	for (int i = 0; i < sz(divs); ++i) {
		if (!pode[i]) continue;
		string ss = to_string(divs[i]);
		reverse(all(ss));
		int y = stoll(ss);
		int tmp = divs[i];
		if (tmp <= n / y) tmp *= y;
		else tmp = n + 1;
		if (y == divs[i] && !vis[divs[i]]) {
			vis[divs[i]] = 1; q.push(divs[i]), quem[divs[i]] = -1;
			divs2.pb(divs[i]);
			rev.pb(y);
		} else if (n % tmp == 0 && !vis[tmp]) {
			divs2.pb(divs[i]);
			rev.pb(y);
			vis[tmp] = 1; q.push(tmp), quem[tmp] = sz(divs2)-1;
		}
	}	
	while (!q.empty() && !vis[n]) {
		auto x = q.front();
		q.pop();
		for (int i = 1; i < sz(divs2); ++i) {
			if (x > n / divs2[i]) continue;
			int y = x * divs2[i];
			if (y > n / rev[i]) continue;
			y *= rev[i];
			if (n % y || vis[y]) continue;
			vis[y] = 1, quem[y] = i;
			q.push(y);
		}
	}
	if (vis[n]) {
		deque<int> dq;
		function<void(int)> work = [&] (int x) {
			if (x == 1) return;
			if (quem[x] == -1) {
				dq.pb(x);
				return;
			}
			int y = x / divs2[quem[x]] / rev[quem[x]];
			work(y);
			dq.pb(divs2[quem[x]]);
			dq.push_front(rev[quem[x]]);
		};
		work(n);
		for (int i = 0; i < sz(dq); ++i) {
			cout << dq[i];
			if (i != sz(dq)-1) cout << "*";
		}
		cout << endl;
	}
	else cout << -1 << endl;
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}

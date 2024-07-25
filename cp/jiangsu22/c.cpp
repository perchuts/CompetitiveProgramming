#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

template<class T> struct minqueue {
	deque<pair<T, int>> q;

	void push(T x) {
		int ct = 1;
		while (q.size() and x < q.front().first)
			ct += q.front().second, q.pop_front();
		q.emplace_front(x, ct);
	}
	void pop() {
		if (q.back().second > 1) q.back().second--;
		else q.pop_back();
	}
	T min() { return q.back().first; }
};

int32_t main() {
	fast_io;

	int n; cin >> n;
	int q; cin >> q;
	int p; cin >> p;
	vector<int> A(n);
	for (auto &x : A) cin >> x;
	
	vector ans(n + 1, -LINF);
	for (int x = 1; x <= p; x++) {
		int k = p / x;
		vector<int> v;
		for (int i = x; i <= n; i += x) {
			v.push_back(A[i - 1]);
		}
		
		int m = v.size();
		vector dp(m + 1, 0LL);
		minqueue<int> mq;
		mq.push(-dp[m]);
		int sz = 1;
		for (int i = m - 1; i >= 0; --i) {
			//dp[i] = v[i];
			dp[i] = v[i] - mq.min();
			int pos = (i + 1) * x;
			if (pos + p > n)
				dp[i] = max(dp[i], v[i]);

			mq.push(-dp[i]); sz++;
			if (sz > k) {
				sz--;
				mq.pop();
			}
		}

		for (int i = 0; i < k; i++)
			ans[x] = max(ans[x], dp[i]);
	}

	while (q--) {
		int x; cin >> x;

		if (ans[x] == -LINF) cout << "Noob" << endl;
		else cout << ans[x] << endl;
	}

	return 0;
}


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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// Min queue - stack
//
// Tudo O(1) amortizado

template<class T> struct minstack {
	stack<pair<T, T>> s;

	void push(T x) {
		if (!s.size()) s.push({x, x});
		else s.emplace(x, std::min(s.top().second, x));
	}
	T top() { return s.top().first;	}
	T pop() {
		T ans = s.top().first;
		s.pop();
		return ans;
	}
	int size() { return s.size(); }
	T min() { return s.top().second; }
};

template<class T> struct minqueue {
	minstack<T> s1, s2;

	void push(T x) { s1.push(x); }
	void move() {
		if (s2.size()) return;
		while (s1.size()) {
			T x = s1.pop();
			s2.push(x);
		}
	}
	T front() { return move(), s2.top(); }
	T pop() { return move(), s2.pop(); }
	int size() { return s1.size()+s2.size(); }
	T min() {
		if (!s1.size()) return s2.min();
		else if (!s2.size()) return s1.min();
		return std::min(s1.min(), s2.min());
	}
};
void solve(){
    int n, m, n1, m1, n2, m2; cin >> n >> m >> n1 >> m1 >> n2 >> m2;
    vector<vector<int>> a(n, vector<int>(m));
    for (auto& x : a) for (auto& y : x) cin >> y;
    vector<vector<int>> ps(n+1, vector<int>(m+1));
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) ps[i][j] = ps[i-1][j] + ps[i][j-1] + a[i-1][j-1] - ps[i-1][j-1];
    auto get = [&] (int x1, int y1, int x2, int y2) { return ps[x2][y2] - ps[x1-1][y2] - ps[x2][y1-1] + ps[x1-1][y1-1]; };
    ckmin(n2, n1), ckmin(m2, m1);
    vector<minqueue<int>> mq(m+1);
    int ans = 0;
    for (int i = n-n2+1; i >= 1; --i) {
        minqueue<int> eu;
        for (int j = m-m2+1; j >= 1; --j) {
            mq[j].push(-get(i, j, i+n2-1, j+m2-1));
            if (sz(mq[j]) > n1-n2+1) mq[j].pop();
            eu.push(mq[j].min());
            if (sz(eu) > m1-m2+1) eu.pop();
            if (i <= n-n1+1 and j <= m-m1+1) ckmax(ans, get(i, j, i+n1-1, j+m1-1) + eu.min());
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

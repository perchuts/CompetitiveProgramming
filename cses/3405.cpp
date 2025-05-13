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
		else s.emplace(x, (s.top().second|x));
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
		return (s1.min()|s2.min());
	}
};
void solve(){
    int k, n; cin >> n >> k;
    int x, a, b, c; cin >> x >> a >> b >> c;
    int ans = (k == 1 ? x : 0);
    minqueue<int> mq;
    mq.push(x);
    for (int i = 1; i < n; ++i) {
        x = (x*a + b) % c;
        mq.push(x);
        if (sz(mq) > k) mq.pop();
        if (sz(mq) == k) ans ^= mq.min();
    }
    cout << ans << endl;
}
 
int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

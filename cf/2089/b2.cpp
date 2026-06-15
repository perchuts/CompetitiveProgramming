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
    bool empty() { return this->size() == 0; }
	T pop() { return move(), s2.pop(); }
	int size() { return s1.size()+s2.size(); }
	T min() {
		if (!s1.size()) return s2.min();
		else if (!s2.size()) return s1.min();
		return std::min(s1.min(), s2.min());
	}
};

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    int S = 0;
    for (auto& x : a) cin >> x, S += x;
    for (auto& x : b) cin >> x;
    if (S == k) {
        cout << 0 << endl;
        return;
    }
    int pos = -1, s = 0;
    vector<ii> stk;
    stk.pb({-1e18, -inf});
    for (int i = 0; i < 2*n; ++i) {
        s += a[i%n] - b[i%n];
        //cout << s << " ";
        while (stk.back().first >= s) stk.pop_back();
        if (n <= i and stk.back().second + n <= i) pos = i;
        stk.pb({s, i});
    }
    //cout << endl;
    //cout << flush;
    assert(pos != -1);
    vector<int> tp(n);
    for (int i = 0; i < n; ++i) tp[i] = a[(i+1+pos)%n];
    a = tp;
    //for (auto x : tp) cout << x << " ";
    //cout << endl;
    for (int i = 0; i < n; ++i) tp[i] = b[(i+1+pos)%n];
    b = tp;
    //for (auto x : tp) cout << x << " ";
    //cout << endl;
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        if (i) c[i] = c[i-1];
        c[i] += a[i] - b[i];
    }
    assert(c.back() == *min_element(all(c)));
    //for (auto x : c) cout << x << " ";
    //cout << endl;
    auto possible = [&] (int x) {
        int cost = 0;
        minqueue<int> mq;
        for (int i = n-2; i >= -1; --i) {
            if (n-x-1 < i) mq.push(c[i+1]);
            else {
                int val = c[i+1] + cost;
                int best = min((mq.empty()?inf*inf:mq.min())-cost, c[i+1]);
                cost += max(0LL, best - (~i ? c[i] : 0LL));
                mq.push(val);
                mq.pop();
            }
        }
        return (cost <= k);
    };
    int l = 1, r = n-1, ans = n;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md, r = md-1;
        else l = md+1;
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

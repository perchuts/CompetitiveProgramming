#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato
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
vector<int> brute(string s, int n, int q, vector<ii> qu) {
    vector<int> dp(1<<n), good(1<<n);
    for (int i = 1; i < (1 << n); ++i) {
        string t;
        for (int j = 0; j < n; ++j) if (i >> j & 1) t += s[j];
        bool ok = 1;
        for (int j = 1; j < sz(t); ++j) ok &= (t[j] != t[j-1]);
        good[i] = ok;
    }
    for (int i = 1; i < (1 << n); ++i) {
        dp[i] = n;
		for (int l = 0; l < n; ++l) {
			int m = 0;
			for (int r = l; r < n; ++r) {
				if (i >> r & 1) m += (1 << r);
				if (good[m]) ckmin(dp[i], dp[i-m]+1);
			}
		}
    }
    vector<int> ans;
    for (auto [l, r] : qu) {
        // 2^{r+1} - 2^l
        int t = (2 << r) - (1 << l);
        ans.pb(dp[t]);
    }
    return ans;
}

vector<int> solve_slow(string s, int n, int q, vector<ii> qu) {
    vector<int> resp;
    for (auto [l, r] : qu) { 
        vector<int> v;
        int c = 1;
        for (int i = l+1; i <= r; ++i) {
            if (s[i] != s[i-1]) v.pb(c), c = 1;
            else c++;
        }
        v.pb(c);
        stack<int> st;
        int tem_1 = 0, ans = 0;
        for (auto x : v){
            if (x == 1) tem_1 ^= 1;
            else {
                if (tem_1 or st.empty()) st.push(x), tem_1 = 0;
                else {
                    while (!st.empty()) {
                        int y = st.top(); st.pop();
                        int k = min(x, y) - 1;
                        ans += k, x -= k, y -= k;
                        if (x == y) { tem_1 = 1; break; }
                        if (x == 1) {
                            st.push(y);
                            tem_1 = 1;
                            break;
                        }
                    }
                    if (x > 1) st.push(x), tem_1 = 0;
                }
            }
        }
        resp.pb(r-l+1-(sz(v)-1)-ans);
    }
    return resp;
}
// 11011001101
// 2 1 2 2 2 1 1
// 2
// 2 1
// 2 1 2
// 2 1 (1)
// 2 1 2 (1)
//
// MO
//
// Para ter o bound abaixo, escolher
// SQ = n / sqrt(q)
// 
// O(n * sqrt(q))

const int MAX = 2e5+10;
const int SQ = sqrt(MAX);
int v[MAX], ps[MAX];


inline ll hilbert(int x, int y) {
	static int N = 1 << (__builtin_clz(0) - __builtin_clz(MAX));
	int rx, ry, s;
	ll d = 0;
	for (s = N/2; s > 0; s /= 2) {
		rx = (x & s) > 0, ry = (y & s) > 0;
		d += s * ll(s) * ((3 * rx) ^ ry);
		if (ry == 0) {
			if (rx == 1) x = N-1 - x, y = N-1 - y;
			swap(x, y);
		}
	}
	return d;
}

#define HILBERT true
vector<int> MO(vector<pair<int, int>> &q) {
	int ans = 0;
	int m = q.size();
	vector<int> ord(m);
	iota(ord.begin(), ord.end(), 0);
#if HILBERT
	vector<ll> h(m);
	for (int i = 0; i < m; i++) h[i] = hilbert(q[i].first, q[i].second);
	sort(ord.begin(), ord.end(), [&](int l, int r) { return h[l] < h[r]; });
#else
	sort(ord.begin(), ord.end(), [&](int l, int r) {
		if (q[l].first / SQ != q[r].first / SQ) return q[l].first < q[r].first;
		if ((q[l].first / SQ) % 2) return q[l].second > q[r].second;
		return q[l].second < q[r].second;
	});
#endif
	vector<int> ret(m);
	int l = 0, r = -1;
    deque<int> dq;
    array<int, 2> s; s[0] = s[1] = 0;
	for (int i : ord) {
		int ql, qr;
		tie(ql, qr) = q[i];
		while (r < qr) {
            //insertR(++r);
            ++r;
            if (dq.empty() or v[r-1] != v[r]) dq.pb(1), s[(sz(dq)%2)^1]++;
            else dq.back()++, s[(sz(dq)%2)^1]++;
        }
		while (l > ql) {
            --l;
            if (dq.empty() or v[l] != v[l+1]) {
                swap(s[0], s[1]);
                dq.push_front(1);
                s[0]++;
            }
            else dq.front()++, s[0]++;
            //insertL(--l);
        }
		while (l < ql) {
            s[0]--;
            if (dq.front() == 1) dq.pop_front(), swap(s[0], s[1]);
            else dq.front()--;
			l++;
            //eraseL(l++);
        }
		while (r > qr) {
            s[(sz(dq)%2)^1]--;
            if (dq.back() == 1) dq.pop_back();
            else dq.back()--;
			r--;
            //eraseR(r--);
        }
        int lb = ps[r] - ps[l] + 1;
		int k = min(s[0] - (sz(dq)+1)/2, s[1] - sz(dq)/2);
		ret[i] = lb -min(s[0] - (sz(dq)+1)/2, s[1] - sz(dq)/2);
	}
	return ret;
}
vector<int> solve_opt(string s, int n, int q, vector<ii> qu) {
    vector<int> resp;
	// soma par, soma impar, quantos tem
    for (auto [l, r] : qu) { 
        vector<int> v;
        int c = 1;
        for (int i = l+1; i <= r; ++i) {
            if (s[i] != s[i-1]) v.pb(c), c = 1;
            else c++;
        }
        v.pb(c);
        int tem_1 = 0, ans = 0, score = 0;
		int par = 0, impar = 0;
		for (int i = 0; i < sz(v); ++i) {
			if (i & 1) impar += v[i]-1;
			else par += v[i]-1;
		}
        resp.pb(r-l+1-(sz(v)-1)-min(par, impar));
    }
	// 1 3 1 1 4 1 3 1 2
	// 3 4 1 3 1 2
	// 1 2 1 3 1 2
    return resp;
}

vector<int> solve(string s, int n, int q, vector<ii> qu) {
    for (int i = 1; i < n; ++i) ps[i] = ps[i-1] + (s[i] == s[i-1]);
    for (int i = 0; i < n; ++i) v[i] = (s[i] == '1');
    return MO(qu);
}
int32_t main() {_
#ifndef gato
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<ii> qu(q);
    for (auto& [x, y] : qu) cin >> x >> y, --x, --y;
    auto ans = solve(s, n, q, qu);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 100000), q = 100;
        string s(n, '0');
        for (auto& x : s) if (rnd(0, 1)) x = '1';
        vector<ii> qu(q);
        for (auto& [x, y] : qu) x = rnd(0, n-1), y = rnd(x, n-1);
		qu[0] = {0, n-1};
        auto my = solve(s, n, q, qu);
        auto ans = solve_opt(s, n, q, qu);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << q << endl;
            cout << s << endl;
            for (auto [l, r] : qu) cout << l+1 << " " << r+1 << endl;
            cout << "Solve: ";
            for (auto x : my) cout << x << " ";
            cout << endl;
            cout << "Brute: ";
            for (auto x : ans) cout << x << " ";
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

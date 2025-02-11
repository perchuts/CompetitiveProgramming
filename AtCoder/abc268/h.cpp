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

struct aho_corasick {
    struct vertex {
        char pch;
        int go[26], next[26], link = -1, p, len = 0;
        bool exist = false;
        vertex(char c, int p_): pch(c), p(p_) {
            for (int i = 0; i < 26; ++i) go[i] = next[i] = -1;
        }
    };

    vector<vertex> t;
    vector<int> dp;

    aho_corasick() {
        t.emplace_back('a', 0);
    }

    void add_string(string s) {
        int cur = 0;
        for (auto x : s) {
            if (t[cur].next[x-'a'] == -1) {
                t[cur].next[x-'a'] = sz(t);
                t.emplace_back(x, cur);
                t.back().len = t[cur].len + 1;
            }
            cur = t[cur].next[x-'a'];
        }
        t[cur].exist = true;
    }

    int go();

    int link(int pos) {
        if (t[pos].link != -1) return t[pos].link;
        if (t[pos].len <= 1) return t[pos].link = 0; 
        return t[pos].link = go(link(t[pos].p), t[pos].pch); 
    }

    int go(int pos, char c) {
        if (t[pos].go[c-'a'] != -1) return t[pos].go[c-'a'];
        if (t[pos].next[c-'a'] != -1) return t[pos].go[c-'a'] = t[pos].next[c-'a'];
        return t[pos].go[c-'a'] = (pos ? go(link(pos), c) : 0);
    }

    void work() {
        queue<int> q;
        dp = vector<int>(sz(t), inf);
        q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            dp[u] = dp[link(u)];
            if (t[u].exist) ckmin(dp[u], t[u].len);
            for (int i = 0; i < 26; ++i) {
                int v = t[u].next[i];
                if (v != -1) q.push(v);
            }
        }
    }
};

void solve(){
    string s; cin >> s;
    int n = sz(s);
    int m; cin >> m;
    vector<string> t(m);
    aho_corasick aho;
    minqueue<int> mq;
    for (auto& st : t) cin >> st, aho.add_string(st);
    aho.work();
    int state = 0;
    mq.push(0);
    for (int i = 0; i < n; ++i) {
        int dp_cur = 1 + mq.min();
        state = aho.go(state, s[i]);
        while (aho.dp[state] <= mq.size()) mq.pop();
        mq.push(dp_cur);
    }
    cout << mq.min() << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

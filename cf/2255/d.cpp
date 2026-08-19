#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int solve(int n, vector<int> a) {
    sort(all(a));
    int l = 1, r = 60, opt = r;
    auto possible = [&] (int x) {
        priority_queue<int> pq;
        for (int i = 0; i < min(n, 30LL); ++i) pq.push(a[i]);
        for (int i = x-1; ~i; --i) {
            int k = pq.top(); pq.pop();
            if (k > (1LL << i)) pq.push(k - (1LL << i));
            if (pq.empty()) return true;
        }
        return false;
    };
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) opt = md, r = md-1;
        else l = md+1;
    }
    return opt + max(n - 30, 0LL);
}

map<vector<int>, int> dp;

int brute(int n, vector<int> a) {
    auto solve = [&] (auto&& self, vector<int> cur) -> int {
        sort(all(cur));
		reverse(all(cur));
		while (!cur.empty() and cur.back() == 0) cur.pop_back();
		reverse(all(cur));
        if (dp.count(cur)) return dp[cur];
		if (cur.empty()) return 0;
        int opt = inf;
        for (int i = 0; i < sz(cur); ++i) { 
            auto cc2 = cur;
            for (int j = 0; j < sz(cur); ++j) {
                if (i == j) cc2[j] = (cc2[j] / 2);
                else cc2[j] = (cc2[j]+1)/2;
            }
            ckmin(opt, self(self, cc2)+1);
        }
		assert(opt != inf);
        return dp[cur] = opt;
    };
	sort(all(a));
    return solve(solve, a);
}

int32_t main() {_
    //int n; cin >> n;
    //vector<int> a(n);
    //for (auto& x : a) cin >> x;
    //cout << brute(n, a) << endl;
    //exit(0);
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        cout << solve(n, a) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 60);
        vector<int> a(n);
        for (auto& x : a) x = rnd(1, 15);
        int my = solve(n, a), ans = brute(n, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

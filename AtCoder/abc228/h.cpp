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
// Convex Hull Trick Estatico
//
// adds tem que serem feitos em ordem de slope
// queries tem que ser feitas em ordem de x
//
// add O(1) amortizado, get O(1) amortizado

struct CHT {
	int it;
	vector<ll> a, b;
	CHT():it(0){}
	ll eval(int i, ll x){
		return a[i]*x + b[i];
	}
	bool useless(){
		int sz = a.size();
		int r = sz-1, m = sz-2, l = sz-3;
#warning cuidado com overflow!
		return (b[l] - b[r])*(a[m] - a[l]) <
			(b[l] - b[m])*(a[r] - a[l]);
	}
	void add(ll A, ll B){
		a.push_back(A); b.push_back(B);
		while (!a.empty()){
			if ((a.size() < 3) || !useless()) break;
			a.erase(a.end() - 2);
			b.erase(b.end() - 2);
		}
		it = min(it, int(a.size()) - 1);
	}
	ll get(ll x){
		while (it+1 < a.size()){
			if (eval(it+1, x) > eval(it, x)) it++;
			else break;
		}
		return eval(it, x);
	}
};
int solve(int n, int x, vector<int> a, vector<int> c) {
    // dp[val] = min_j (dp[j] + \sum(j<k<val) { sx[j] * (val - j) }) + x
    // dp[val] = min_j (dp[j] + \sum(j<k<val) { sx[k] * val - sx[k] * k }) + x
    // dp[val] = min_j (dp[j] + \sum(j<k<val) { sx[k] } * val - \sum(j<k<val) { sx[k] * k }) + x
    // Let P[i] = \sum(1<=j<=i) sx[j] * j
    // dp[val] = min_j (dp[j] + \sum(j<k<val) { sx[k] } * val) + P[j] - P[i] + x
    // dp[val] = min_j (dp[j] + P[j] + \sum(j<k<val) { sx[k] } * val) - P[i] + x
    // Let S[i] = \sum(1<=j<=i) sx[j]
    // dp[val] = min_j (dp[j] + P[j] + (S[i-1]-S[j]) * val) - P[i] + x
    // dp[val] = min_j (dp[j] + P[j] - S[j] * val) - P[i] + x + S[i-1] * val
    // pretty much convex hull trick: want minimum every time, queries are increasing with X
    int N = *max_element(all(a));
    vector<int> sx(N+1), S(N+1), P(N+1);
    auto aa = a;
    sort(all(aa)); aa.erase(unique(all(aa)), end(aa));
    for (int i = 0; i < n; ++i) sx[a[i]] += c[i];
    for (int i = 1; i <= N; ++i) S[i] = S[i-1] + sx[i], P[i] = P[i-1] + i * sx[i];
    CHT cht;
    int ret;
    for (auto i : aa) {
        int best = x + S[i-1] * i - P[i-1];
        if (!cht.a.empty()) ckmin(best, -cht.get(i) - P[i-1] + x + S[i-1] * i);
        int b = -(best + P[i]), a = S[i];
        if (i == N) ret = best;
        cht.add(a, b);
    }
    return ret;
}

int brute(int n, int x, vector<int> a, vector<int> c) {
    int N = *max_element(all(a));
    vector<int> dp(N+1), sx(N+1);
    auto aa = a;
    sort(all(aa)); aa.erase(unique(all(aa)), end(aa));
    for (int i = 0; i < n; ++i) sx[a[i]] += c[i];
    for (int i = 0; i < sz(aa); ++i) {
        int cost = 0;
        dp[aa[i]] = 1e18;
        for (int j = i-1; j >= 0; --j) {
            ckmin(dp[aa[i]], dp[aa[j]] + cost + x);
            cost += (aa[i]-aa[j]) * sx[aa[j]];
        }
        ckmin(dp[aa[i]], cost + x);
    }
    return dp[N]; 
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, x; cin >> n >> x;
    vector<int> a(n), c(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> c[i];
    cout << solve(n, x, a, c) << endl;
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

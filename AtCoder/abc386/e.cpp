#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define stress

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
int solve(int n, int K, vector<int> v){
	int tudo = 0, ans = 0;
	for (int i = 0; i < n; ++i) tudo ^= v[i];
	if (K == 1 or K == n-1) {
		if (K == 1) tudo = 0;
		for (int i = 0; i < n; ++i) ckmax(ans, tudo ^ v[i]);
	} else if (K == 2 or K == n-2) {
		if (K == 2) tudo = 0;
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) 
				ckmax(ans, tudo ^ v[i] ^ v[j]);	
	} else if (K == 3 or K == n-3) {
		if (K == 3) tudo = 0;
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) 
				for (int k = j + 1; k < n; ++k) 
					ckmax(ans, tudo ^ v[i] ^ v[j] ^ v[k]);	
	} else if (K == 4 or K == n-4) {
		if (K == 4) tudo = 0; 
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) 
				for (int k = j + 1; k < n; ++k) 
					for (int w = k + 1; w < n; ++w) 
						ckmax(ans, tudo ^ v[i] ^ v[j] ^ v[k] ^ v[w]);	
	} else if (K == 5 or K == n-5) {
		if (K == 5) tudo = 0; 
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) 
				for (int k = j + 1; k < n; ++k) 
					for (int w = k + 1; w < n; ++w) 
						for (int p = w + 1; p < n; ++p) 
							ckmax(ans, tudo ^ v[i] ^ v[j] ^ v[k] ^ v[w] ^ v[p]);
	} else if (K == 6 or K == n - 6) {
		if (K == 6) tudo = 0; 
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) 
				for (int k = j + 1; k < n; ++k) 
					for (int w = k + 1; w < n; ++w) 
						for (int p = w + 1; p < n; ++p) 
							for (int z = p + 1; z < n; ++z)
								ckmax(ans, tudo ^ v[i] ^ v[j] ^ v[k] ^ v[w] ^ v[p] ^ v[z]);
	} else if (K == 7 or K == n - 7) {
		if (K == 7) tudo = 0; 
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) 
				for (int k = j + 1; k < n; ++k) 
					for (int w = k + 1; w < n; ++w) 
						for (int p = w + 1; p < n; ++p) 
							for (int z = p + 1; z < n; ++z)
								for (int s = z+1; s < n; ++s)
								ckmax(ans, tudo ^ v[i] ^ v[j] ^ v[k] ^ v[w] ^ v[p] ^ v[z] ^ v[s]);
	} else {
		for (int i = 0; i < (1 << n); ++i) {
			int xx = 0;
			if (__builtin_popcount(i) != K) continue;
			for (int j = 0; j < n; ++j) {
				if (i >> j & 1) xx ^= v[j];
			}
			ckmax(ans, xx);
		}
	}
	return ans;
}

using namespace chrono;
class timer: high_resolution_clock {
    const time_point start_time;
public:
    timer(): start_time(now()) {}
    rep elapsed_time() const { return duration_cast<milliseconds>(now()-start_time).count(); } };
int brute(int n, int k, vector<int> v) {
	int ans = 0;
	stack<iii> st;
	st.push({n, 0, k});
	timer t;
	while (!st.empty() && t.elapsed_time() < 1200) {
		auto [pos, val, x] = st.top(); st.pop();
		if (x == 0) ckmax(ans, val);
		else for (int i = pos-1; i >= x-1; --i) st.push({i, val ^ v[i], x-1});
	}
	return ans;
}
int32_t main(){_
#ifdef stress
	int t = 1;
	while (true) {
		int n = rnd(1, 18), k = rnd(1, n);
		vector<int> v(n);
		for (auto& x : v) x = rnd(0, 1e18);
		int my = solve(n, k, v), br = brute(n, k, v);
		if (my != br) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << " " << k << endl;
			for (auto x : v) cout << x << ' ';
			cout << endl;
			cout << "Your output: " << my << endl;
			cout << "Answer: " << br << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#else
	int n, k; cin >> n >> k;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	cout << max(brute(n, k, v), solve(n, k, v)) << endl;
#endif
}

#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
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


const int MAX = 5e5 + 60;
const int MAX2 = 19;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
namespace sparse {
	int m[MAX2][MAX], n;
	void build(int n2, vector<int> v) {
		n = n2;
		for (int i = 0; i < n; i++) m[0][i] = v[i];
		for (int j = 1; (1<<j) <= n; j++) for (int i = 0; i+(1<<j) <= n; i++)
			m[j][i] = max(m[j-1][i], m[j-1][i+(1<<(j-1))]);
	}
	int query(int a, int b) {
		int j = __builtin_clz(1) - __builtin_clz(b-a+1);
		return max(m[j][a], m[j][b-(1<<j)+1]);
	}
}

int solve(int n, vector<int> a){
	sparse::build(n, a);
	vector<int> h(n+1);
	int ans = 0;
	for (int g = n; g >= 1; --g) {
		stack<array<int, 4>> st; 
		while (!st.empty()) st.pop();
		st.push({inf, 0, 0, inf});
		for (int i = 0; i < n/g; ++i) {
			int eu = sparse::query(i*g, i*g+g-1);
			array<int, 4> arr;
			arr[1] = 1, arr[2] = a[i*g+g-1], arr[3] = a[i*g+g-1];
			while (st.top()[0] < eu) arr[2] += st.top()[1] * eu, arr[1] += st.top()[1], st.pop(), arr[2] %= mod;
			if (st.top()[3] < eu) arr[2] = (arr[2] + eu) % mod, arr[2] = (arr[2] + mod - st.top()[3]);	
			arr[2] = (arr[2] + st.top()[2]);
			h[g] = (h[g] + arr[2]) % mod;
			if (i != n/g-1) arr[0] = sparse::query((i?i*g:i*g+g-1), i*g+g-1), st.push(arr);
		}
		for (int gg = 2*g; gg <= n; gg += g) h[g] = (h[g] - h[gg] + mod) % mod;
		ans = (ans + g * g % mod * h[g]) % mod;
	}
	return ans;
}

int brute(int n, vector<int> a) {
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; ++j) {
			int g = gcd(i, j), mx = 0;
			for (int k = i-1; k < j; ++k) mx = max(mx, a[k]); 
			ans += g * g * mx;
			ans %= mod;
		}
	}
	return ans;
}

int32_t main(){_
#ifdef stress
	int t = 1;
	while (true) {
		int n = rnd(1, 50);
		vector<int> v(n);
		for (auto& x : v) x = rnd(1, 1e9);
		int my = solve(n, v), ans = brute(n, v);
		if (my != ans) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << endl;
			for (auto x : v) cout << x << ' ';
			cout << endl;
			cout << "Your output: " << my << endl;
			cout << "Answer: " << ans << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#else
	int n; cin >> n;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	cout << solve(n, v) << endl;
#endif
}

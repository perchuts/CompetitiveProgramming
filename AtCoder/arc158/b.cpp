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

void solve(int n, vector<int> a){
	double ans1 = (a[0]+a[1]+a[2])/(double)(a[0]*a[1]*a[2]), ans2 = ans1;
	double ans3 = ans1, ans4 = ans2;
	iii x={0,1,2}, y={0,1,2};
	sort(all(a));
	for (int i = 0; i < n-2; ++i) {
		int j = i + 1, k = i + 2;
		double s = a[i] + a[j] + a[k];
		double p = a[i] * a[j] * a[k];
		if(ckmax(ans3, s/p)) x = {i, j, k};
		if(ckmin(ans4, s/p)) y = {i, j, k};
	}
	for (int i = 0; i < n-2; ++i) {
		int j = i + 1, k = n-1;
		double s = a[i] + a[j] + a[k];
		double p = a[i] * a[j] * a[k];
		if(ckmax(ans3, s/p)) x = {i, j, k};
		if(ckmin(ans4, s/p)) y = {i, j, k};
	}
	for (int i = 1; i < n-1; ++i) {
		int j = i + 1, k = 0;
		double s = a[i] + a[j] + a[k];
		double p = a[i] * a[j] * a[k];
		if(ckmax(ans3, s/p)) x = {i, j, k};
		if(ckmin(ans4, s/p)) y = {i, j, k};
	}
	cout << fixed << setprecision(15) << ans4 <<  endl;
	cout << fixed << setprecision(15) << ans3 <<  endl;
}

int32_t main(){_
	int n; cin >> n;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	solve(n, a);
}

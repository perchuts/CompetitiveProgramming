#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
#define szo(x) ((int)x.size())
using namespace std;

using ll = long long;

const int maxn = 6010;
int dp[maxn][maxn];
int hs[maxn];
int suf[maxn];
int pref[maxn];
int st[maxn];
int pt[maxn];
int n;

int cost(int l, int r){
	l--;

	int m1 = (l+r)/2;
	int m2 = (l+r+1)/2;

	int sum = 0;

	int v1 = pref[m1]-pref[l]-l*(pt[m1]-pt[l]);
	int v2 = suf[m2]-suf[r]-(n-r+1)*(st[m2]-st[r]);
	sum = v1+v2;

	int le = (r-l+1);
	if (le&1){
		int mid = (l+r)/2;
		sum -= (mid-l)*hs[mid];
	}

	return sum;
}

const int INF = 1e18;

void solve(int k){
	int lins = n+1;
	vector<int> opt(2*n+10,n);

	auto mat = [&](int i, int j){
		if (j >= 1) return dp[k-1][j-1] + cost(j,i);
		return (j>i) ? INF+j : INF-j;
	};	

	function<void(int, vector<int>&)> smawk = [&](int p, vector<int> &cols){
		if ((1<<p) > lins) return;
		vector<int> ncols = {cols[0]};
		for (int j = 1; j < szo(cols); ++j){
			while (!ncols.empty()){
				int h = szo(ncols);
				if (mat((h<<p)-1, ncols.back()) < mat((h<<p)-1, cols[j])) break;
				ncols.pop_back();
			}
			if ((szo(ncols)<<p) < lins) ncols.pb(cols[j]);
		}

		smawk(p+1,ncols);

		int pot = 1<<p, j = 0;
		for (int i = pot-1; i < lins; i += 2*pot, --j){
			opt[i] = cols[j];
			for (; j < szo(cols) and cols[j] <= opt[i+pot]; ++j){
				if (mat(i,cols[j]) <= mat(i,opt[i])) opt[i] = cols[j];
			}		
		}
	};

	vector<int> cols(n);
	iota(cols.begin(), cols.end(), 1);
	smawk(0,cols);

	for (int i = 1; i <= n; ++i) dp[k][i] = mat(i,opt[i]);
}

int32_t main() {_
	int b, c; cin >> n >> b >> c;
	for (int i = 1; i <= n; ++i) cin >> hs[i];

	for (int i = 1; i <= n; ++i) pt[i] = st[i] = hs[i];
	for (int i = 1; i <= n; ++i) pref[i] = i*hs[i];
	for (int i = 1; i <= n; ++i) suf[i] = (n-i+1)*hs[i];
	for (int i = 1; i <= n; ++i) pt[i] += pt[i-1], pref[i] += pref[i-1];
	for (int i = n; i >= 0; --i) st[i] += st[i+1], suf[i] += suf[i+1];

	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= n; ++j) dp[i][j] = INF;

	for (int i = 1; i <= n; ++i){
		dp[1][i] = suf[1] - suf[i] - (n-i+1) * (st[1]-st[i]);
	}

	vector<int> ans;

	for (int j = 1; j <= n; ++j){
		if (j > 1) solve(j);

		int best = INF;
		for (int e = 1; e <= n; ++e){
			int plus = 0;
			if (e < n){
				plus = pref[n]-pref[e]-e*(pt[n]-pt[e]);
			}
			int val = dp[j][e] + plus;
			if (val > best) continue;
			int w = val * c + j * b;
			best = min(best, w);
		}
		ans.pb(best);
	}

	for (auto v : ans) cout << v << " ";
	cout << endl;
}

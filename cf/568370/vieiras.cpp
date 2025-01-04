#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define f first
#define s second
typedef pair<int, int>ii;
typedef long long ll;

const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;

const int MAX = 200010;
const int MAX2 = 20;
const int mod = 998244353;

int pot[21];
int pre[MAX];
int lst[MAX][30];

int v[MAX];
unordered_map<int, int> memu;
unordered_map<int, int> comp;
vector<vector<pair<int, int>>> segments; 
int n;
int conta = 0;
int dp(int i, int j, int k){
    ll h = (((1000000007)*ll(i) + ll(j)*(1000000009))%1000000000000000ll + ll(k)*(998244353)) % 1000000000000000;
    if(i==n-1 and k==1) return 1;
    if(i==n-1 and k==0) return 0;
    int t = h;
    if(comp[t]){
        return memu[t];
    }
    comp[t] = true;
    if(k==0){
        return memu[t] = (dp(i+1, j|v[i], 0) + dp(i+1, j|v[i], 1))%mod;
    }
	int valor = j|v[i];
	int w = lower_bound(begin(segments[i+1]), end(segments[i+1]), make_pair(valor, 0)) - begin(segments[i+1]);
	if (w < segments[i+1].size()) {
		auto [val2, p] = segments[i+1][w];
		return memu[t] = (dp(p, val2, 0) + dp(p, val2, 1)) % mod;
	}
	return memu[t] = 0;
}


int32_t main(){_
    cin >> n;
    for(int i = 0; i < n; i++) cin >> v[i];
	
	for (int i = n-1; ~i; --i) {
		for (int j = 0; j < 30; ++j) {
			if (v[i] >> j & 1) lst[i][j] = i;
			else lst[i][j] = (i == n-1 ? n : lst[i+1][j]);
		}
	}
	segments.resize(n);
	for (int i = 0; i < n; ++i) {
		int cur = 0, r = i;
		while (r < n) {
			cur |= v[r];
			segments[i].emplace_back(cur, r);
			int nr = n;
			for (int j = 0; j < 30; ++j) {
				if (cur >> j & 1) {}
				else nr = min(nr, lst[i][j]);
			}
			r = nr;
		}
	}
    int ans = dp(0, 0, 0);
    ans = (ans+dp(0, 0, 1))%mod;
    cout << ans << endl;
}


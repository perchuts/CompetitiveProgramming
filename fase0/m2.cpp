#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
 
using namespace std;
	
#define int long long
#define PI pair<int,int>
#define f first
#define s second
#define pb push_back
#define szo(x) ((int)x.size())

const int maxn = 1e5+10;
int freq[maxn];

const int mod = 998244353;
int binexp(int a, int b){
	int ret = 1;
	while (b){
		if (b&1) ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}

int inv(int x){
	return binexp(x, mod-2);
}

int meb[maxn];
int nums[maxn];

int p2[maxn];
vector<int> divs[maxn];

vector<int> esperto[maxn];
int ans[maxn];

int32_t main(){
	for (int i = 1; i < maxn; ++i)
		for (int j = i; j < maxn; j += i) divs[j].pb(i);

	for (int i = 2; i < maxn; ++i) meb[i] = 2;
	meb[1] = 1;
	for (int i = 2; i < maxn; ++i)if (meb[i] == 2)
		for (int j = i; j < maxn; j += i) if (meb[j]) {
			if (meb[j] == 2) meb[j] = 1;
			meb[j] *= j/i%i ? -1 : 0;
		}
    
    for (int i = 1; i < maxn; ++i) if (meb[i])
		for (int j = i; j < maxn; j += i) esperto[j].pb(i);

	p2[0] = 1;
	for (int i = 1; i < maxn; ++i) p2[i] = p2[i-1] * 2 % mod;

	int n; cin >> n;
	for (int i = 0; i < n; ++i){
		int x; cin >> x;
		nums[i] = x;
		for (auto v : divs[x]) freq[v]++;
	}

    for (int x = 1; x < maxn; ++x){
        int res = 0;
        for (int i = 1; i*x < maxn; ++i){
				int cur = (mod + p2[freq[i*x]] - 1) % mod;
				cur = cur * meb[i];
				cur = (mod + cur) % mod;
				res = (res + cur) % mod;
        }
        ans[x] = res;
    }
	
	int tot = binexp(2, n);
	tot = (mod + tot - 1) % mod;
	int itot = inv(tot);

	int q; cin >> q;
	while (q--){
		int c; cin >> c;
		if (c == 1){
			int x; cin >> x;
			cout << ans[x]*itot%mod << '\n';
		}
		else{
			int p, x; cin >> p >> x;
			p--;
			int y = nums[p];
			if (x == y) continue;

			for (auto v : divs[y]){
				int sob = y/v;
				for (auto u : esperto[sob]){
					int cur = (mod + p2[freq[u*v]] - 1) % mod;
                    cur = cur * meb[u];
                    cur = (mod + cur) % mod;
                    ans[v] = (mod + ans[v] - cur) % mod;
				}
 			}

			for (auto v : divs[y]) freq[v]--;

            for (auto v : divs[y]){
				int sob = y/v;
				for (auto u : esperto[sob]){
					int cur = (mod + p2[freq[u*v]] - 1) % mod;
                    cur = cur * meb[u];
                    cur = (mod + cur) % mod;
                    ans[v] = (ans[v] + cur) % mod;
				}
 			}

            for (auto v : divs[x]){
				int sob = x/v;
				for (auto u : esperto[sob]){
					int cur = (mod + p2[freq[u*v]] - 1) % mod;
                    cur = cur * meb[u];
                    cur = (mod + cur) % mod;
                    ans[v] = (ans[v] + mod - cur) % mod;
				}
 			}

			for (auto v : divs[x]) freq[v]++;

			for (auto v : divs[x]){
				int sob = x/v;
				for (auto u : esperto[sob]){
					int cur = (mod + p2[freq[u*v]] - 1) % mod;
                    cur = cur * meb[u];
                    cur = (mod + cur) % mod;
                    ans[v] = (ans[v] + cur) % mod;
				}
 			}

			nums[p] = x;
		}
	}

	return 0;
}
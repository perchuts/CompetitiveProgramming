#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define eb emplace_back
#define pu push
#define ins insert
#define fi first
#define se second
#define all(a) a.begin(),a.end()
#define bruh ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define fu(x,a,b) for (auto x=a;x<=b;x++)
#define fd(x,a,b) for (auto x=a;x>=b;x--)
#define int ll

using namespace std;
//mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());

/*
Competitive Programming notes that I need to study & fix my dumbass self:

1. Coding:
- Always be sure to check the memory of arrays (maybe use vectors), for loops
- Always try to maximize the memory if possible, even if you are going for subtasks
- Do not exploit #define int long long, it will kill you

2. Stress: 
- Always try generating big testcases and try if they run

3. Time management:
- Don't overcommit or undercommit, always spend a certain amount of time to think a problem, don't just look at it and say I'm fucked
- Do not spend too much time coding brute-force solutions, they should be easily-codable solutions that don't take up too much time

Time management schedule:
Offline / LAH days (4 problems - 3h):
15' thinking of solution / idea
1. no idea: skip
2. yes idea: continue thinking for <= 15'

+ implementing: <= 20'
+ brute-force: <= 5'
+ test generator: <= 5'

I hate offline because I am dumb
*/

typedef pair<int, int> ii;
const int N = 3e5+5;
const int B = 750;
const int mod = 1e9+7;
const int inf = 1e18;
using cd = complex<double>;
const long double PI = acos(-1);
int power(int a,int b) {ll x = 1;if (a >= mod) a%=mod; while (b) {if (b & 1) x = x*a % mod;a = a*a % mod;b>>=1;}return x;} 

int basis[65], subset[65];

bool add(int mask, int pos) 
{
	// cout<<mask<<" "<<pos<<endl;
	int cur = (1ll<<pos);
	for (int i = 0; i < 60; i++) 
	{
		if ((mask>>i & 1ll) == 0) continue;
		if (basis[i] == -1) 
		{
			basis[i] = mask;
			subset[i] = cur;
			return 0;
		}
		mask ^= basis[i];
		cur ^= subset[i];
	}
	return 1;
}

int check(int mask) 
{
	int cur = 0;
	for (int i = 0; i < 60; i++) 
	{
		if ((mask>>i & 1) == 0) continue;
		if (basis[i] == -1) 
		{
			return -1;
		}
		mask ^= basis[i];
		cur ^= subset[i];
	}
	return cur;
}

void solve()
{
	int n, k;
	cin>>n>>k;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin>>a[i];
	for (int i = 0; i < n-1; i++) 
	{
		for (int j = 0; j < 60; j++) basis[j] = -1, subset[j] = 0;
		for (int j = 0; j < n; j++) 
		{
			if (j == i) add(a[i] ^ a[i+1], i);
			else if (j == i+1) continue;
			else add(a[j], j);
		}
		int ret = check(k);
		if (ret != -1) 
		{
			// cout<<i<<" "<<ret<<endl;
			cout<<"Yes";
			return;
			vector<int> ans;
			if (ret>>i & 1) 
			{
				ans.pb(i);
				if (i+2 < n) 
				{
					if (ret>>(i+2) & 1) 
					{
						// cout<<"Case 1"<<endl;
						ans.pb(i+1); 
						ans.pb(i); ans.pb(i);
						for (int j = i-1; j >= 0; j--) 
						{
							if (ret>>j & 1) 
							{
								if (i-j > 2) 
								{
									for (int l = j+1; l <= i-2; l += 2) ans.pb(l), ans.pb(l);
									if ((i-1) % 2 == (j+1) % 2) ans.pb(i-2), ans.pb(i-2);
									for (int l = j; l <= i-1; l++) ans.pb(l);
								} else if (i-j == 1)
								{
									ans.pb(j);
								} else 
								{
									ans.pb(i);
									ans.pb(i-1); ans.pb(i-1);
									ans.pb(i);
									ans.pb(i-2); ans.pb(i-1);
								}
							}
						}
						if (i) 
						{
							if (i == 1) 
							{
								ans.pb(i);
								ans.pb(i-1); ans.pb(i-1);
								ans.pb(i); ans.pb(i-1);
							} else 
							{
								for (int j = 0; j <= i-2; j += 2) ans.pb(j), ans.pb(j);
								if ((i-1) % 2 == 0) ans.pb(i-2); ans.pb(i-2);
								for (int j = i-1; j >= 0; j--) ans.pb(j);
							}
						}
						for (int j = i+2; j < n; j++) 
						{
							if (ret>>j & 1) 
							{
								for (int l = 1; l <= j-2; l += 2) ans.pb(l), ans.pb(l);
								if ((j-1) % 2 == 1) ans.pb(j-2), ans.pb(j-2);
								for (int l = j-1; l >= 0; l--) ans.pb(l);
							}
						}
					} else 
					{
						// cout<<"Case 3"<<endl;
						ans.pb(i+1); ans.pb(i+1);
						ans.pb(i); ans.pb(i+1);
						ret ^= (1ll<<(i+2));
						ans.pb(i); ans.pb(i);
						for (int j = i-1; j >= 0; j--) 
						{
							if (ret>>j & 1) 
							{
								if (i-j > 2) 
								{
									for (int l = j+1; l <= i-2; l += 2) ans.pb(l), ans.pb(l);
									if ((i-1) % 2 == (j+1) % 2) ans.pb(i-2), ans.pb(i-2);
									for (int l = j; l <= i-1; l++) ans.pb(l);
								} else if (i-j == 1)
								{
									ans.pb(j);
								} else 
								{
									ans.pb(i);
									ans.pb(i-1); ans.pb(i-1);
									ans.pb(i);
									ans.pb(i-2); ans.pb(i-1);
								}
							}
						}
						if (i) 
						{
							if (i == 1) 
							{
								ans.pb(i);
								ans.pb(i-1); ans.pb(i-1);
								ans.pb(i); ans.pb(i-1);
							} else 
							{
								for (int j = 0; j <= i-2; j += 2) ans.pb(j), ans.pb(j);
								if ((i-1) % 2 == 0) ans.pb(i-2); ans.pb(i-2);
								for (int j = i-1; j >= 0; j--) ans.pb(j);
							}
						}
						for (int j = i+2; j < n; j++) 
						{
							if (ret>>j & 1) 
							{
								for (int l = 1; l <= j-2; l += 2) ans.pb(l), ans.pb(l);
								if ((j-1) % 2 == 1) ans.pb(j-2), ans.pb(j-2);
								for (int l = j-1; l >= 0; l--) ans.pb(l);
							}
						}
					}
				} else 
				{
					if (ret>>(i-1) & 1) 
					{
						ans.pb(i-1); 
						ans.pb(i); ans.pb(i);
						for (int j = i-1; j >= 0; j--) 
						{
							if (ret>>j & 1) 
							{
								if (i-j > 2) 
								{
									for (int l = j+1; l <= i-2; l += 2) ans.pb(l), ans.pb(l);
									if ((i-1) % 2 == (j+1) % 2) ans.pb(i-2), ans.pb(i-2);
									for (int l = j; l <= i-1; l++) ans.pb(l);
								} else if (i-j == 1)
								{
									ans.pb(j);
								} else 
								{
									ans.pb(i);
									ans.pb(i-1); ans.pb(i-1);
									ans.pb(i);
									ans.pb(i-2); ans.pb(i-1);
								}
							}
						}
						if (i) 
						{
							if (i == 1) 
							{
								ans.pb(i);
								ans.pb(i-1); ans.pb(i-1);
								ans.pb(i); ans.pb(i-1);
							} else 
							{
								for (int j = 0; j <= i-2; j += 2) ans.pb(j), ans.pb(j);
								if ((i-1) % 2 == 0) ans.pb(i-2); ans.pb(i-2);
								for (int j = i-1; j >= 0; j--) ans.pb(j);
							}
						}
						for (int j = i+2; j < n; j++) 
						{
							if (ret>>j & 1) 
							{
								for (int l = 1; l <= j-2; l += 2) ans.pb(l), ans.pb(l);
								if ((j-1) % 2 == 1) ans.pb(j-2), ans.pb(j-2);
								for (int l = j-1; l >= 0; l--) ans.pb(l);
							}
						}
					} else 
					{
						// cout<<"Case 4"<<endl;
						ans.pb(i-1); ans.pb(i-1);
						ans.pb(i); ans.pb(i-1);
						ret ^= (1ll<<(i-1));
						ans.pb(i); ans.pb(i);
						for (int j = i-1; j >= 0; j--) 
						{
							if (ret>>j & 1) 
							{
								if (i-j > 2) 
								{
									for (int l = j+1; l <= i-2; l += 2) ans.pb(l), ans.pb(l);
									if ((i-1) % 2 == (j+1) % 2) ans.pb(i-2), ans.pb(i-2);
									for (int l = j; l <= i-1; l++) ans.pb(l);
								} else if (i-j == 1)
								{
									ans.pb(j);
								} else 
								{
									ans.pb(i);
									ans.pb(i-1); ans.pb(i-1);
									ans.pb(i);
									ans.pb(i-2); ans.pb(i-1);
								}
							}
						}
						if (i) 
						{
							if (i == 1) 
							{
								ans.pb(i);
								ans.pb(i-1); ans.pb(i-1);
								ans.pb(i); ans.pb(i-1);
							} else 
							{
								for (int j = 0; j <= i-2; j += 2) ans.pb(j), ans.pb(j);
								if ((i-1) % 2 == 0) ans.pb(i-2); ans.pb(i-2);
								for (int j = i-1; j >= 0; j--) ans.pb(j);
							}
						}
						for (int j = i+2; j < n; j++) 
						{
							if (ret>>j & 1) 
							{
								for (int l = 1; l <= j-2; l += 2) ans.pb(l), ans.pb(l);
								if ((j-1) % 2 == 1) ans.pb(j-2), ans.pb(j-2);
								for (int l = j-1; l >= 0; l--) ans.pb(l);
							}
						}
					}
				}
			} else 
			{
				// cout<<"Case 2"<<endl;
				ans.pb(i); ans.pb(i);
				for (int j = i-1; j >= 0; j--) 
				{
					if (ret>>j & 1) 
					{
						if (i-j > 2) 
						{
							for (int l = j+1; l <= i-2; l += 2) ans.pb(l), ans.pb(l);
							if ((i-1) % 2 == (j+1) % 2) ans.pb(i-2), ans.pb(i-2);
							for (int l = j; l <= i-1; l++) ans.pb(l);
						} else if (i-j == 1)
						{
							ans.pb(j);
						} else 
						{
							ans.pb(i);
							ans.pb(i-1); ans.pb(i-1);
							ans.pb(i);
							ans.pb(i-2); ans.pb(i-1);
						}
					}
				}
				if (i) 
				{
					if (i == 1) 
					{
						ans.pb(i);
						ans.pb(i-1); ans.pb(i-1);
						ans.pb(i); ans.pb(i-1);
					} else 
					{
						for (int j = 0; j <= i-2; j += 2) ans.pb(j), ans.pb(j);
						if ((i-1) % 2 == 0) ans.pb(i-2); ans.pb(i-2);
						for (int j = i-1; j >= 0; j--) ans.pb(j);
					}
				}
				for (int j = i+2; j < n; j++) 
				{
					if (ret>>j & 1) 
					{
						for (int l = 1; l <= j-2; l += 2) ans.pb(l), ans.pb(l);
						if ((j-1) % 2 == 1) ans.pb(j-2), ans.pb(j-2);
						for (int l = j-1; l >= 0; l--) ans.pb(l);
					}
				}
			}
			cout<<ans.size()<<endl;
			for (auto i : ans) cout<<i+1<<" ";
			// cout<<endl;
			// return;
			for (auto i : ans) 
			{
				int x = a[i] ^ a[i+1];
				a[i] = a[i+1] = x;
			}
			// for (int j = 0; j < n; j++) cout<<a[j]<<" ";
			// cout<<endl;
			assert(a[0] == k);
			assert(ans.size() <= 10000);
			return;
		}
	}
	cout<<"No";
}

/*
Go through the mistakes you usually make and revise your code, for god's sake...
*/

signed main()
{
	bruh
	//freopen("input.inp","r",stdin);
	//freopen("output.inp","w",stdout);
	int t = 1;
	cin>>t;	
	while (t--)
	{
		solve();
		cout<<"\n";
	}
} 

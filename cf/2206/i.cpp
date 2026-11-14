#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

const int lim = 2e5+10;
vector<int> divs[lim];

int32_t main() {_ 
	int n; cin >> n; 
	vector<int> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = n-2; i >= 0; --i) a[i] = min(a[i], a[i+1]);

    const int max = 200000;
	vector<int> dp(max+1); 
    dp[1] = 1;
    int s = 1;
    for (int i = 2; i <= 100000; ++i) {
        for (int j = 1; j * j <= i; ++j) {
            if (i % j) continue;
            dp[i] += dp[j];
            if (j * j != i) dp[i] += dp[i/j];
        }
        s += dp[i];
    }
    cout << fixed << setprecision(2);
    cout << s/1e8 << endl;
}

#include <bits/stdc++.h>
#define maxn (int)(1e5+51)
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define ll long long
#define pb push_back
#define ull unsigned long long
#define ii pair<int,int>
#define iii tuple<int,int,int>
#define inf 2000000001
#define mod 1000000007 //998244353
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

pair<ll,ll> point[10*maxn];
ll dp[4][20005];//currentrow, currentcolumn, lastrow, lastcolumn
int main(){_
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>point[i].first>>point[i].second;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<i-1;j++){
            dp[0][j] = dp[2][j] + abs(point[i-1].first-point[i].first);
            dp[1][j] = dp[3][j] + abs(point[i-1].second-point[i].second);
        }
        //dp[i][j] = dp[last selected x_i][last selected y_j]
        //optimization: only maintain last row and last column (i-1)th
        dp[0][i] = dp[1][i] = dp[0][i-1] = dp[1][i-1] = dp[2][i-1] = dp[3][i-1] = 1e18;
        if(i==1)dp[2][i-1]=dp[3][i-1]=0;
        for(int k=0;k<i;k++){
            ckmin(dp[0][i-1],dp[3][k] + abs(point[k].first-point[i].first));
            ckmin(dp[1][i-1],dp[2][k] + abs(point[k].second-point[i].second));
        }
        for(int k=0;k<=i-1;k++)dp[2][k]=dp[0][k],dp[3][k]=dp[1][k];
    }

    ll ans = 1e18;
    for(int i=0;i<n;i++)ckmin(ans,min(dp[0][i],dp[1][i]));
    cout<<ans<<endl;
}
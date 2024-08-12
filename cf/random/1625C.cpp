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
//dp[i][j] = min(dp[i-1][j],dp[i-1][j-1] + dp[i-1][j-1].lastnonremovedtrack*(pos[i]-pos[i-1]))
//first case: dp[i][j].f = dp[i-1][j].f 
//second case: dp[i][j].f = i 

ll pos[501],tempo[501];
ll dp[501][501];
int main(){_
    ll n,l,k;cin>>n>>l>>k;
    for(int i=0;i<n;i++){
        cin>>pos[i];
    }    
    for(int i=0;i<n;i++){
        cin>>tempo[i];
    }
    pos[n] = l;
    for(int i=0;i<=k;i++)
        for(int j=0;j<=n;j++)
            dp[i][j] = 1e18;
    for(int i=0;i<=k;i++){
        for(int j=0;j<=n;j++){
            if(!i&&!j)dp[i][j] = 0LL;
            else{
                for(int w=0;w<=i;w++){
                    if(j-w-1<0)break;
                    ckmin(dp[i][j],dp[i-w][j-w-1]+(pos[j]-pos[j-w-1])*tempo[j-w-1]);
                }
            }

        }
    }
    ll ans = 1e18;
    for(int i=0;i<=k;i++)ckmin(ans,dp[i][n]);
    cout<<ans<<endl;

}
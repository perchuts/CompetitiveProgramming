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

ll grid[1001][1001],dp[1001][10];
int n;
ll solve(int i,int mask){
    if(dp[i][mask])return dp[i][mask];
    if(i>n)return 0;
    ll tmp = 0;
    if((mask)==0){//going for three
        ckmax(tmp,grid[i-1][1]*grid[i][1]+grid[i-1][2]*grid[i][2]+grid[i-1][3]*grid[i][3]+solve(i+1,7));
    }
    if((mask&4)==0)ckmax(tmp,grid[i-1][1]*grid[i][1]+grid[i][2]*grid[i][3]+solve(i+1,7));
    if((mask&1)==0)ckmax(tmp,grid[i-1][3]*grid[i][3]+grid[i][2]*grid[i][1]+solve(i+1,7));
    //going for two
    if((mask&6)==0)ckmax(tmp,grid[i-1][1]*grid[i][1]+grid[i-1][2]*grid[i][2]+solve(i+1,6));
    if((mask&3)==0)ckmax(tmp,grid[i-1][3]*grid[i][3]+grid[i-1][2]*grid[i][2]+solve(i+1,3));
    if((mask&5)==0)ckmax(tmp,grid[i-1][1]*grid[i][1]+grid[i-1][3]*grid[i][3]+solve(i+1,5));
    ckmax(tmp,grid[i][1]*grid[i][2]+solve(i+1,6));
    ckmax(tmp,grid[i][2]*grid[i][3]+solve(i+1,3));
    //going for one
    if((mask&4)==0)ckmax(tmp,grid[i-1][1]*grid[i][1]+solve(i+1,4));
    if((mask&2)==0)ckmax(tmp,grid[i-1][2]*grid[i][2]+solve(i+1,2));
    if((mask&1)==0)ckmax(tmp,grid[i-1][3]*grid[i][3]+solve(i+1,1));
    //going for zero
    ckmax(tmp,solve(i+1,0));
    return dp[i][mask] = tmp;
}


int main(){_
    int i = 1;
    while(cin>>n&&n){
        for(int i=1;i<=3;i++)for(int j=1;j<=n;j++)cin>>grid[j][i];
        solve(1,7);
        printf("Case %d: %d\n",i++,dp[1][7]);
        for(int i=1;i<=n;i++)
            for(int j=0;j<10;j++)
                dp[i][j] = 0;
            
        
    }    
}
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

int grid[51][51], pr[51][51], dp[51][51][51][51];

int calcRect(int x1,int y1,int x2,int y2){
    return pr[x2][y2] - pr[x2][y1-1] - pr[x1-1][y2] + pr[x1-1][y1-1];
}

int main(){_
    int n,m;cin>>n>>m;

    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            cin>>grid[i][j];    

    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            pr[i][j] = pr[i-1][j] + pr[i][j-1] - pr[i-1][j-1] + grid[i][j];

    for(int x1=n;x1>=1;--x1){
        for(int y1=m;y1>=1;--y1){
            for(int x2=x1;x2<=n;++x2){
                for(int y2=y1;y2<=m;++y2){
                    if(x1==x2&&y1==y2)dp[x1][y1][x2][y2] = 0;
                    else{
                        dp[x1][y1][x2][y2] = calcRect(x1,y1,x2,y2);
                        int best = inf;
                        for(int k=x1;k<x2;++k)ckmin(best,dp[x1][y1][k][y2]+dp[k+1][y1][x2][y2]);
                        for(int k=y1;k<y2;++k)ckmin(best,dp[x1][y1][x2][k]+dp[x1][k+1][x2][y2]);
                        dp[x1][y1][x2][y2] += best;
                    }
                }
            }
        }
    }
    
    cout<<dp[1][1][n][m]<<endl;
}
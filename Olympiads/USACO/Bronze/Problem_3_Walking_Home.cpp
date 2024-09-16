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
#define inf (int)(2e9+1)
#define mod (int)(1e9+7)

using namespace std;
char grid[51][51];
int dp[51][51][4][2];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;cin>>t;
    while(t--){
        int n,k;cin>>n>>k;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                cin>>grid[i][j];
        dp[1][1][0][1]=dp[1][1][0][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(grid[i][j]=='H'||(i==1&&j==1))continue;
                for(int w=0;w<=k;w++){
                    dp[i][j][w][0]=dp[i-1][j][w][0];//continuar para baixo
                    dp[i][j][w][1]=dp[i][j-1][w][1];//continuar para a direita
                    if(w){
                        dp[i][j][w][0]+=(j!=1 ? dp[i-1][j][w-1][1]:0);
                        dp[i][j][w][1]+=(i!=1 ? dp[i][j-1][w-1][0]:0);
                    }
                }
            }
        }
        ll ans=0;
        for(int i=0;i<=k;i++)
            ans+=1LL*dp[n][n][i][0]+1LL*dp[n][n][i][1];
        cout<<ans<<endl;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                for(int w=0;w<=k;w++)
                    for(int u=0;u<2;u++)
                        dp[i][j][w][u]=0;
    }   
}
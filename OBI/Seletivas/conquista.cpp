/*
    Seletiva IOI 2018
    Conquista
    https://neps.academy/br/exercise/457
    por Gabriel Lucas
*/

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

int n,m,grid[3001][3001],dp[3001][3001];//dp[i][j] = melhor soma possivel ao chegar em (i,j)

int main(){_
    cin>>n>>m;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>grid[i][j];
        }
    }

    for(int j=1;j<=m;j++)dp[1][j] = dp[1][j-1] + grid[1][j];//unica maneira de prosseguir na primeira linha

    for(int i=2;i<=n;i++){
        
        dp[i][1] = dp[i-1][1]+grid[i][1]; 
        
        for(int j=2;j<=m;j++)//indo da esquerda para direita
            dp[i][j] = max(dp[i-1][j],dp[i][j-1]) + grid[i][j];
        
        
        int best = dp[i-1][m] + grid[i][m];

        for(int j=m-1;j>=1;j--){//indo da direita para esquerda
            best = max(best,dp[i-1][j]) + grid[i][j];
            ckmax(dp[i][j],best);
        }
    }
    
    cout<<dp[n][m]<<endl;
}
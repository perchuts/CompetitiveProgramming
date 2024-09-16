#include <bits/stdc++.h>

using namespace std;
int pode[30][30],ans;
int n, m;
vector<int>nao;
int dp[1<<23];

void solve(int p,int k,int choose){
    if(dp[choose])return;
    if(k>n){
        for(auto v:nao){
            if((choose&v)==v)return;
        }
        dp[choose] = 1;
        ans++;
        return;
    }
    solve(p,k+1,choose);
    if(pode[p][k]){
        choose|=(1<<k);
        solve(p,k+1,choose);
    }
}


int main(int argc, char const *argv[])
{
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            pode[i][j]=1;
        }
    }
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        int x=0;
        x|=(1<<a);
        x|=(1<<b);
        nao.push_back(x);
        pode[a][b]=0;
        pode[b][a]=0;
    }

    for(int i=1;i<=n;i++){

        solve(i,i+1,(1<<i));
    }
    cout<<ans;
    return 0;
}

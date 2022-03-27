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
 
//observation: model the problem to a graph
//count the number of hamiltonian paths.
int v[21];
int cnt2[21],cnt3[21];
ll dp[21][(1<<21)+10];
int count3(int x){
    int resp = 0;
    while(x){
        if(x%3==1)resp++;
        x/=3;
    }
    return resp;
}
int n;
int can[21][21];
bool mark[21][1<<22];
ll solve(int cur,int mask){
    if(mark[cur][mask])return dp[cur][mask];
    mark[cur][mask] = 1;
    if(mask==(1<<n)-1)return dp[cur][mask] = 1LL;
    for(int i=0;i<n;i++){
        if((mask&(1<<i))==0&&can[cur][i])dp[cur][mask]+=solve(i,mask|(1<<i));
    }
    return dp[cur][mask];
}
 
int main(){_
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>v[i];
        cnt2[i] = __builtin_popcount(v[i]);
        cnt3[i] = count3(v[i]);
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(i!=j&&(cnt2[i]==cnt2[j]||cnt3[i]==cnt3[j]))can[i][j] = 1;
    
    ll ans = 0;
    for(int i=0;i<n;i++)ans += solve(i,1<<i);
    cout<<ans<<endl;
}
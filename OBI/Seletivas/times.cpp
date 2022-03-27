/*
    Seletiva IOI 2019
    Times
    https://codeforces.com/group/2k70zKp2Ci/contest/263244/problem/B
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
#define inf (int)(2e9+1)
#define mod (int)(1e9+7)
 
using namespace std;
vector<int>g[maxn];
int visited[maxn];
 
int dfs(int x,int p){
    visited[x]=visited[p]^1;
    for(auto v:g[x]){
        if(v==p)continue;
        if(visited[v]==-1){
            if(dfs(v,x)==-1)return -1;
        }else if(visited[v]==visited[x])return -1;
    }
    return 1;
}
 
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        int u,v;
        cin>>u>>v;
        g[i].pb(u);
        g[i].pb(v);
    }   
    for(int i=1;i<=n;i++)   
        visited[i]=-1;
    
    int comp=0;
 
    for(int i=1;i<=n;i++){
        if(visited[i]==-1){
            if(dfs(i,0)==-1){
                cout<<0<<endl;
                return 0;
            }
            comp++;
        }
    }
    int ans=1;
    for(int i=1;i<=comp;i++)
        ans=(ans+ans)%mod;
    cout<<(n&1 ? 0 : ans)<<endl;
 
}

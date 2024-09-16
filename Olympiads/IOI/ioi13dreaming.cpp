#include <bits/stdc++.h>
#include "dreaming.h"
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
vector<ii>g[maxn];
 
int vis[maxn];
ii farthest;
 
void dfs(int u,int p,int d,bool type){//acha maior caminho
    vis[u] = type;
    if(ckmax(farthest.second,d))farthest.first = u;
    for(auto [d2,v]:g[u]){
        if(v!=p)dfs(v,u,d+d2,type);
    }
}
 
int dfs2(int u,int p,int target,int weight,int totweight){//acha centro
    if(u==target)return -1;
    for(auto [w,v]:g[u]){
        if(v==p)continue;
        int acc = dfs2(v,u,target,w,totweight);
        if(acc){
            acc = max(0,acc);
            if(ckmin(farthest.second,max(acc+w,totweight-acc-w)))farthest.first = u;
            return acc+w;
        }
    }
    return 0;
}
 
vector<int>centros;
int travelTime(int n,int m,int l,int a[],int b[],int t[]){
    for(int i=0;i<m;i++){
        g[a[i]].pb({t[i],b[i]});
        g[b[i]].pb({t[i],a[i]});
    }
    //achar centro de todas as componentes
    //unir centro das componentes
    //                           usar u,          usar v
    //ao unir, novo centro = min(max(d(v)+l,d(u)),max(d(u)+l,d(v)))
    //fixar uma arvore e unir todas as restantes a partir dela
    int resp = 0;
    for(int i=0;i<n;i++){
        if(!vis[i]){
            farthest = {i,0};
            dfs(i,i,0,0);
            farthest.second = 0;
            int u = farthest.first;
            dfs(u,u,0,1);
            int v = farthest.first;
            ckmax(resp,farthest.second);//maior caminho dentro da propria arvore
            dfs2(u,u,v,0,farthest.second);
            centros.pb(farthest.second);
        }
    }
    sort(all(centros),greater<int>());
    if(sz(centros)==1)return resp;
    else if(sz(centros)==2)return max(resp,l+centros[0]+centros[1]);
    else return max({resp,l+centros[0]+centros[1],2*l+centros[1]+centros[2]});
}
// int a[maxn],b[maxn],t[maxn];
// int main(){
//     int n,m,l;cin>>n>>m>>l;
//     for(int i=1;i<=m;i++)cin>>a[i-1]>>b[i-1]>>t[i-1];
//     cout<<travelTime(n,m,l,a,b,t)<<endl;
// }
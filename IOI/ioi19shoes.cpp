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
#include "shoes.h"
using namespace std;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
vector<int>pos[2*maxn];
int n,par[2*maxn],vis[2*maxn],bit[4*maxn];
 
void insert(int x,int d){
    x++;
    while(x<=n)bit[x]+=d,x+=x&(-x);
}
 
int query(int x){
    x++;
    int ans = 0;
    while(x)ans+=bit[x],x-=x&(-x);
    return ans;
}
 
ll count_swaps(vector<int>v){
    n = sz(v);
    for(int i=n-1;~i;--i){
        pos[v[i]+maxn].pb(i);
    }   
    ll ans = 0;
    for(int i=0;i<n;++i){
        if(vis[i])continue;
        int j = maxn - v[i];
        par[i] = pos[j].back();
        while(vis[par[i]]){
            pos[j].pop_back();par[i] = pos[j].back();
        }
        par[par[i]] = i,vis[par[i]] = vis[i] = 1;
        pos[j].pop_back();
        ans += 1ll*(abs(i-par[i]+1) + (v[min(i,par[i])]>0));
        insert(min(i,par[i]),1);
        insert(max(i,par[i]),-1);
    }
    for(int i=0;i<n;++i)vis[i] = 0;
    // cout<<ans<<endl;
    for(int i=0;i<n;++i){
        if(vis[i])continue;
        vis[i] = vis[par[i]] = 1;
        // cout<<i<<" "<<par[i]<<endl;
        // cout<<query(max(i,par[i])) - query(min(i,par[i])-1)<<endl;
        ans -= query(max(i,par[i])) - query(min(i,par[i])-1);
        // cout<<ans<<endl;
        insert(min(i,par[i]),-1);
        insert(max(i,par[i]),1);
    }
 
    return ans;
}

// int main(){
//     int n;cin>>n;
//     vector<int>v(2*n);
//     for(auto& x:v)cin>>x;
//     cout<<count_swaps(v)<<endl;
// }
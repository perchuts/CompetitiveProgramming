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
vector<ll>g[maxn];
set<ll>comp[maxn];
int vis[maxn];
int cur=0;
int n, m;
int where;
void dfs(ll u){
    vis[u]=1;
    if(u==n)where=cur;
    comp[cur].insert(u);
    for(auto v:g[u])
        if(!vis[v])
            dfs(v);
}
ll dist1[maxn],dist2[maxn];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;cin>>t;
    while(t--){
        cin>>n>>m;
        for(int i=0;i<m;i++){
            ll u,v;cin>>u>>v;
            g[u].pb(v);
            g[v].pb(u);
        }
        for(ll i=1;i<=n;i++){
            if(!vis[i]){
                cur++;
                dfs(i);
            }
        }
        if(where==1)
            cout<<0<<endl;
        else{
            fill(dist1+1,dist1+2+cur,100000LL*inf);
            fill(dist2+1,dist2+2+cur,100000LL*inf);
            for(int i=1;i<=cur;i++){
                for(auto x:comp[i]){
                    auto mn = comp[1].lower_bound(x);
                    ll curmn = 1LL*(x-*mn)*(x-*mn);
                    if(mn!=begin(comp[1])){
                        curmn = min(1LL*curmn,1LL*(x-*prev(mn))*(x-*prev(mn)));
                }
                    dist1[i] = min(dist1[i],curmn);
                    mn = comp[where].lower_bound(x);
                    curmn = 1LL*(x - *mn) * (x - *mn);
                    if (mn != begin(comp[where]))
                    {
                        curmn = min(curmn, 1LL*(x - *prev(mn)) * (x - *prev(mn)));
                    }
                    dist2[i] = min(dist2[i], curmn);
                }
            }
            ll ans = dist1[1]+dist2[1];
            for(int i=1;i<=cur;i++){
                ans = min(ans,dist1[i]+dist2[i]);
            }
            cout<<ans<<endl;
        }
        
        for(int i=1;i<=cur;i++){
            comp[i].clear();
        }
        for(int i=1;i<=n;i++){
            g[i].clear();
            vis[i]=0;
        }
        cur = 0,where=0;


    }   
}
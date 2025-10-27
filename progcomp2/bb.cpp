#include <bits/stdc++.h>
#define maxn (int)(2e5+51)
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
 
#pragma GCC optimize("Ofast")
using namespace std;
int k1,k2;
int subsz[maxn],vis[maxn],maxh;
vector<int>g[maxn];
ll ans, bit[maxn];
int dfs(int u,int p){
    subsz[u]=1;
    for(auto v:g[u]){
        if(!vis[v]&&v!=p)
            subsz[u]+=dfs(v,u);
    }
    return subsz[u];
}
 
int find_centroid(int u,int p,int n){
    for(auto v:g[u])
        if(!vis[v]&&v!=p&&subsz[v]>n/2)
            return find_centroid(v,u,n);
    return u;
}
 
void insert(int x,ll d){
    while(x<=k2){
        bit[x]+=d;
        x+=x&(-x);
    }
}
 
ll query(int x){
    ll ans=0LL;
    while(x){
        ans+=bit[x];
        x-=x&(-x);
    }
    return ans;
}
 
 
int qnts[maxn], curq[maxn], curh=0;
 
void solve(int u,int p,int lvl){
    if(lvl>k2)return;
    maxh = max(maxh,lvl);
	curh = max(curh,lvl);
    if(lvl<k1){
        ans+=query(k2-lvl)-query(k1-lvl-1), curq[lvl]++;
    }else{
       	ans+=query(k2-lvl)+1LL, curq[lvl]++;
    }
    for(auto v:g[u])
        if(!vis[v]&&v!=p)
            solve(v,u,lvl+1);    
}
 
 
void build(int u=1){
    int centroid = find_centroid(u,-1,dfs(u,-1));
    vis[centroid]=1,maxh=0;
    for(auto v:g[centroid]){
        if(!vis[v]){
			curh=0;
            solve(v,-1,1);
			for(int i = 1; i <= curh; ++i) insert(i, curq[i]), qnts[i] += curq[i], curq[i] = 0;
        }
    }
	for (int i = 1; i <= maxh; ++i) insert(i, -qnts[i]), qnts[i] = 0;
    for(auto v:g[centroid])
        if(!vis[v])
            build(v);
}
 
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	freopen("awesome.in", "r", stdin); //freopen("awesome.out", "w", stdout);
	int t; cin >> t;
	while (t--) {
		int n;cin>>n>>k1>>k2;
		int nk1 = n-1-k2, nk2 = n-1-k1;
		k1 = nk1, k2 = nk2;
		for(int i=1;i<n;i++){
			int a,b;cin>>a>>b;
			g[a].pb(b);   
			g[b].pb(a);   
		}
		build();
		cout<<ans<<endl;
		for (int i = 1; i <= n; ++i) g[i].clear(), bit[i] = qnts[i] = curq[i] = vis[i] = 0;
		ans = 0;
	}
    
}

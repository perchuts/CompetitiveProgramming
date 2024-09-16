#include <bits/stdc++.h>
#define maxn (int)(1e5+51)
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define ll long long
#define ull unsigned long long
#define ii pair<int,int>
#define iii tuple<int,int,int>
#define inf (int)(2e9+1)
#define mod (int)(1e9+7)
#define LOG 17
using namespace std;
int n,visited[50010],level[50010],maxdist=0,root=1,parent[50010][17];
vector<int>adj[50010];
vector<int>leaf,raizes;

void bfs(int x){
    for(int i=1;i<=n;i++){
        visited[i]=0;level[i]=0;
    }
    queue<int>q;
    q.push(x);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        visited[u]=1;
        for(auto v:adj[u]){
            if(!visited[v]){
                level[v]=level[u]+1;
                if(level[v]>maxdist){
                    maxdist=level[v];
                    root=v;
                }
                q.push(v);
            }
        }
    }
}
void dfs(int x,int l,int p){
    parent[x][0]=p;
    level[x]=l;
    maxdist=max(maxdist,l);
    for (int j = 1; j < LOG; j++)
        if (parent[x][j - 1])
            parent[x][j] = parent[parent[x][j - 1]][j - 1];
    for (auto v : adj[x]){
        if (v != p){
            dfs(v,l+1,x);
        }
    }
}

void dfs2(int x,int p){
    int flag=1;
    for(auto v:adj[x]){
        if(v!=p){
            flag=0;
            dfs2(v,x);
        }
    }
    if(flag==1){
        if(level[x]==maxdist){
            raizes.push_back(x);
        }else{
            leaf.push_back(x);
        }
    }
}

int lca(int u,int v){
    int U = u, V = v;
    if (level[u] > level[v])
        swap(u, v);
    for (int i = LOG - 1; i >= 0; i--)
        if (parent[v][i] != 0 and level[parent[v][i]] >= level[u])
            v = parent[v][i];
    if (v == u)
        return level[U] + level[V] - 2 * level[v];
    for (int i = LOG - 1; i >= 0; i--)
        if (parent[v][i] != parent[u][i])
            v = parent[v][i], u = parent[u][i];
    int _lca = parent[v][0];
    return level[U] + level[V] - 2 * level[_lca];
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin>>n;
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    bfs(1);
    maxdist=0;
    dfs(root,0,0);
    dfs2(root,0);
    long long ans=1LL*raizes.size();
    if(leaf.size()==0){
        ans = raizes.size()*raizes.size()-1/2;
    }else{
        for (auto u : raizes)
        {
            for (auto v : leaf)
            {
                if (lca(u, v) == maxdist)
                {
                    ans++;
                }
            }
        }
    }
    
    cout<<maxdist+1<<endl<<ans<<endl;
    
}
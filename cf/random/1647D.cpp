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
 
map<string,int>mp;
int par[maxn];
vector<int>g[maxn];
int vis[maxn], mark[maxn][2][2], dp[maxn][2][2];
 
int countnodes(int u){
    vis[u] = 1;
    int resp = 1;
    for(auto v:g[u]){
        resp += countnodes(v);
    }
    return resp;
}

int dfs(int u,bool mode,bool type){
    if(mark[u][mode][type])return dp[u][mode][type];
    mark[u][mode][type] = 1;
    if(mode)dp[u][mode][type] = 1;
    else{
        dp[u][mode][type] = dfs(u,1,type) - 1;
    }
    int best = 0;
    for(auto v:g[u]){
        if(mode){
            dp[u][mode][type] += dfs(v,0,type);
        }else{
            ckmax(best,dfs(v,1,type) - dfs(v,0,type));
        }
    }
    dp[u][mode][type] += best;
    return dp[u][mode][type];
}

void removeAdj(int x){
    for(int i=0;i<sz(g[par[x]]);++i){
        if(g[par[x]][i]==x){
            g[par[x]].erase(g[par[x]].begin()+i);
            break;
        }
    }
}

int main(){_
    int n;cin>>n;
    if(n&1){
        cout<<-1<<endl;
        return 0;
    }
    int q = 0, resp = 0;
    for(int i=1;i<=n;++i){
        string a,b;cin>>a>>b;
        if(mp.find(a)==mp.end())mp[a]=++q;
        if(mp.find(b)==mp.end())mp[b]=++q;
        int u = mp[a], v = mp[b];
        par[u] = v;
        g[v].pb(u);
    }   
    for(int i=1;i<=n;++i){
        if(!vis[i]){
            int cur = i;
            while(!vis[cur])vis[cur] = 1, cur = par[cur];
            int start = cur, cnt = 1, ans = 0, nodes = 0, last = cur;
            cur = par[cur];
            while(cur!=start)last = cur,cur = par[cur], ++cnt;
            removeAdj(start);
            nodes = countnodes(start);
            if(cnt==1){
                ans = dfs(start,0,0);
            }else if(cnt==2){
                removeAdj(par[start]);
                for(auto v:g[start])ans += dfs(v,0,0);
                for(auto v:g[par[start]])ans += dfs(v,0,0);
                int ans2 = dfs(start,0,1) + dfs(par[start],0,1);
                ans += 2;
                ckmax(ans,ans2);
            }else{
                ans = dfs(start,0,0);//start is shot
                int ans2 = 1;
                removeAdj(par[start]);
                removeAdj(last);
                for(auto v:g[start])ans2 += dfs(v,0,1);
                for(auto v:g[par[start]])ans2 += dfs(v,0,1);
                ans2 += dfs(last,0,1);
                ckmax(ans,ans2);
            }   
            resp += nodes - ans;
        }
    }   
    cout<<resp<<endl;
}
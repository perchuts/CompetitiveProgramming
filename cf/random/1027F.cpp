#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;
 
const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 2e6+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
ii tempos[maxn], v[maxn], qnt[maxn];
bool ok[maxn], pode[maxn];
vector<int>cnv, g[maxn];
int n, par[maxn], lvl[maxn];
 
bool dfs(int u,int take,int x){
    if(u>=x||pode[u]==0){
        // printf("erro: x=%d, u=%d, ok2[u]=%d\n",x,u,pode[u]);
        return 0;
    }
    // printf("visitando o tempo de indice %d e fazendo a prova %d\n",u,take);
    pode[u] = 0, ok[take] = 1;
    for(auto y:g[u]){
        if(ok[y])continue;
        int outro = (v[y].first==u?v[y].second:v[y].first);
        if(!dfs(outro,y,x))return 0;
    }
    return 1;
}
 
int findp(int x){return par[x] = (par[x]==x?x:findp(par[x]));}
 
void merge(int x,int y){
    x = findp(x), y = findp(y);
    if(x==y){
        qnt[x].second++;
        return;
    }
    if(lvl[x]<lvl[y])swap(x,y);
    par[y] = x;
    if(lvl[x]==lvl[y])lvl[x]++;
    qnt[x].first += qnt[y].first, qnt[x].second += qnt[y].second+1;
}
 
bool possible(int x){
    for(int i=0;i<=max(n,sz(cnv));++i)ok[i]=lvl[i]=0,par[i]=i,qnt[i]={1,0},pode[i]=1;    
 
    int idx = upper_bound(all(cnv), x) - begin(cnv);
 
    for(int i=1;i<=n;++i){//tira as provas com < 2 opcoes
        if(ok[i])continue;
        if(v[i].first>=idx)return 0;
        else if(v[i].second>=idx){
            if(!dfs(v[i].first,i,idx))return 0;
        }
    }
 
    for(int i=1;i<=n;++i)if(!ok[i])merge(v[i].first,v[i].second);
        
    for(int i=0;i<sz(cnv);++i){
        if(!pode[i])continue;
        int p = findp(i);
        if(qnt[p].first<qnt[p].second)return 0;
    }
 
    return 1;
}
 
int main(){_
    cin>>n;
 
    for(int i=1;i<=n;++i){
        cin>>tempos[i].first>>tempos[i].second;
        cnv.pb(tempos[i].first), cnv.pb(tempos[i].second);
    }    
 
    sort(all(cnv)), cnv.erase(unique(all(cnv)), end(cnv));
 
    for(int i=1;i<=n;++i){
        v[i].first = lower_bound(all(cnv), tempos[i].first) - begin(cnv);
        v[i].second = lower_bound(all(cnv), tempos[i].second) - begin(cnv);
        g[v[i].first].pb(i), g[v[i].second].pb(i);
    }
 
    int l = 1, r = 1e9, ans = -1;
 
    while(l<=r){
        int md = l + (r-l+1)/2;
        if(possible(md))r = md-1, ans = md;
        else l = md+1;
    }
    
    cout<<ans<<endl;
}
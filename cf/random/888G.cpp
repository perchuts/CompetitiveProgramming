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
const int maxn = 2e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
int v[maxn], par[maxn], lvl[maxn], n;
bool vis[maxn];
ll ans;
vector<int>cm[maxn];
 
int findp(int x){return par[x] = (x==par[x]?x:findp(par[x]));}
 
bool merge(int x,int y){
    x = findp(x), y = findp(y);
    if(x==y)return 0;
    if(lvl[x]<lvl[y])swap(x,y);
    par[y] = x;
    lvl[x]+=lvl[y];
    for(auto z:cm[y])cm[x].pb(z);
    return 1;
}
 
int trie[maxn*20][2], cnt[maxn*20], t=1, who[maxn*20];
 
void upd(int idx,int d){
    int x = v[idx];
    int cur = 1;
    for(int j=29;~j;--j){
        int me = (x>>j)&1;
        if(trie[cur][me]==0)trie[cur][me] = ++t;
        cnt[trie[cur][me]] += d, cur = trie[cur][me];
        if(d==1)who[cur] = idx;
    } 
}
 
ii query(int idx){
    int x = v[idx], resp = 0;
    int cur = 1;
    for(int j=29;~j;--j){
        int need = ((x>>j)&1);
        if(cnt[trie[cur][need]]==0)need^=1;
        resp += (need<<j), cur = trie[cur][need];
    }
    return make_pair(x^resp,who[cur]);
}
 
ii processa(int x){
    int m = sz(cm[x]);
    for(auto y:cm[x])upd(y,-1);
    int best = inf, idx1 = -1, idx2 = -1;
    for(auto y:cm[x]){
        ii cur = query(y);
        if(ckmin(best,cur.first))idx1 = cur.second, idx2 = y;
    }
    for(auto y:cm[x])upd(y,1);
    return {idx1,idx2};
}
 
int main(){_
    cin>>n;
    vector<int>unicos(n);
    for(auto& x:unicos)cin>>x;
    sort(all(unicos)), unicos.erase(unique(all(unicos)),end(unicos));
    n = sz(unicos);
    for(int i=1;i<=n;++i){
        v[i] = unicos[i-1], upd(i,1), par[i] = i, cm[i].pb(i);
    }
    int componentes = n;
    while(componentes!=1){
        vector<pair<int,ii>>edges;
        for(int i=1;i<=n;++i){
            if(findp(i)!=i)continue;
            ii best = processa(i);
            edges.pb({v[best.first]^v[best.second],best});
        }
        sort(all(edges));
        for(auto [x,p]:edges){
            if(merge(p.first,p.second))ans += x, --componentes;
        }
    }
    cout<<ans<<endl;
}
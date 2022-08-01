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
const int maxn = 4e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
struct interval{
    int st, en, qnt;
};
 
struct delta{
    ll delta;
    int idx;
};
 
ll resp[maxn], pr[maxn];
 
int par[maxn], lvl[maxn];
 
int findp(int x){return par[x] = (par[x]==x?x:findp(par[x]));}
 
int merge(int x,int y){
    x = findp(x), y = findp(y);
    if(x==y)return -1;
    if(lvl[x]<lvl[y])swap(x,y);
    par[y] = x;
    if(lvl[x]==lvl[y])lvl[x]++;
    return x; 
}
 
bool sortt(delta x,delta y){
    // if(x.delta==y.delta)return x.idx>y.idx;
    return x.delta<y.delta;
}
 
int main(){_
    int n, m, q;cin>>n>>m>>q;    
    //need to compress coordinates first..
    vector<pair<ll,int>>v1(n), v2(m), cmp;
    for(auto& x:v1)cin>>x.first, x.second = 1;//pego
    for(auto& x:v2)cin>>x.first, x.second = 0;//nao pego
 
    cmp = v1;for(auto x:v2)cmp.pb(x);
    sort(all(cmp));
    vector<interval>intr;
 
    int i=0;
    while(i<n+m){
        ll x = cmp[i].first;int qnt = 0;
        int st = i;
        while(i<n+m&&cmp[i].first==x)qnt += cmp[i++].second;
        interval cur = {st,i-1,qnt};
        intr.pb(cur);
    }
 
    for(int i=0;i<n+m;++i)pr[i+1] = pr[i] + cmp[i].first;
    
    vector<ii>queries;
    
    for(int i=0;i<q;++i){
        int x;cin>>x;
        queries.pb({x,i});
    }
    
    sort(all(queries));
    
    ll ans = 0;
    for(auto x:v1)ans += x.first;
 
    vector<delta>exl;
 
    for(int i=0;i<sz(intr)-1;++i){
        exl.pb({cmp[intr[i].en+1].first-cmp[intr[i].en].first,i});
    }
 
    for(int i=0;i<sz(intr);++i)par[i] = i;
 
    sort(all(exl), sortt);
    int current = 0;
 
    for(auto [x,idx]:queries){
        while(current<sz(exl)&&exl[current].delta<=x){
            int me = findp(exl[current].idx), prox = findp(exl[current].idx+1), father = merge(me,prox);
            int inicio = intr[prox].en-intr[prox].qnt, posso = max(0,inicio-intr[prox].st+1);
            int l = intr[me].en-intr[me].qnt+1, r = min(l+posso-1,intr[me].en);
            ans -= pr[r+1] - pr[l];
            ans += pr[inicio+1] - pr[inicio-(r-l)];
            assert(father!=-1);
            intr[father].en = max(intr[me].en,intr[prox].en),
            intr[father].st = min(intr[me].st,intr[prox].st),
            intr[father].qnt = intr[me].qnt + intr[prox].qnt;
            ++current;
        }
        resp[idx] = ans;
    }
 
    for(int i=0;i<q;++i)cout<<resp[i]<<endl;
}
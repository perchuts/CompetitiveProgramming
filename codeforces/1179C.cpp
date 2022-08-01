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
const int maxn = 1e6+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
    
int where[maxn][2], v[maxn];
ii seg[4*maxn];
 
void build(int i,int l,int r){
    if(l==r){
        seg[i] = {v[l],v[l]};
        return;
    }
    int md = (l+r)/2;
    build(2*i,l,md), build(2*i+1,md+1,r);
    seg[i].first = seg[2*i].first+seg[2*i+1].first;
    seg[i].second = max(seg[2*i].second+seg[2*i+1].first,seg[2*i+1].second);
}
 
void update(int i,int l,int r,int x,int d){
    if(l>x||r<x)return;
    if(l==r){
        seg[i].first += d;
        seg[i].second = seg[i].first;
        return;
    }
    int md = (l+r)/2;
    update(2*i,l,md,x,d), update(2*i+1,md+1,r,x,d);
    seg[i].first = seg[2*i].first+seg[2*i+1].first;
    seg[i].second = max(seg[2*i].second+seg[2*i+1].first,seg[2*i+1].second);
}
 
int query(int i,int l,int r,int inc){
    if(l==r){
        if(inc+seg[i].first>0)return l;
        return -1;
    }
    int md = (l+r)/2;
    if(seg[2*i+1].second+inc>0)return query(2*i+1,md+1,r,inc);
    return query(2*i,l,md,inc+seg[2*i+1].first);
}
 
int main(){_
    int n,m;cin>>n>>m;
 
    for(int i=1;i<=n;++i){
        int x;cin>>x;
        where[i][0] = x, v[x]++;
    }
 
    for(int i=1;i<=m;++i){
        int x;cin>>x;
        where[i][1] = x, v[x]--;
    }
 
    build(1,1,1e6);
 
    int q;cin>>q;
    while(q--){
        int op, idx, x;cin>>op>>idx>>x;
        --op;
        int d = (op==0?1:-1);
        update(1,1,1e6,where[idx][op],-d);
        where[idx][op] = x;
        update(1,1,1e6,where[idx][op],d);
        cout<<query(1,1,1e6,0)<<endl;
    }
}
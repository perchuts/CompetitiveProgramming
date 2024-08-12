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
const int maxn = 5e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
int v[maxn], ans[maxn];
 
ii seg[4*maxn];
 
vector<int>pos[maxn];
 
vector<tuple<int,int,int,int>>intr[maxn];
 
void update(int i,int l,int r,int x,ii d){
    if(l>x||r<x)return;
    if(l==r){
        seg[i] = d;
        return;
    }
    int md = (l+r)/2;
    update(2*i,l,md,x,d), update(2*i+1,md+1,r,x,d);
    seg[i] = max(seg[2*i],seg[2*i+1]);
}
 
ii query(int i,int l,int r,int x,int y){
    if(l>y||r<x)return {0,0};
    if(x<=l&&r<=y)return seg[i];
    int md = (l+r)/2;
    return max(query(2*i,l,md,x,y), query(2*i+1,md+1,r,x,y));
}
 
int main(){_
    int n;cin>>n;
 
    for(int i=1;i<=n;++i)pos[i].pb(0);
    
    for(int i=1;i<=n;++i){
        cin>>v[i];    
        pos[v[i]].pb(i);
    }
 
    for(int i=1;i<=n;++i)pos[i].pb(n+1);
 
    for(int i=1;i<=5e5;++i){
        for(int j=1;j<sz(pos[i])-1;++j){
            intr[pos[i][j-1]+1].pb({pos[i][j],pos[i][j+1]-1,i,1});
            intr[pos[i][j+1]].pb({pos[i][j],pos[i][j+1]-1,i,0});
        }   
    }
 
    vector<iii>qry;
 
    int q;cin>>q;
 
    for(int i=0;i<q;++i){
        int l,r;cin>>l>>r;
        qry.pb({l,r,i});
    }
 
    sort(all(qry));
 
    int pt = 0;
 
    for(auto [l,r,idx]:qry){
        while(pt!=l){
            ++pt;
            // cout<<"tempo: "<<pt<<endl;
            for(auto [pos,fim,val,tipo] : intr[pt]){
                if(tipo){
                    update(1,1,n,pos,{fim,val});
                    // cout<<"+ "<<pos<<" "<<fim<<" "<<val<<endl;
                }else{
                    update(1,1,n,pos,{0,0});  
                    // cout<<"- "<<pos<<" "<<fim<<" "<<val<<endl;
                } 
            }
        }
        ii resp = query(1,1,n,l,r);
        ans[idx] = resp.first<r?0:resp.second;
    }
 
    for(int i=0;i<q;++i)cout<<ans[i]<<endl;
 
}
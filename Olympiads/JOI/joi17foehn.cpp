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
 
ll v[2*maxn],seg[8*maxn],lazy[8*maxn];
int n,q;
ll s,t,sum;
 
void push(int i,int l,int r){
    if(l!=r)lazy[2*i]+=lazy[i],lazy[2*i+1]+=lazy[i];
    seg[i]+=lazy[i]*(1LL*(r-l+1));
    lazy[i] = 0;
}
 
void update(int i,int l,int r,int x,int y,ll d){
    push(i,l,r);
    if(l>y||r<x)return;
    if(x<=l&&r<=y){
        lazy[i]+=d;
        push(i,l,r);
        return;
    }
    int md = (l+r)/2;
    update(2*i,l,md,x,y,d);
    update(2*i+1,md+1,r,x,y,d);
    seg[i] = seg[2*i]+seg[2*i+1];
}
 
ll query(int i,int l,int r,int x){
    push(i,l,r);
    if(l>x||r<x)return 0;
    if(l==r)return seg[i];
    int md = (l+r)/2;
    return query(2*i,l,md,x) + query(2*i+1,md+1,r,x);
}
 
void updatesum(int i){
    ll l = query(1,1,n,i-1), r = query(1,1,n,i);
    sum-=v[i];
    if(l<=r)v[i] = (l-r)*(s);
    else v[i] = (l-r)*(t);
    sum+=v[i];   
 
}
 
int main(){_
    cin>>n>>q>>s>>t;
    ll last = 0;
    n++;
    for(int i=1;i<=n;i++){
        ll x;cin>>x;
        update(1,1,n,i,i,x);
        if(i!=1)updatesum(i);
        last = x;
        // cout<<sum<<" ";
    }
    // cout<<endl; 0 18 7
    while(q--){
        int l,r;
        ll x;cin>>l>>r>>x;l++,r++;
        update(1,1,n,l,r,x);
        if(r!=n)updatesum(r+1);
        updatesum(l);
        cout<<sum<<endl;
    }
}
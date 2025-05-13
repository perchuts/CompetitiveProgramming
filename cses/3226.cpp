#include <bits/stdc++.h>
#define maxn (int)(3e5+51)
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
//best: left + right, only left, only right, nothing.
//should store prefix, suffix, sum and best subsegment.
//prefix = left prefix or left segment + right prefix
//suffix = exactly like prefix but reversed 
struct node{
    ll pref,suf,best,sum; 
};
node seg[4*maxn],no;

ll v[maxn];

node merge(node a,node b){
    node ans;
    ans.sum = a.sum + b.sum;
    ans.pref = max(a.pref,a.sum+b.pref);
    ans.suf = max(b.suf,b.sum+a.suf);
    ans.best = max({a.best,b.best,a.suf+b.pref});
    return ans;
}


void build(int i,int l,int r){
    if(l==r){
        seg[i].pref = seg[i].suf = seg[i].sum = v[l];
        seg[i].best = max(0LL,v[l]);
        return;
    }
    int md = (l+r)/2;
    build(2*i,l,md);
    build(2*i+1,md+1,r);
    seg[i] = merge(seg[2*i],seg[2*i+1]);
}

void update(int i,int l,int r,int x,ll d){
    if(l>x||r<x)return;
    if(r==l){
        seg[i].pref = seg[i].suf = seg[i].sum = d;
        seg[i].best = max(0LL,d);
        return;        
    }
    int md = (l+r)/2;
    update(2*i,l,md,x,d);
    update(2*i+1,md+1,r,x,d);
    seg[i] = merge(seg[2*i],seg[2*i+1]);
}

node query(int i, int l, int r, int x, int y) {
    if (x <= l and r <= y) return seg[i];
    int md = (l+r)/2;
    if (y <= md) return query(2*i, l, md, x, y);
    if (md < x) return query(2*i+1, md+1, r, x, y);
    return merge(query(2*i, l, md, x, y), query(2*i+1, md+1, r, x, y));
};

int main(){_
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>v[i];    
    build(1,1,n);
    while(m--){
        int l, r; cin >> l >> r;
        cout << query(1, 1, n, l, r).best << endl;
    }
}

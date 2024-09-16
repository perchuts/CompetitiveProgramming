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

ll seg[4*maxn],lazy[4*maxn];

void update(int i,ll l,ll r,int p,int q,ll v){
    if(lazy[i]!=0){
        seg[i]+=lazy[i]*(r-l+1LL);
        if(l!=r){
            lazy[2*i]+=lazy[i];
            lazy[2*i+1]+=lazy[i];
        }
        lazy[i] = 0;
    }
    if(l>q||r<p)return;
    if(p<=l&&r<=q){
        seg[i]+=v*(r-l+1LL);
        if(l!=r){
            lazy[2*i]+=v;
            lazy[2*i+1]+=v;
        }
        return;
    }
    int md = (l+r)/2;
    update(2*i,l,md,p,q,v);
    update(2*i+1,md+1,r,p,q,v);
    seg[i] = seg[2*i]+seg[2*i+1];
}

ll query(int i,ll l,ll r,int p,int q){
    if(lazy[i]!=0){
        seg[i]+=lazy[i]*(r-l+1LL);
        if(l!=r){
            lazy[2*i]+=lazy[i];
            lazy[2*i+1]+=lazy[i];
        }
        lazy[i] = 0;
    }
    if(l>q||r<p)return 0;
    if(p<=l&&r<=q){
        return seg[i];
    }
    int md = (l+r)/2;
    return query(2*i,l,md,p,q)+query(2*i+1,md+1,r,p,q);
}

int main(){_
    int t;cin>>t;
    while(t--){
        int n,c;cin>>n>>c;
        while(c--){
            int o;cin>>o;
            if(o){
                ll l,r;cin>>l>>r;
                cout<<query(1,1,n,min(l,r),max(l,r))<<endl;
            }else{
                ll l,r;cin>>l>>r;
                ll v;cin>>v;
                update(1,1,n,min(l,r),max(l,r),v);
            }
        }
        for(int i=1;i<=4*n;i++)seg[i] = lazy[i] = 0;
    }   
}

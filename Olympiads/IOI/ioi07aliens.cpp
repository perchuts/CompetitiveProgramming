#include <bits/stdc++.h>
#define maxn (int)(1e5+51)
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
int q = 0;
void tle(){
    while(true){
        // cout<<"a"<<endl;
    }
}
ll n,xi,yi;
bool query(ll x,ll y){
    if(x>n||y>n||x<1||y<1)return 0;
    if(q==299)tle();
    q++;
    cout<<"examine "<<x<<" "<<y<<endl;
    string s;cin>>s;
    return s=="true";
}
 
ii resolve(ll x,ll y,ll m){
    queue<ii>q;
    q.push({x,y});
    ll a[12] = {0,0,2,-2,1,-1,-1,1,2,-2,-2,2};
    ll b[12] = {2,-2,0,0,1,-1,1,-1,2,-2,2,-2};
    while(true){
        int ok = 0;
        auto [x1,y1] = q.front();q.pop();
        for(int i=0;i<12;i++){
            ll x2 = x1+m*1LL*a[i], y2 = y1+m*1LL*b[i];
            if(query(x2,y2))q.push({x2,y2}),ok++;
        }
        if(ok==12)return {x1,y1};
    }
    return {0,0};
}
 
int main(){_
    cin>>n>>xi>>yi;
    //find rightmost
    ll rb = xi+1LL,it=0,lb = xi;
    while(query(rb,yi))lb = rb,rb+=(1LL<<it),it++;
    ll rightmost = lb;
    while(lb<=rb){
        ll md = lb + (rb - lb +1LL)/2;
        if(query(md,yi)){
            lb = md+1LL;rightmost = md;
        }else{
            rb = md-1LL;
        }
    }
    //find leftmost
    rb = xi,lb = xi-1LL,it = 0;
    while(query(lb,yi))rb = lb,lb-=(1LL<<it),it++;
    ll leftmost = rb;
    lb = max(1LL,lb);
    while(lb<=rb){
        ll md = lb + (rb - lb +1LL)/2;
        if(query(md,yi)){
            rb = md-1LL;leftmost = md;
        }else{
            lb = md+1LL;
        }
    }
    //find topmost
    rb = yi+1LL,lb = yi,it = 0;
    while(query(xi,rb))lb = rb,rb+=(1LL<<it),it++;
    ll topmost = lb;
    while(lb<=rb){
        ll md = lb + (rb - lb +1LL)/2;
        if(query(xi,md)){
            lb = md+1LL;topmost = md;
        }else{
            rb = md-1LL;
        }
    }
    ll m = rightmost - leftmost + 1LL, xc = leftmost + m/2, yc = topmost - m/2;//(xc,yc) is the center
    ii ans = resolve(xc,yc,m);
    cout<<"solution "<<ans.first<<" "<<ans.second<<endl;
}
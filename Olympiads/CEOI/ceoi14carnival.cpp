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
 
int color[200];
vector<int>v;
 
bool inside(int x,int l,int r){
    cout<<r-l+2<<" ";
    for(int i=l;i<=r;i++)cout<<v[i]<<" ";
    cout<<x<<endl;
    int cnt;cin>>cnt;
    return cnt<r-l+2;
}
 
 
int main(){_
    int n;cin>>n;
    int last = inf,c=0;
    v.pb(0);
    for(int i=n;i>=1;i--){
        if(last==1){
            v.pb(i);
            break;
        }
        cout<<i<<" ";
        for(int j=1;j<=i;j++){
            cout<<j<<" ";
        }
        cout<<endl;
        int x;cin>>x;ckmax(c,x);
        if(x!=last&&last!=inf)v.pb(i+1);
        last = x;
    }
    
    for(int i=1;i<=c;i++)color[v[i]] = i;
 
    for(int i=1;i<=n;i++){
        if(color[i])continue;
        int l = 1, r = c;
        while(l<r){
            int md = (l+r)/2;
            if(inside(i,l,md)){
                r = md;
            }else l = md+1;
        }
        color[i] = l;
    }
    cout<<"0 ";
    for(int i=1;i<=n;i++)cout<<color[i]<<" ";
    cout<<endl;
}
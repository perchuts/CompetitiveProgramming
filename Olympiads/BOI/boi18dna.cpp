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
//iterate over possible endpoints.
//first, identify first endpoint which every letter is satisfied.
//then,
 
multiset<int>mn;
queue<int>q[2*maxn];
int v[2*maxn],need[2*maxn];
 
int main(){_
    int n,k,r;cin>>n>>k>>r;
    for(int i=1;i<=n;i++){
        cin>>v[i];    
    }
    for(int i=1;i<=r;i++){
        int x,qnt;cin>>x>>qnt;
        need[x] = qnt;
    }
    int ok = 0,ans = inf;
    for(int i=1;i<=n;i++){
        if(need[v[i]]){
            q[v[i]].push(i);
            if(sz(q[v[i]])==need[v[i]]){
                mn.insert(q[v[i]].front());
                ok++;
            }
            if(sz(q[v[i]])>need[v[i]]){
                mn.erase(mn.find(q[v[i]].front()));
                q[v[i]].pop();
                mn.insert(q[v[i]].front());
            }
        }
        if(ok==r)ckmin(ans,i-*begin(mn)+1);
    }
    if(ans==inf)cout<<"impossible"<<endl;
    else cout<<ans<<endl;
}
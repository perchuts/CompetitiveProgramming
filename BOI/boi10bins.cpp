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
 
int m,n,v[maxn];
multiset<int>l,r;
 
bool check(){
    auto itl = begin(l),itr = begin(r);
    while(itl!=end(l)){
        if(*itl>=*itr)return false;
        itl = next(itl), itr = next(itr);
    }
    return true;
}
 
 
int main(){_
    cin>>m>>n;
    for(int i=1;i<=n;i++)cin>>v[i];
    // for(int i=1;i<=n/2;i++){
    //     l.insert(v[i]);r.insert(v[i+n/2]);
    // }
    // for(int i=n/2;i>=1;i--){
    //     if(check()){
    //         cout<<i<<endl;
    //         return 0;
    //     }
    //     l.erase(l.find(v[i]));
    //     r.insert(v[i]);
    //     r.erase(r.find(v[2*i]));
    //     r.erase(r.find(v[2*i-1]));
    // }
    int ans = 0;
    for(int i=1;i<=n/2;i++){
        if(i!=1){
            r.erase(r.find(v[i]));
            r.insert(v[2*i-1]);
        }
        r.insert(v[2*i]);
        l.insert(v[i]);
        if(check())ans = i;
    }
    cout<<ans<<endl;
 
}
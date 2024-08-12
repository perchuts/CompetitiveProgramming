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
// (a + x)|(b+y) = (b+y)+z
// minimizar x+y+z
// x+y+z 
// 101 010
// 110
// 1000
// 0101
void solve(){
    int a,b;cin>>a>>b;
    int ans = inf;
    int add=0,x=0;
    vector<int>bi;
    bi.pb(b);
    while((1<<x)<=a){
        if(((1<<x)&a)&&((1<<x)&b)==0){
            add+=(1<<x);
            bi.pb((b&(~((1<<x)-1)))|add);
        }
        x++;
    }
    for(auto x:bi){
        for(int i=a;i<x;i++){
            ckmin(ans,(i-a)+((i|x)-x)+1+x-b);
        }
        ckmin(ans,x-a+x-b);
    }
    cout<<ans<<endl;
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}
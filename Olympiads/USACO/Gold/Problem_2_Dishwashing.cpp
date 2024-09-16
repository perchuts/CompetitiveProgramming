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
int source[maxn];
stack<int>st[maxn];
int main(){_
    freopen("dishes.in", "r", stdin);
    freopen("dishes.out", "w", stdout);
    int n;cin>>n;
    int ans=n,big=0;
    for(int i=0;i<n;i++){
        int x;cin>>x;
        if(x<big){
            ans=i;break;
        }   
        for(int j=x;!source[j]&&j;j--)source[j]=x;
        while(!st[source[x]].empty()&&st[source[x]].top()<x){
            big = st[source[x]].top();
            st[source[x]].pop();
        }
        st[source[x]].push(x);
    }
    cout<<ans<<endl;
}

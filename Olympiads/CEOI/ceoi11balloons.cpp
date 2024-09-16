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
 
long double rad[2*maxn],v[2*maxn];
int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>v[i]>>rad[i];
    }
    stack<pair<long double,long double>>st;
    for(int i=1;i<=n;i++){
        long double d = v[i];
        long double r = rad[i];
        while(!st.empty()){
            ckmin(r,(d-st.top().second)*(d-st.top().second)/(4*st.top().first));
            if(r<=st.top().first)break;
            else st.pop();
        }
        cout<<fixed<<setprecision(3)<<r<<endl;
        st.push({r,d});
    }
}
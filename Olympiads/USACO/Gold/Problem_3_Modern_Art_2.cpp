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

int l[maxn],r[maxn];
vector<ii>ranges;
int main(){_
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);
    int n;cin>>n;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        if(!l[x])l[x]=i;
        r[x]=i;
    }
    for(int i=1;i<=n;i++){
        if(l[i])
            ranges.pb({l[i],r[i]});
    }
    sort(all(ranges));
    stack<ii>st;
    int ans=0;
    for(auto [l,r]:ranges){
        while(!st.empty()&&st.top().second<l)st.pop();
        if(st.size()&&st.top().second<r){
            cout<<-1<<endl;
            return 0;
        }        
        st.push({l,r});
        ckmax(ans,st.size());
    }
    cout<<ans<<endl;

}

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

ii v[10*maxn];
int n,m,d;
bool possible(int x){
    queue<int>q;
    int it = 1;
    for(int i=1;i<=n;i++){
       while(it<=m&&v[it].first==i)q.push(i),it++;
        for(int j=1;j<=x&&!q.empty();j++){
            int k = q.front();q.pop();
            if(k+d<i)return 0;
        }
    }
    return 1;
}



int main(){_
    cin>>n>>d>>m;
    for(int i=1;i<=m;i++){
        int day;
        cin>>day;
        v[i] = {day,i};
    }    
    sort(v+1,v+1+m);
    int l = 1, r = m,ans;
    while(l<=r){
        int md = l + (r-l+1)/2;
        if(possible(md)){
            ans = md,r=md-1;
        }else{
            l = md+1;
        }
    }
    int x = ans,it = 1;
    queue<ii>q;
    cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        while(it<=m&&v[it].first==i&&it<=m)q.push(v[it++]);
        for(int j=1;j<=x&&!q.empty();j++){
            auto [k,id] = q.front();q.pop();
            cout<<id<<" ";
        }
        cout<<"0\n";
    }
}
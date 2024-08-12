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

ii p[2*maxn];
int vis[2*maxn];
int a[8] = {1,-1,0,0,0,0,1,-1};
map<ii,bool>visited,mark,hasAnswer;
map<ii,ii>ans; 

void bfs(int i){
    queue<ii>q, border;
    vector<ii>restart;
    q.push({p[i].first,p[i].second});
    map<ii,bool>visitednow;
    visited[{p[i].first,p[i].second}] = visitednow[{p[i].first,p[i].second}] = 1;
    while(!q.empty()){
        auto [x,y] = q.front();q.pop();
        for(int i=0;i<4;++i){
            int x2 = a[i] + x, y2 = a[i+4] + y;
            if(!visitednow[{x2,y2}]){
                visitednow[{x2,y2}] = 1;
                if(mark[{x2,y2}]){
                    visited[{x2,y2}] = 1;
                    q.push({x2,y2});
                }else{
                    border.push({x2,y2});
                    ans[{x2,y2}] = {x2,y2};
                }
            }
        }
    }
    while(!border.empty()){
        auto [x,y] = border.front();border.pop();
        for(int i=0;i<4;++i){
            int x2 = x + a[i], y2 = y + a[i+4];
            if(visitednow[{x2,y2}]&&mark[{x2,y2}]&&!hasAnswer[{x2,y2}]){
                hasAnswer[{x2,y2}] = 1;
                ans[{x2,y2}] = ans[{x,y}];
                border.push({x2,y2});
            }
        }
    }
}


void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;++i){
        cin>>p[i].first>>p[i].second;
        mark[{p[i].first,p[i].second}] = 1;
    }
    for(int i=1;i<=n;++i){
        if(!visited[{p[i].first,p[i].second}])bfs(i);
    }
    for(int i=1;i<=n;++i){  
        cout<<ans[{p[i].first,p[i].second}].first<<" "<<ans[{p[i].first,p[i].second}].second<<endl;
    }
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;t=1;
    while(t--)solve();
}
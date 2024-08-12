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
#define inf (int)(2e9+1)
#define mod (int)(1e9+7)

using namespace std;
vector<int>g[2*maxn];
vector<int>color[2];
int ans[2*maxn];
void dfs(int x,int p,int c){
    color[c].pb(x);
    for(auto v:g[x]){
        if(v==p)continue;
        dfs(v,x,c^1);
    }
}
bool ok[2*maxn];
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        for(int i=1;i<n;i++)
        {
            int a,b;cin>>a>>b;
            g[a].pb(b);
            g[b].pb(a);
        }
        dfs(1,1,1);
        if(color[0].size()>color[1].size())swap(color[0],color[1]);
        int w=color[0].size();
        int j=0,last=1,shift=0;
        for(int i=1;i<=n;i++){
            if(last*2==i){
                shift++;
                last=i;
            }
            if((1<<shift)&w){
                ok[i]=1;
                ans[color[0][j++]]=i;
            }
        }
        j=0;
        for(int i=1;i<=n;i++){
            if(ok[i]==0)ans[color[1][j++]]=i;
        }
        
        for(int i=1;i<=n;i++)
            cout<<ans[i]<<" ";
        cout<<endl;
        for(int i=1;i<=n;i++){
            ok[i]=0;
            g[i].clear();
        }
        color[1].clear();
        color[0].clear();
        
    }   
}
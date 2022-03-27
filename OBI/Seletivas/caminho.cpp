/*
    Seletiva IOI 2015
    Caminho
    https://neps.academy/br/exercise/344
    por Gabriel Lucas
*/

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
int grid[301][301],dist[301][301];
int adj[8]={0,0,1,-1,1,-1,0,0};
int n;
bool visited[301][301];

bool bound(int x,int y){return x>=1&&y>=1&&x<=n&&y<=n;}


bool possible(int mx){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            visited[i][j]=0;
    queue<ii>q;
    q.push({1,1});
    visited[1][1]=1;
    if(grid[1][1]>mx)return 0;//verificar se o próprio inicio é maior que o upper bound (mx)
    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int x2=x+adj[i],y2=y+adj[i+4];
            if(bound(x2,y2)&&!visited[x2][y2]&&grid[x2][y2]<=mx){
                visited[x2][y2]=1;
                q.push({x2,y2});
            }
        }
    }
    return visited[n][n];
}

int bfs(int mx){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            dist[i][j]=1e9;
    queue<pair<int,ii>>q;
    dist[1][1]=1;
    q.push({1,{1,1}});
    while(!q.empty()){
        auto [d,c] = q.front();
        auto [x,y] = c;
        q.pop();
        for(int i=0;i<4;i++){
            int x2=x+adj[i],y2=y+adj[i+4];
            if(bound(x2,y2)&&dist[x2][y2]>d+1&&grid[x2][y2]<=mx){
                dist[x2][y2] = d+1;
                q.push({dist[x2][y2],{x2,y2}});
            }
        }
    }
    return dist[n][n];
}




int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>grid[i][j];
    int l=1,r=1e9;
    while(l<r){//busca binária para achar o caminho com menor peso
        int md = (l+r)/2;
        if(possible(md))r = md;
        else
            l=md+1;
    }
    cout<<l<<" "<<bfs(l)<<endl;//bfs para achar o menor caminho com o menor peso
}
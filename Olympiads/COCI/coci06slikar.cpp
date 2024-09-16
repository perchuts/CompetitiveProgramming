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

string grid[51];
int r,c,dist[51][51],mydistance[51][51];
int a[8] = {0,0,1,-1,1,-1,0,0};

int bfs(vector<ii>sources,ii start,ii dest){
    auto valid = [&](int x,int y){
        return x>=0&&y>=0&&x<r&&y<c;
    };
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            dist[i][j] = inf;
    queue<ii>q;
    for(auto [i,j]:sources){
        q.push(make_pair(i,j));
        dist[i][j] = 0;
    }
    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int x2 = x+a[i],y2 = y+a[i+4];
            if(valid(x2,y2)&&grid[x2][y2]!='D'&&grid[x2][y2]!='X'){
                if(ckmin(dist[x2][y2],dist[x][y]+1))q.push(make_pair(x2,y2));
            }
        }
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            mydistance[i][j] = inf;
            // cout<<dist[i][j]<<" \n"[j==c-1];
        }
    }
    mydistance[start.first][start.second] = 0;
    q.push(start);
    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int x2 = x+a[i],y2 = y+a[i+4];
            if(valid(x2,y2)&&dist[x2][y2]>mydistance[x][y]+1&&grid[x2][y2]!='X'){
                if(ckmin(mydistance[x2][y2],mydistance[x][y]+1))q.push(make_pair(x2,y2));
            }
        }
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            // cout<<mydistance[i][j]<<" \n"[j==c-1];
        }
    }
    return mydistance[dest.first][dest.second]==inf?-1:mydistance[dest.first][dest.second];
}


int main(){_
    cin>>r>>c;
    for(int i=0;i<r;i++)
        cin>>grid[i];    
    ii origin,destination;
    vector<ii>watersources;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(grid[i][j]=='D'){
                destination = {i,j};
            }
            if(grid[i][j]=='S'){
                origin = {i,j};
            }
            if(grid[i][j]=='*'){
                watersources.pb({i,j});
            }
        }
    }
    
    int ans = bfs(watersources,origin,destination);

    if(ans!=-1)cout<<ans<<endl;
    else cout<<"KAKTUS"<<endl;

}
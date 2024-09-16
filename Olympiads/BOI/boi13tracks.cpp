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
string grid[4000];
int h,w;
int a[8] = {-1,1,0,0,0,0,1,-1};
bool vis[4000][4000];
bool valid(int x,int y){return (x>=0&&x<h&&y>=0&&y<w);}
 
int bfs(){
    int ans = 0;
    queue<ii>q,qnext;
    bool type = grid[h-1][w-1]=='F';
    q.push({h-1,w-1});
    while(!q.empty()){
        while(!q.empty()){
            auto [x,y] = q.front();q.pop();
            for(int i=0;i<4;i++){
                int x2 = x+a[i], y2 = y+a[i+4]; 
                if(valid(x2,y2)&&!vis[x2][y2]&&grid[x2][y2]!='.'){
                    vis[x2][y2] = 1;
                    if(grid[x2][y2]==grid[x][y])q.push({x2,y2});
                    else qnext.push({x2,y2});
                }
            }
        }
        ans++;
        q = qnext;
        while(!qnext.empty())qnext.pop();
    }
  return ans;  
}
 
 
 
int main(){_
    cin>>h>>w;
    for(int i=0;i<h;i++)cin>>grid[i];
    cout<<bfs()<<endl;
}
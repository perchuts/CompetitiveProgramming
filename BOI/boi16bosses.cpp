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

/*
adding edges using bfs is the optimal way.
that is because the answer depends only on the lvl of nodes (check code).
when we build the tree this way, we make all nodes as close to the
root as possible, hence minimizing ans.
*/

vector<int>can[10001];
bool assigned[10001];
int n,tmp,lvl[10001];

bool createTree(int root){
    queue<int>q;
    q.push(root);
    int qtd = 0;
    tmp=n,assigned[root]=1;
    while(!q.empty()){
        qtd++;
        int u = q.front();
        q.pop();
        for(auto v:can[u]){
            if(!assigned[v]){
                assigned[v] = 1;
                lvl[v] = lvl[u]+1;
                tmp+=lvl[u];//smaller lvl[u] = smaller ans
                q.push(v);
            }
        }
    }
    return qtd==n;
}

int main(){_
    cin>>n;
    for(int i=1;i<=n;i++){
        int k;cin>>k;
        for(int j=1;j<=k;j++){
            int x;cin>>x;
            can[x].pb(i);
        }
    }   
    int ans = inf; 
    for(int i=1;i<=n;i++){//check for each node being the root
        for(int j=1;j<=n;j++)assigned[j] = 0,lvl[j]=1;
        if(createTree(i))ckmin(ans,tmp);
    }
    cout<<ans<<endl;
}
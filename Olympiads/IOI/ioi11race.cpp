#include <bits/stdc++.h>
#define maxn (int)(2e5 + 51)
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define ll long long
#define pb push_back
#define ull unsigned long long
#define ii pair<int, int>
#define iii tuple<int, int, int>
#define inf (int)(2e9 + 1)
#define mod (int)(1e9 + 7)

using namespace std;
vector<ii> g[maxn];
int subsz[maxn], vis[maxn];

ii cnt[5 * maxn];

int dfs(int v, int p)
{
  subsz[v] = 1;
  for (auto [u, d] : g[v])
  {
    if (u != p && !vis[u])
      subsz[v] += dfs(u, v);
  }
  return subsz[v];
}
int ans = inf, curcentroid;

int find_centroid(int u, int p, int n)
{
  for (auto [v, d] : g[u])
  {
    if (v != p && !vis[v] && subsz[v] > n / 2)
      return find_centroid(v, u, n);
  }
  return u;
}
void solve(int u, int p, int d, int k, int len, int mode)
{
  if (d > k)
    return;
  if (mode && (curcentroid != cnt[d].second || (curcentroid == cnt[d].second && cnt[d].first > len)))
    cnt[d] = {len, curcentroid};

  if (!mode && (cnt[k - d].second == curcentroid || k == d))
    ans = min(ans, cnt[k - d].first + len);

  for (auto [v, ed] : g[u])
    if(v!=p&&vis[v]==0)
        solve(v, u, d + ed, k, len + 1, mode);
}

void build(int v, int k)
{
  int centroid = find_centroid(v, -1, dfs(v, -1));
  vis[centroid] = 1;
  curcentroid = centroid;
  for (auto [u, d] : g[centroid])
  {
    if (!vis[u])
    {
      solve(u, -1, d, k, 1, 0);
      solve(u, -1, d, k, 1, 1);
    }
  }
  for (auto [u, d] : g[centroid])
    if (!vis[u])
      build(u, k);
}

int best_path(int N, int K, int H[maxn][2], int L[maxn])
{
  int n=N,k=K;
  for (int i = 0; i < n - 1; i++)
  {
    int u = H[i][0], v = H[i][1], d = L[i];
    g[u].pb({v, d});
    g[v].pb({u, d});
  }
  for (int i = 1; i <= k; i++)
    cnt[i] = {inf, -1};
  cnt[0]={0,-1};
  build(0, k);
  return (ans == inf ? -1 : ans);
}

// int h[maxn][2],l[maxn];
// int main(){
//   int n,k;cin>>n>>k;
//   for(int i=0;i<n-1;i++){
    
//     int a,b,x;cin>>a>>b>>x;
//     l[i]=x;
//     h[i][0]=a;
//     h[i][1]=b;
//   }
//   cout<<best_path(n,k,h,l)<<endl;
// }
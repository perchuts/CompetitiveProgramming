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

ii bit[10*maxn];
int pointing[10*maxn], maxj;

void insert(int x, int d,int xc){
    while(x<=maxj){
        if(ckmax(bit[x].first,d))bit[x].second = xc;
        x += x&(-x);
    }
}

ii query(int x){
    ii ans = {0,0};
    while(x){
        if(ckmax(ans.first,bit[x].first))ans.second = bit[x].second;
        x -= x&(-x);
    }
    return ans;
}

bool sorted(ii x,ii y){
    if(x.first==y.first)return x.second<y.second;
    return x.first>y.first;
}

int main(){_
    int n;cin>>n;
    vector<ii>intr(n);
    for(auto &[x,y]:intr){
        cin>>x>>y;
        ckmax(maxj,y);
    }
    sort(all(intr),sorted);
    for(int i=0;i<n;++i){
        int j = intr[i].second;
        ii q = query(j);
        pointing[i] = q.second;
        insert(j,q.first+1,i);
    }
    ii resp = query(maxj);
    cout<<resp.first<<endl;
    int cur = resp.second, cnt = 0;
    while(cur){
        cout<<intr[cur].first<<" "<<intr[cur].second<<endl;
        cur = pointing[cur], ++cnt;
    } 
    if(cnt!=resp.first)cout<<intr[cur].first<<" "<<intr[cur].second<<endl;
}
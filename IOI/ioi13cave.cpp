#include <bits/stdc++.h>
#include "cave.h"
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
int door[5001],ans[5001],tmp[5001];
int N;
 
int isHere(int x,int target,int type){
    int cnt = 0,last = -1;
    for(int i=0;i<N;i++){
        tmp[i] = ans[i];
        if(door[i]==-1){
            if(cnt<x)tmp[i] = 1;
            if(!type&&cnt<x)last = i;
            else if(x==cnt&&type) last = i;
            cnt++;
        }
    }
    if(tryCombination(tmp)==target)return last;
    return -1;
}
 
void exploreCave(int n){
    N = n;
    for(int i=0;i<n;i++)door[i]=-1;
 
    int st = tryCombination(tmp); 
    if(st==-1){
        for(int i=0;i<n;i++){
            ans[i] = 1;
            door[i] = tryCombination(ans);
            ans[i] = 0;
        }
        answer(ans,door);
        return;
    }
 
    for(int i=0;i<n;i++){
        tmp[i] = 1;
        int cur = tryCombination(tmp);
        if(cur<st&&cur!=-1)door[i] = cur;
        else if(cur>st||cur==-1)door[i] = st,ans[i] = 1;
        tmp[i] = 0;
    }
    int target = st + 1;
 
    while(target<n){
        bool type = isHere(n-target,target,0)==-1;
        int l = 0, r = n - target,resp;
        while(l<=r){
            int md = l + (r-l+1)/2;
            int cur = isHere(md,target,type);
            if(type){
                if(cur==-1)r = md - 1;
                else l = md + 1, resp = cur;
            }else{
                if(cur==-1)l = md + 1;
                else r = md - 1, resp = cur;
            }
        }
        
        ans[resp] = type, door[resp] = target++;
    }
 
    answer(ans,door);
}
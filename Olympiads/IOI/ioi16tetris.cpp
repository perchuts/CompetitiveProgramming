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
 
int n,type,newpos,newrotation,mode;
 
void init(int num){
    n = num;
}
 
void play(){
 
    if(type==1){
        newpos = 0;
        newrotation = 0;
        return;
    }
 
    switch(mode){
 
        case 0://mode = 0: empty
            if(type==2){
                newpos = 0;
                newrotation = 0;
                mode = 1;
            }else{
                newpos = 1;
                newrotation = 1;
                mode = 4;
            }
            break;
 
        case 1://mode = 1: figure 2 left
            if(type==2){
                newpos = 2;
                newrotation = 1;
                mode = 6;
            }else{
                newpos = 1;
                newrotation = 2;
                mode = 2;
            }
            break;
 
        case 2://mode = 2: figure 2 right
            if(type==2){
                newpos = 0;
                newrotation = 1;
                mode = 5;
            }else{
                newpos = 0;
                newrotation = 3;
                mode = 1;
            }
            break;
 
        //mode = 3: figure 3 left (never used)
 
        case 4://mode = 4: figure 3 right
            if(type==2){
                newpos = 0;
                newrotation = 0;
                mode = 2;
            }else{
                newpos = 0;
                newrotation = 3;
                mode = 0;
            }
            break;
 
        case 5://mode = 5: one left
            if(type==2){
                newpos = 1;
                newrotation = 0;
                mode = 0;
            }else{
                newpos = 1;
                newrotation = 1;
                mode = 6;
            }
            break;
 
        case 6://mode = 6: one right
            if(type==2){
                newpos = 0;
                newrotation = 0;
                mode = 0;
            }else{
                newpos = 0;
                newrotation = 0;
                mode = 5;
            }
            break;
    }
}
 
void new_figure(int x){
    type = x;
    play();
}
 
int get_position(){
    return newpos;
}
 
int get_rotation(){
    return newrotation;
}
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
    int a,b;
    cin>>a>>b;
    int c;
    int menor=1e9+10;
    if(2*a-b<menor)menor=2*a-b;
    if(2*b-a<menor)menor=2*b-a;
    if((a+b)/2<menor)menor=(a+b)/2;
    cout<<menor;
    return 0;
}

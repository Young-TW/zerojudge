#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    if(scanf("%d",&n)!=1) return 0;
    for(int i=0;i<n;i++){
        char buf[128];
        if(scanf("%127s",buf)!=1) break;
        bool neg=false;
        long long r=0;
        for(char* p=buf; *p; ++p){
            if(*p=='-'){ neg=true; continue; }
            if(*p<'0'||*p>'9') continue;
            r = (r*10 + (*p-'0'))%360;
        }
        if(neg) r = (360 - r) % 360;
        printf("%lld\n", r);
    }
    return 0;
}

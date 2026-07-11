#include <bits/stdc++.h>
using namespace std;

static inline int gc(){
    static char buf[1<<16];
    static int len=0,pos=0;
    if(pos==len){ len=fread(buf,1,sizeof(buf),stdin); pos=0; if(len==0) return -1;}
    return buf[pos++];
}
static inline bool readInt(int &x){
    int c=gc();
    while(c!=-1 && c!='-' && (c<'0'||c>'9')) c=gc();
    if(c==-1) return false;
    bool neg=false;
    if(c=='-'){neg=true;c=gc();}
    x=0;
    while(c>='0'&&c<='9'){x=x*10+(c-'0');c=gc();}
    if(neg)x=-x;
    return true;
}

int main(){
    int n,k;
    while(readInt(n) && readInt(k)){
        vector<int> L(n+1);
        L[0]=1;
        vector<int> prev(100005,0);
        for(int i=1;i<=n;i++){
            int x; readInt(x);
            L[i] = max(L[i-1], prev[x]+1);
            prev[x]=i;
        }
        vector<int> prev_dp(n+1,0), cur_dp(n+1,0);
        vector<int> dq(n+2);
        for(int j=1;j<=k;j++){
            int head=0, tail=0;
            cur_dp[0]=0;
            for(int i=1;i<=n;i++){
                int gi = prev_dp[i-1] - i;
                while(head<tail){
                    int t=dq[tail-1];
                    int gt = prev_dp[t-1]-t;
                    if(gt<=gi) tail--;
                    else break;
                }
                dq[tail++]=i;
                while(head<tail && dq[head]<L[i]) head++;
                int t=dq[head];
                int gt = prev_dp[t-1]-t;
                cur_dp[i] = max(cur_dp[i-1], i+1+gt);
            }
            swap(prev_dp,cur_dp);
        }
        printf("%d\n", prev_dp[n]);
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;

// A<C<G<T  -> 0,1,2,3
int mp(char c){
    switch(c){case 'A':return 0;case 'C':return 1;case 'G':return 2;case 'T':return 3;}
    return -1;
}
const char CH[4]={'A','C','G','T'};
const u64 CAP=4000000000000000000ULL; // 4e18

inline u64 add(u64 a,u64 b){ u64 s=a+b; if(s>CAP||s<a) return CAP; return s; }

int main(){
    int M,K; u64 R;
    // read multiple cases until EOF
    bool first=true;
    while(scanf("%d %d %llu",&M,&K,&R)==3){
        char buf[50005];
        if(scanf("%s",buf)!=1) break;
        string s(buf);
        // allowed[i] : bitmask of allowed chars
        vector<int> allow(M);
        for(int i=0;i<M;i++){
            if(s[i]=='N') allow[i]=0xF;
            else allow[i]=1<<mp(s[i]);
        }
        int B=K; // budget dimension 0..K-1
        // dp[i][c][b] : ways to fill s[i..M-1] with s[i]=c, internal descents (in [i,M-1]) <= b
        // store as flat vector, only need current and next -> rolling
        // dp indexed [c*B + b]
        vector<u64> cur(4*B), nxt(4*B);
        // base i=M-1
        for(int c=0;c<4;c++){
            u64 v = (allow[M-1]>>c &1)?1ULL:0ULL;
            for(int b=0;b<B;b++) cur[c*B+b]=v;
        }
        // we need dp for every i during greedy; store all
        // memory: M*4*B * 8 bytes = 50000*40*8 = 16MB
        vector<vector<u64>> DP(M);
        DP[M-1]=cur;
        for(int i=M-2;i>=0;i--){
            for(int c=0;c<4;c++){
                if(!(allow[i]>>c &1)){ for(int b=0;b<B;b++) nxt[c*B+b]=0; continue; }
                for(int b=0;b<B;b++){
                    u64 tot=0;
                    for(int c2=0;c2<4;c2++){
                        if(!(allow[i+1]>>c2 &1)) continue;
                        int din=(c2<c)?1:0;
                        if(din>b) continue;
                        tot=add(tot,DP[i+1][c2*B+(b-din)]);
                    }
                    nxt[c*B+b]=tot;
                }
            }
            DP[i]=nxt;
        }
        // greedy
        string ans(M,'?');
        int budget=K-1;
        int prev=-1;
        for(int i=0;i<M;i++){
            bool placed=false;
            for(int c=0;c<4;c++){
                if(!(allow[i]>>c &1)) continue;
                int din=(prev!=-1 && c<prev)?1:0;
                if(din>budget) continue;
                u64 ways=DP[i][c*B+(budget-din)];
                if(ways>=R){
                    ans[i]=CH[c];
                    prev=c;
                    budget-=din;
                    placed=true;
                    break;
                } else {
                    R-=ways;
                }
            }
            // placed should always be true given guarantees
            (void)placed;
        }
        if(!first) printf("\n");
        first=false;
        printf("%s\n",ans.c_str());
    }
    return 0;
}

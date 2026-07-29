#include <cstdio>
#include <cstring>
static const long long MOD = 1000000007LL;

static char inbuf[1<<16];
static int inLen=0, inPos=0;
static inline int gc(){
    if(inPos==inLen){ inLen=(int)fread(inbuf,1,sizeof(inbuf),stdin); inPos=0; if(inLen==0) return -1; }
    return inbuf[inPos++];
}
static char outbuf[1<<16];
static int outPos=0;
static inline void flushOut(){ if(outPos){ fwrite(outbuf,1,outPos,stdout); outPos=0; } }
static inline void pc(char c){ if(outPos==(int)sizeof(outbuf)) flushOut(); outbuf[outPos++]=c; }
static inline void writeNum(long long a){
    if(a==0){ pc('0'); return; }
    char rev[24]; int m=0;
    while(a){ rev[m++]=(char)('0'+(int)(a%10)); a/=10; }
    while(m) pc(rev[--m]);
}
int main(){
    int c=gc();
    while(c!=-1 && (c<'0'||c>'9')) c=gc();
    if(c==-1) return 0;
    long long T=0;
    while(c>='0'&&c<='9'){ T=T*10+(c-'0'); c=gc(); }
    while(c!=-1 && c!='\n') c=gc();
    for(long long t=0;t<T;t++){
        long long ocount=0, wcount=0, ans=0;
        while(true){
            int ch=gc();
            if(ch==-1) break;
            if(ch=='\n') break;
            if(ch=='O'){ ans+=wcount; if(ans>=MOD) ans-=MOD; ocount++; }
            else if(ch=='w'){ wcount+=ocount; if(wcount>=MOD) wcount-=MOD; }
        }
        writeNum(ans); pc('\n');
    }
    flushOut();
    return 0;
}

#include <cstdio>
#include <cstdint>
#include <vector>
#include <string>
using namespace std;

static const uint64_t B = 1000000000ULL; // base 1e9

// ---- fast input ----
static char inbuf[1<<20];
static int inLen=0, inPos=0;
static inline int gc(){
    if(inPos==inLen){ inLen=(int)fread(inbuf,1,sizeof(inbuf),stdin); inPos=0; if(inLen==0) return -1; }
    return inbuf[inPos++];
}
// read a decimal token into string of digits (most significant first). returns false on EOF.
static bool readToken(string &s){
    s.clear();
    int c=gc();
    while(c!=-1 && (c<'0'||c>'9')) c=gc();
    if(c==-1) return false;
    while(c>='0'&&c<='9'){ s.push_back((char)c); c=gc(); }
    return true;
}

// convert decimal string (MSB first) to little-endian base-1e9 limbs
static vector<uint32_t> toLimbs(const string &s){
    // strip leading zeros
    int start=0; while(start+1<(int)s.size() && s[start]=='0') start++;
    int len=(int)s.size()-start;
    int nl=(len+8)/9;
    vector<uint32_t> v(nl,0);
    int idx=0;
    int end=(int)s.size();
    // group from the least significant
    for(int pos=end; pos>start; pos-=9){
        int lo = pos-9; if(lo<start) lo=start;
        uint32_t val=0;
        for(int k=lo;k<pos;k++) val=val*10+(uint32_t)(s[k]-'0');
        v[idx++]=val;
    }
    // remove trailing zero limbs (high)
    while((int)v.size()>1 && v.back()==0) v.pop_back();
    return v;
}

// ---- fast output ----
static char outbuf[1<<20];
static int outPos=0;
static inline void flushOut(){ if(outPos){ fwrite(outbuf,1,outPos,stdout); outPos=0; } }
static inline void pc(char c){ if(outPos==(int)sizeof(outbuf)) flushOut(); outbuf[outPos++]=c; }

static void printBig(const vector<uint32_t> &q){
    // q little-endian; find highest nonzero
    int hi=(int)q.size()-1;
    while(hi>0 && q[hi]==0) hi--;
    if(hi==0 && q[0]==0){ pc('0'); pc('\n'); return; }
    // top limb no padding
    char tmp[16]; int m=0; uint32_t x=q[hi];
    if(x==0){ pc('0'); } else { while(x){ tmp[m++]='0'+(x%10); x/=10; } while(m) pc(tmp[--m]); }
    for(int i=hi-1;i>=0;i--){
        uint32_t val=q[i];
        // 9-digit zero padded
        char d[9];
        for(int k=8;k>=0;k--){ d[k]='0'+(val%10); val/=10; }
        for(int k=0;k<9;k++) pc(d[k]);
    }
    pc('\n');
}

int main(){
    string tok;
    if(!readToken(tok)) return 0;
    // T
    long long T=0; for(char c:tok) T=T*10+(c-'0');
    for(long long t=0;t<T;t++){
        string xs, ys;
        readToken(xs); readToken(ys);
        vector<uint32_t> u=toLimbs(xs); // dividend
        vector<uint32_t> v=toLimbs(ys); // divisor
        int ulen=(int)u.size();
        int n=(int)v.size();
        // if u < v -> 0
        bool uLess=false;
        if(ulen<n) uLess=true;
        else if(ulen==n){
            for(int i=ulen-1;i>=0;i--){ if(u[i]!=v[i]){ uLess = u[i]<v[i]; break; } }
        }
        if(uLess){ pc('0'); pc('\n'); continue; }

        if(n==1){
            uint64_t v0=v[0];
            vector<uint32_t> q(ulen,0);
            uint64_t rem=0;
            for(int i=ulen-1;i>=0;i--){
                uint64_t cur=rem*B + u[i];
                q[i]=(uint32_t)(cur/v0);
                rem=cur%v0;
            }
            printBig(q);
            continue;
        }

        // Knuth Algorithm D, base B, n>=2, ulen>=n
        int m=ulen-n; // quotient has m+1 limbs
        // normalize
        uint64_t d = B / ((uint64_t)v[n-1] + 1);
        vector<uint32_t> un(ulen+1,0), vn(n,0);
        // vn = v*d
        {
            uint64_t carry=0;
            for(int i=0;i<n;i++){ uint64_t p=(uint64_t)v[i]*d + carry; vn[i]=(uint32_t)(p%B); carry=p/B; }
        }
        {
            uint64_t carry=0;
            for(int i=0;i<ulen;i++){ uint64_t p=(uint64_t)u[i]*d + carry; un[i]=(uint32_t)(p%B); carry=p/B; }
            un[ulen]=(uint32_t)carry;
        }
        vector<uint32_t> q(m+1,0);
        for(int j=m;j>=0;j--){
            uint64_t num=(uint64_t)un[j+n]*B + un[j+n-1];
            uint64_t qhat=num/vn[n-1];
            uint64_t rhat=num - qhat*vn[n-1];
            while(qhat>=B || qhat*(uint64_t)vn[n-2] > B*rhat + un[j+n-2]){
                qhat--; rhat+=vn[n-1];
                if(rhat>=B) break;
            }
            // multiply and subtract
            long long borrow=0; uint64_t carry=0;
            for(int i=0;i<n;i++){
                uint64_t p=qhat*(uint64_t)vn[i] + carry;
                carry=p/B;
                long long sub=(long long)un[i+j] - borrow - (long long)(p%B);
                if(sub<0){ sub+=B; borrow=1; } else borrow=0;
                un[i+j]=(uint32_t)sub;
            }
            long long sub=(long long)un[j+n] - borrow - (long long)carry;
            if(sub<0){ sub+=B; borrow=1; } else borrow=0;
            un[j+n]=(uint32_t)sub;
            if(borrow){
                // qhat too big by 1, add back
                qhat--;
                uint64_t c=0;
                for(int i=0;i<n;i++){
                    uint64_t s=(uint64_t)un[i+j]+vn[i]+c;
                    un[i+j]=(uint32_t)(s%B); c=s/B;
                }
                un[j+n]=(uint32_t)((un[j+n]+c)%B);
            }
            q[j]=(uint32_t)qhat;
        }
        printBig(q);
    }
    flushOut();
    return 0;
}

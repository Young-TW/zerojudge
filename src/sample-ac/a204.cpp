#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef uint32_t u32;
typedef uint64_t u64;

static const u32 BASE = 1000000000u;
static const int BASE_DIGITS = 9;
// fixed-point scale: value represented as (number)*10^SCALE
// 200 gives ample guard digits beyond the 50 output digits and the
// ~22-digit cancellation that occurs for |x|<=50.
static const int SCALE = 200;
static const int OUT_DIGITS = 50;

struct Big {
    vector<u32> d; // little-endian base 1e9, normalized (no leading zero limbs)
    Big(){}
    Big(u64 v){ while(v){ d.push_back((u32)(v%BASE)); v/=BASE; } }
    bool isZero() const { return d.empty(); }
    void norm(){ while(!d.empty() && d.back()==0) d.pop_back(); }
};

int cmp(const Big&a, const Big&b){
    if(a.d.size()!=b.d.size()) return a.d.size()<b.d.size()?-1:1;
    for(int i=(int)a.d.size()-1;i>=0;i--) if(a.d[i]!=b.d[i]) return a.d[i]<b.d[i]?-1:1;
    return 0;
}

Big add(const Big&a, const Big&b){
    Big r; size_t n=max(a.d.size(),b.d.size());
    r.d.resize(n);
    u64 carry=0;
    for(size_t i=0;i<n;i++){
        u64 s=carry; if(i<a.d.size()) s+=a.d[i]; if(i<b.d.size()) s+=b.d[i];
        r.d[i]=(u32)(s%BASE); carry=s/BASE;
    }
    if(carry) r.d.push_back((u32)carry);
    r.norm();
    return r;
}

// a - b, assumes a >= b
Big sub(const Big&a, const Big&b){
    Big r; r.d.resize(a.d.size());
    u64 borrow=0;
    for(size_t i=0;i<a.d.size();i++){
        u64 av=a.d[i]; u64 bv=(i<b.d.size()?b.d[i]:0);
        u64 cur=av-bv-borrow;
        if(cur>>63){ cur+=BASE; borrow=1; } else borrow=0;
        r.d[i]=(u32)cur;
    }
    r.norm();
    return r;
}

Big mul(const Big&a, const Big&b){
    if(a.isZero()||b.isZero()) return Big();
    Big r; r.d.assign(a.d.size()+b.d.size(),0);
    for(size_t i=0;i<a.d.size();i++){
        u64 carry=0;
        for(size_t j=0;j<b.d.size();j++){
            u64 cur=(u64)a.d[i]*b.d[j]+r.d[i+j]+carry;
            r.d[i+j]=(u32)(cur%BASE);
            carry=cur/BASE;
        }
        size_t pos=i+b.d.size();
        while(carry){
            u64 cur=(u64)r.d[pos]+carry;
            r.d[pos]=(u32)(cur%BASE);
            carry=cur/BASE;
            pos++;
        }
    }
    r.norm();
    return r;
}

Big mulsmall(const Big&a, u32 m){
    if(m==0||a.isZero()) return Big();
    Big r; r.d.resize(a.d.size());
    u64 carry=0;
    for(size_t i=0;i<a.d.size();i++){
        u64 cur=(u64)a.d[i]*m+carry;
        r.d[i]=(u32)(cur%BASE); carry=cur/BASE;
    }
    while(carry){ r.d.push_back((u32)(carry%BASE)); carry/=BASE; }
    r.norm();
    return r;
}

// divide by 10^k, truncate toward zero (a >= 0)
Big divpow10(const Big&a, int k){
    if(a.isZero()) return Big();
    int q=k/BASE_DIGITS, r=k%BASE_DIGITS;
    if((int)a.d.size()<=q) return Big();
    u32 p=1; for(int i=0;i<r;i++) p*=10;
    Big res; res.d.resize(a.d.size()-q);
    u64 rem=0;
    for(int i=(int)a.d.size()-1;i>=0;i--){
        u64 cur=rem*BASE+a.d[i];
        u32 qv=(u32)(cur/p);
        rem=cur%p;
        if(i-q>=0) res.d[i-q]=qv;
    }
    res.norm();
    return res;
}

// multiply by 10^k
Big mulpow10(const Big&a, int k){
    if(a.isZero()) return Big();
    int q=k/BASE_DIGITS, r=k%BASE_DIGITS;
    Big res; res.d.assign(q,0);
    res.d.insert(res.d.end(), a.d.begin(), a.d.end());
    u32 p=1; for(int i=0;i<r;i++) p*=10;
    res=mulsmall(res,p);
    res.norm();
    return res;
}

// divide by small m (m<BASE), truncate toward zero
Big divsmall(const Big&a, u32 m){
    if(a.isZero()) return Big();
    Big r; r.d.resize(a.d.size());
    u64 rem=0;
    for(int i=(int)a.d.size()-1;i>=0;i--){
        u64 cur=rem*BASE+a.d[i];
        r.d[i]=(u32)(cur/m);
        rem=cur%m;
    }
    r.norm();
    return r;
}

Big fromDecimal(const string&s){
    vector<u32> limbs;
    int n=(int)s.size(), pos=n;
    while(pos>0){
        int start=max(0,pos-BASE_DIGITS);
        u32 v=0;
        for(int i=start;i<pos;i++) v=v*10+(u32)(s[i]-'0');
        limbs.push_back(v);
        pos=start;
    }
    Big r; r.d=limbs; r.norm();
    return r;
}

string toDecimal(const Big&a){
    if(a.isZero()) return "0";
    string s=to_string(a.d.back());
    for(int i=(int)a.d.size()-2;i>=0;i--){
        string t=to_string(a.d[i]);
        while(t.size()<(size_t)BASE_DIGITS) t="0"+t;
        s+=t;
    }
    return s;
}

struct SBig{ bool neg=false; Big mag; };

void addTo(SBig&s, const Big&t){
    if(t.isZero()) return;
    if(!s.neg){ s.mag=add(s.mag,t); }
    else{
        if(cmp(s.mag,t)>=0){ s.mag=sub(s.mag,t); if(s.mag.isZero()) s.neg=false; }
        else { s.mag=sub(t,s.mag); s.neg=false; }
    }
}
void subFrom(SBig&s, const Big&t){
    if(t.isZero()) return;
    if(!s.neg){
        if(cmp(s.mag,t)>=0){ s.mag=sub(s.mag,t); if(s.mag.isZero()) s.neg=false; }
        else { s.mag=sub(t,s.mag); s.neg=true; }
    } else { s.mag=add(s.mag,t); }
}

int main(){
    string s;
    while(cin>>s){
        bool sx=false; size_t i=0;
        if(!s.empty() && s[0]=='-'){ sx=true; i=1; }
        else if(!s.empty() && s[0]=='+'){ i=1; }
        string intpart, fracpart; bool dot=false;
        for(; i<s.size(); i++){
            if(s[i]=='.'){ dot=true; continue; }
            if(!dot) intpart+=s[i]; else fracpart+=s[i];
        }
        if(intpart.empty()) intpart="0";
        string digits=intpart+fracpart;
        size_t first=0; while(first<digits.size()-1 && digits[first]=='0') first++;
        digits=digits.substr(first);
        Big b=fromDecimal(digits);
        Big Y=mulpow10(b, SCALE-(int)fracpart.size());
        // sin(y), y=|x| ; series with exact bigint accumulation
        Big Y2=mul(Y,Y); Y2=divpow10(Y2,SCALE);
        Big term=Y;
        SBig sum; sum.neg=false; sum.mag=Y;
        if(!Y.isZero()){
            for(long long k=1;k<300000;k++){
                term=mul(term,Y2);
                term=divpow10(term,SCALE);
                term=divsmall(term,(u32)(2*k));
                term=divsmall(term,(u32)(2*k+1));
                if(term.isZero()) break;
                if(k&1) subFrom(sum,term); else addTo(sum,term);
            }
        }
        bool resultNeg = sum.mag.isZero() ? false : (sum.neg ^ sx);
        Big M=divpow10(sum.mag, SCALE-OUT_DIGITS); // floor(|sin|*10^50)
        string full=toDecimal(M);
        string intstr, fracstr;
        if((int)full.size()<=OUT_DIGITS){
            intstr="0";
            fracstr=full;
            while((int)fracstr.size()<OUT_DIGITS) fracstr="0"+fracstr;
        } else {
            intstr=full.substr(0, full.size()-OUT_DIGITS);
            fracstr=full.substr(full.size()-OUT_DIGITS);
        }
        string out=(resultNeg?"-":"")+intstr+"."+fracstr;
        printf("%s\n", out.c_str());
    }
    return 0;
}

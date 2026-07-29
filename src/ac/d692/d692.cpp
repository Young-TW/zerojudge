// d692 - 矢量星球 (fast). Self-written.
// Rofu draws odd rounds, Yin even. A vector must be orthogonal to all previous
// accepted vectors; the first vector that isn't -> its drawer loses.
// Fast orthogonality-against-all check via randomized linear combination:
//   A[i] = sum_j r_j * u_j[i] (mod p) over accepted vectors j.
//   dot(v,A) = sum_j r_j * (v . u_j). If v _|_ all u_j it's 0; else nonzero whp.
// Two independent instances mod p make false-positive prob ~ (1/p)^2.
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef unsigned __int128 u128;

static const u64 P = 2305843009213693951ULL; // 2^61 - 1 (prime)

static u64 sm_state;
static inline u64 splitmix64(){
    sm_state += 0x9e3779b97f4a7c15ULL;
    u64 z = sm_state;
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
    z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
    return z ^ (z >> 31);
}
static inline u64 randMod(){ return splitmix64() % (P - 1) + 1; } // in [1, P-1]

int main(){
    // read all input
    string buf;
    {
        std::ios::sync_with_stdio(false);
        std::ostringstream ss;
        ss << std::cin.rdbuf();
        buf = ss.str();
    }
    // replace ':' with space so everything is whitespace-separated integers
    for(char &c : buf) if(c==':') c=' ';
    const char* s = buf.c_str();
    size_t pos = 0, len = buf.size();

    auto nextInt = [&](long long &out)->bool{
        while(pos<len){ char c=s[pos]; if((c>='0'&&c<='9')||c=='-') break; pos++; }
        if(pos>=len) return false;
        bool neg=false;
        if(s[pos]=='-'){ neg=true; pos++; }
        long long v=0; bool any=false;
        while(pos<len && s[pos]>='0'&&s[pos]<='9'){ v=v*10+(s[pos]-'0'); pos++; any=true; }
        if(!any) return false;
        out = neg? -v : v;
        return true;
    };

    sm_state = 0x123456789abcdefULL;

    vector<u64> A1, A2;               // per-coordinate accumulators
    vector<size_t> touched;           // coords modified this test (for reset)

    auto ensure = [&](size_t c){
        if(c >= A1.size()){ A1.resize(c+1, 0); A2.resize(c+1, 0); }
    };

    string out;
    long long n, m;
    // pair buffers (k <= 100)
    static long long bi[128], bd[128];

    while(nextInt(n)){
        if(!nextInt(m)) break;
        if(n==0 && m==0) break;

        bool decided=false;
        const char* answer=nullptr;

        for(long long round=1; round<=m; ++round){
            long long k;
            if(!nextInt(k)) { k=0; }
            for(long long i=0;i<k;i++){
                long long ii, dd;
                nextInt(ii); nextInt(dd);
                bi[i]=ii; bd[i]=dd;
            }
            if(decided) continue; // just consume input

            // compute s1, s2 = dot(v, A) mod P
            u128 s1=0, s2=0;
            for(long long i=0;i<k;i++){
                long long c = bi[i];
                if(c<0) continue;
                u64 a1 = ((size_t)c < A1.size()) ? A1[c] : 0;
                u64 a2 = ((size_t)c < A2.size()) ? A2[c] : 0;
                if(bd[i] > 0){ s1 += a1; s2 += a2; }
                else { s1 += (a1? P - a1 : 0); s2 += (a2? P - a2 : 0); }
            }
            bool orth = ( (u64)(s1 % P) == 0 ) && ( (u64)(s2 % P) == 0 );

            if(orth){
                // accept new vector: add random weights
                u64 r1 = randMod(), r2 = randMod();
                for(long long i=0;i<k;i++){
                    long long c = bi[i];
                    if(c<0) continue;
                    ensure((size_t)c);
                    u64 add1 = (bd[i] > 0) ? r1 : (P - r1);
                    u64 add2 = (bd[i] > 0) ? r2 : (P - r2);
                    A1[c] = (A1[c] + add1) % P;
                    A2[c] = (A2[c] + add2) % P;
                    touched.push_back((size_t)c);
                }
            } else {
                decided = true;
                // round odd -> Rofu drew -> Yin wins; even -> Rofu wins
                answer = (round & 1) ? "Yin" : "Rofu";
            }
        }

        if(!decided) answer = "Hakuna matata";
        out += answer;
        out += '\n';

        // reset accumulators for next test
        for(size_t c : touched){ A1[c]=0; A2[c]=0; }
        touched.clear();
    }

    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}

// b485 音高: given a (waveshaped) sine-wave sound, recover the note name.
//
// Idea: waveshaping f(x)=a5 x^5 + a3 x^3 + a1 x (coeffs >=0, sum 1) is an odd,
// monotonic-increasing map on [-1,1], so it PRESERVES the sign of each sample:
//   sign(signal[t]) == sign(sin(2*pi*f*t/R))   (except rounding-to-0 near crossings).
// Note frequencies are f = 440 * 2^((idx-57)/12), idx = octave*12 + pc, A4=440.
// Octave in 1..7, pc in 0..11 -> 84 candidates, all below Nyquist (<4000 Hz).
// For each candidate count sign mismatches; the true note has ~0 mismatches while
// any wrong candidate drifts in phase over the samples and disagrees a lot.
// Tie-break (needed only for truncated/short inputs) by least-squares fit to a
// pure sine of amplitude 32767.
#include <bits/stdc++.h>
using namespace std;

static const char* NAMES[12] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};

static bool parseInt(const string& s, long long& out){
    if(s.empty()) return false;
    size_t i=0; bool neg=false;
    if(s[0]=='+'||s[0]=='-'){ if(s.size()==1) return false; neg=(s[0]=='-'); i=1; }
    for(size_t k=i;k<s.size();++k) if(!isdigit((unsigned char)s[k])) return false;
    try { out = stoll(s); } catch(...) { return false; }
    (void)neg; return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // read all whitespace tokens (>> already strips \r, spaces, newlines)
    vector<string> tok; { string t; while(cin>>t) tok.push_back(t); }
    size_t pos=0;
    auto nextInt=[&](long long& v)->bool{
        while(pos<tok.size()){
            if(parseInt(tok[pos],v)){ pos++; return true; }
            return false; // non-int token -> stop (garbage / label)
        }
        return false;
    };

    string outbuf;
    long long R, N;
    while(true){
        // read header R N (skip stray non-int tokens between cases)
        if(!nextInt(R)) { // skip one garbage token and retry once
            if(pos<tok.size()){ pos++; continue; }
            break;
        }
        if(!nextInt(N)) break;
        if(N<0) N=0;
        vector<long long> sig; sig.reserve((size_t)min<long long>(N, 100000));
        long long v;
        for(long long k=0;k<N;++k){ if(!nextInt(v)) break; sig.push_back(v); }
        long long M=(long long)sig.size();
        if(M==0){ continue; }
        double Rr = (R>0? (double)R : 8000.0);

        // candidates
        double bestMismRatio=1e18; long long bestMism=LLONG_MAX; int bestIdx=-1;
        // store per-candidate mismatch to find ties
        struct Cand{int idx; long long mism; long long valid;};
        vector<Cand> cands;
        for(int oct=1;oct<=7;++oct){
            for(int pc=0;pc<12;++pc){
                int idx=oct*12+pc;
                double f = 440.0 * pow(2.0,(idx-57)/12.0);
                if(f<=0 || f>=Rr/2.0) continue; // above Nyquist -> impossible
                long long mism=0, valid=0;
                for(long long t=0;t<M;++t){
                    if(sig[t]==0) continue;
                    double ph = f*(double)t/Rr;
                    ph -= floor(ph);
                    double s = sin(2.0*M_PI*ph);
                    if(fabs(s)<1e-9) continue; // predicted crossing -> ambiguous
                    int ps = (s>0)?1:-1;
                    int as = (sig[t]>0)?1:-1;
                    valid++;
                    if(ps!=as) mism++;
                }
                cands.push_back({idx,mism,valid});
                double ratio = valid? (double)mism/valid : 1e18;
                if(mism<bestMism || (mism==bestMism && ratio<bestMismRatio)){
                    bestMism=mism; bestMismRatio=ratio; bestIdx=idx;
                }
            }
        }
        // gather ties (same minimal mismatch) and break by pure-sine LSQ
        long long minM=LLONG_MAX; for(auto&c:cands) minM=min(minM,c.mism);
        int chosen=bestIdx; double bestErr=1e300; bool tie=false;
        int cntMin=0; for(auto&c:cands) if(c.mism==minM) cntMin++;
        if(cntMin>1){
            tie=true;
            for(auto&c:cands){
                if(c.mism!=minM) continue;
                double f = 440.0*pow(2.0,(c.idx-57)/12.0);
                double err=0;
                for(long long t=0;t<M;++t){
                    double ph=f*(double)t/Rr; ph-=floor(ph);
                    double pred=32767.0*sin(2.0*M_PI*ph);
                    double d=(double)sig[t]-pred; err+=d*d;
                }
                if(err<bestErr){ bestErr=err; chosen=c.idx; }
            }
        }
        (void)tie;
        int O=chosen/12, PC=chosen%12;
        outbuf += NAMES[PC];
        outbuf += to_string(O);
        outbuf += "\n";
    }
    cout<<outbuf;
    return 0;
}

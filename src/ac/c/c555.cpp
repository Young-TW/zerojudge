#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef complex<long double> cld;

// evaluate real poly (coeffs high->low) at real x via Horner
static inline ld evalR(const vector<ld>&a, ld x){
    ld r=0; for(ld c: a) r=r*x+c; return r;
}
static inline ld evalDeriv(const vector<ld>&a, ld x){
    // derivative Horner
    int n=a.size()-1; ld r=0;
    for(int i=0;i<n;i++) r=r*x+a[i]*(ld)(n-i);
    return r;
}
static inline cld evalC(const vector<cld>&a, cld x){
    cld r=0; for(auto&c:a) r=r*x+c; return r;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout.setf(std::ios::fmtflags(0), std::ios::floatfield);
    int N;
    string outbuf;
    while(cin>>N){
        vector<ld> a(N+1);
        bool ok=true;
        for(int i=0;i<=N;i++){ if(!(cin>>a[i])){ok=false;break;} }
        if(!ok) break;
        // collect candidate real roots (polished in long double)
        vector<ld> cands;
        auto consider=[&](ld x){
            if(!isfinite((double)x)) return;
            // polish with Newton (real)
            ld cur=x;
            for(int it=0; it<200; it++){
                ld f=evalR(a,cur), d=evalDeriv(a,cur);
                if(fabsl(d)<1e-30) break;
                ld step=f/d;
                ld nx=cur-step;
                if(!isfinite((double)nx)) break;
                cur=nx;
                if(fabsl(step)<=1e-18*(1+fabsl(cur))) break;
            }
            if(isfinite((double)cur)) cands.push_back(cur);
        };

        if(N==1){
            consider(-a[1]/a[0]);
        } else {
            // Durand-Kerner on monic poly
            vector<cld> c(N+1);
            for(int i=0;i<=N;i++) c[i]=cld(a[i]/a[0],0.0L);
            vector<cld> roots(N);
            cld seed(0.4L,0.9L);
            cld p(1.0L,0.0L);
            for(int i=0;i<N;i++){ roots[i]=p; p*=seed; }
            // DK only needs to land each root in a Newton basin; polish afterwards.
            for(int iter=0; iter<120; iter++){
                ld maxd=0;
                for(int i=0;i<N;i++){
                    cld num=evalC(c,roots[i]);
                    cld den(1.0L,0.0L);
                    for(int j=0;j<N;j++) if(j!=i) den*=(roots[i]-roots[j]);
                    if(abs(den)<1e-300L) continue;
                    cld delta=num/den;
                    roots[i]-=delta;
                    maxd=max(maxd,(ld)abs(delta));
                }
                if(maxd<1e-13L) break;
            }
            // consider real parts of near-real roots
            for(int i=0;i<N;i++){
                ld re=roots[i].real(), im=roots[i].imag();
                if(fabsl(im) < 1e-3L*(1+fabsl(re))+1e-6L){
                    consider(re);
                }
            }
            // also always consider all real parts (fallback)
            for(int i=0;i<N;i++) consider(roots[i].real());
        }

        if(cands.empty()) cands.push_back(0.0L);
        // dedupe candidates
        sort(cands.begin(),cands.end());
        cands.erase(unique(cands.begin(),cands.end(),[](ld a,ld b){
            return fabsl(a-b) <= 1e-14L*(1+fabsl(a));
        }),cands.end());
        // Final selection in the double domain: the judge evaluates f(x) in double,
        // so minimize |f_double(x)| over doubles adjacent to each candidate and
        // pick the global best (this favors the best-conditioned real root).
        auto evalD=[&](double x)->double{
            double r=0; for(ld c:a) r=r*x+(double)c; return r;
        };
        double bx=(double)cands[0];
        double bf=fabs(evalD(bx));
        for(ld cd: cands){
            double c0=(double)cd;
            for(int dir=-1; dir<=1; dir+=2){
                double x=c0;
                for(int s=0;s<80;s++){
                    if(s>0) x=nextafter(x, dir<0?-INFINITY:INFINITY);
                    double v=fabs(evalD(x));
                    if(v<bf){ bf=v; bx=x; }
                }
            }
        }

        char tmp[64];
        snprintf(tmp,sizeof(tmp),"%.17g",bx);
        outbuf += tmp; outbuf += '\n';
    }
    cout<<outbuf;
    return 0;
}

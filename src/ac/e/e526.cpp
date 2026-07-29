#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld NEG = -1e300L, POS = 1e300L;

// solve one test case: numbers, and operator multiset counts p(+) m(-) t(*) d(/)
ld solveCase(const vector<ld>& num, int p, int m, int t, int d){
    int N = num.size();
    // maxTerm[i][j][g], minTerm[i][j][g]: value of term over numbers [i..j) with exactly g divisions among the (len-1) non-leading numbers
    // i inclusive, j exclusive, len=j-i, g in [0,len-1]
    // store as vectors indexed
    // maxT[i][j] is vector over g
    vector<vector<vector<ld>>> maxT(N+1, vector<vector<ld>>(N+1));
    vector<vector<vector<ld>>> minT(N+1, vector<vector<ld>>(N+1));
    for(int i=0;i<N;i++){
        for(int j=i+1;j<=N;j++){
            int len=j-i;
            vector<ld> mx(len, NEG), mn(len, POS);
            // bucket g -> (max,min) of partial product
            mx[0]=num[i]; mn[0]=num[i];
            for(int k=i+1;k<j;k++){
                ld x=num[k];
                int cur=k-i; // number of others processed so far after this = cur; buckets up to cur-1 valid before, now up to cur
                // process from high g to low to avoid overwrite; use temp
                vector<ld> nmx(len,NEG), nmn(len,POS);
                for(int g=0; g<=cur-1; g++){
                    if(mx[g]==NEG && mn[g]==POS) continue; // empty
                    // mult: same g
                    ld a=mx[g]*x, b=mn[g]*x;
                    nmx[g]=max(nmx[g], max(a,b));
                    nmn[g]=min(nmn[g], min(a,b));
                    // div: g+1
                    if(fabsl(x)>1e-15L){
                        ld a2=mx[g]/x, b2=mn[g]/x;
                        nmx[g+1]=max(nmx[g+1], max(a2,b2));
                        nmn[g+1]=min(nmn[g+1], min(a2,b2));
                    }
                }
                mx=nmx; mn=nmn;
            }
            maxT[i][j]=mx; minT[i][j]=mn;
        }
    }
    // global dp[i][a][b][e]: max accumulated sum covering [0..i) using a plus-seps, b minus-seps, e divisions
    // c (mult) = (i-1) - (a+b) - e  must be >=0; number of terms = a+b+1
    // dims
    auto idx=[&](int i,int a,int b,int e){ return ((i*(p+1)+a)*(m+1)+b)*(d+1)+e; };
    int SZ=(N+1)*(p+1)*(m+1)*(d+1);
    vector<ld> dp(SZ, NEG);
    // start: first term from i=0
    // dp base handled by first-term transitions
    // We'll iterate i ascending.
    // initialize a virtual state: before any term, i=0. Represent by processing first term specially.
    // Use dp for states with at least one term completed.
    for(int j=1;j<=N;j++){
        int len=j-0;
        for(int g=0; g<len; g++){
            // first term added, sign +
            int e=g;
            if(e>d) continue;
            int a=0,b=0;
            // c = (j-1)-(a+b)-e = (j-1)-e must be >=0
            if((j-1)-e<0) continue;
            ld v=maxT[0][j][g];
            if(v==NEG) continue;
            ld &cell=dp[idx(j,a,b,e)];
            cell=max(cell, v);
        }
    }
    for(int i=1;i<=N;i++){
        for(int a=0;a<=p;a++)for(int b=0;b<=m;b++)for(int e=0;e<=d;e++){
            ld base=dp[idx(i,a,b,e)];
            if(base==NEG) continue;
            // add a new term [i..j)
            for(int j=i+1;j<=N;j++){
                int len=j-i;
                for(int g=0; g<len; g++){
                    int ne=e+g;
                    if(ne>d) continue;
                    // plus separator
                    if(a+1<=p){
                        ld v=maxT[i][j][g];
                        if(v!=NEG){
                            ld nv=base+v;
                            ld &cell=dp[idx(j,a+1,b,ne)];
                            cell=max(cell,nv);
                        }
                    }
                    // minus separator: contribution -termvalue, maximize => minimize termvalue
                    if(b+1<=m){
                        ld v=minT[i][j][g];
                        if(v!=POS){
                            ld nv=base-v;
                            ld &cell=dp[idx(j,a,b+1,ne)];
                            cell=max(cell,nv);
                        }
                    }
                }
            }
        }
    }
    return dp[idx(N,p,m,d)];
}

// classify line
bool isOpLine(const vector<string>& toks){
    if(toks.empty()) return false;
    for(auto&s:toks){ if(!(s=="+"||s=="-"||s=="*"||s=="/")) return false; }
    return true;
}
int main(){
    string line;
    vector<double> pendingNums; bool haveNums=false;
    vector<string> outv;
    while(getline(cin,line)){
        // strip \r
        while(!line.empty() && (line.back()=='\r'||line.back()=='\n'||line.back()==' '||line.back()=='\t')) line.pop_back();
        // find first non-space
        size_t st=line.find_first_not_of(" \t");
        if(st==string::npos) continue; // blank
        if(line[st]=='#') continue; // comment
        // tokenize
        stringstream ss(line); string tk; vector<string> toks;
        while(ss>>tk) toks.push_back(tk);
        if(toks.empty()) continue;
        if(isOpLine(toks)){
            if(!haveNums) continue; // orphan operator line
            int p=0,mn=0,t=0,dd=0;
            for(auto&s:toks){ if(s=="+")p++; else if(s=="-")mn++; else if(s=="*")t++; else dd++; }
            vector<ld> num(pendingNums.begin(), pendingNums.end());
            ld res=solveCase(num,p,mn,t,dd);
            double rv=(double)res;
            double r=round(rv*100.0)/100.0;
            if(fabs(r)<1e-9) r=0.0;
            char buf[64]; snprintf(buf,sizeof(buf),"%.2f", r);
            outv.push_back(string(buf));
            haveNums=false; pendingNums.clear();
        } else {
            // numbers line: parse doubles; ignore tokens that aren't numeric
            vector<double> nums; bool ok=true;
            for(auto&s:toks){ try{ size_t pos; double v=stod(s,&pos); if(pos!=s.size()){ok=false;break;} nums.push_back(v);}catch(...){ok=false;break;} }
            if(!ok || nums.size()<2) continue;
            pendingNums=nums; haveNums=true;
        }
    }
    for(auto&s:outv) cout<<s<<"\n";
    return 0;
}

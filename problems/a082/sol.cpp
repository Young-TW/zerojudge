#include <bits/stdc++.h>
using namespace std;

// Modern symbol ids: 0-9 digits, 10='+', 11='*', 12='='
// Two-phase search:
//   Phase 1: choose which appearing symbols are '=', '+', '*' (or NONE for +/*),
//            validate the arithmetic *skeleton* of every line (structure only).
//   Phase 2: assign decimal digit values to the remaining (digit) symbols,
//            evaluate each equation for equality (with leading-zero rule).
// Collect all valid full bijections; a correspondence is output iff it is the
// same across every valid bijection. Output sorted; "noway" if none valid.

int gmap[13];
bool usedDigit[13];      // digits 0-9 in use during phase 2
bool appears[13];
bool mustDigit[13];      // appears at a line boundary or self-adjacent -> cannot be operator/=
bool eqOk[13];           // count exactly 1 in every line -> eligible for '='
vector<int> linesOf[13]; // unique line indices containing symbol
vector<vector<int> > distinctSyms; // per line: distinct appearing symbols
vector<string> lines;
int remaining[1005];

int numAppearing;
vector<int> appList;

// determination bookkeeping
bool ambiguous[13];
int img[13];
bool haveFirst;
long long solCount;
set<int> leftoverSet;
bool stopFlag;

// phase-2 state
vector<int> digitOrder;
int eqSym, plusSym, starSym;
bool cantZero[13];  // symbol is the leading digit of some multi-digit number
bool configStop;    // all of this config's digit symbols already ambiguous -> cut

char mc(int id){ if(id<10) return char('0'+id); if(id==10) return '+'; if(id==11) return '*'; return '='; }

bool evalSide(const vector<int>& s, long long& out){
    int n = s.size();
    if(n==0) return false;
    long long sum=0, term=1;
    int i=0; bool haveTerm=false;
    while(i<n){
        if(s[i]>=10) return false;
        int start=i; long long num=0;
        while(i<n && s[i]<10){ num=num*10+s[i]; i++; }
        if(i-start>=2 && s[start]==0) return false; // leading zero
        term*=num; haveTerm=true;
        if(i<n){
            if(s[i]==11){ i++; if(i>=n) return false; }
            else if(s[i]==10){ sum+=term; term=1; i++; if(i>=n) return false; }
            else return false;
        }
    }
    if(!haveTerm) return false;
    sum+=term; out=sum; return true;
}

// full evaluation once all symbols of the line are assigned
bool validLine(const string& line){
    vector<int> whole; whole.reserve(line.size());
    int eqpos=-1, eqcount=0;
    for(size_t k=0;k<line.size();k++){ int id=gmap[line[k]-'a']; whole.push_back(id); if(id==12){ eqcount++; eqpos=(int)k; } }
    if(eqcount!=1) return false;
    vector<int> L(whole.begin(), whole.begin()+eqpos);
    vector<int> R(whole.begin()+eqpos+1, whole.end());
    long long lv,rv;
    if(!evalSide(L,lv)) return false;
    if(!evalSide(R,rv)) return false;
    return lv==rv;
}

// structural (skeleton) validity given operator roles; digit values unknown
bool structuralValid(const string& line){
    int n=line.size();
    // role: 0 digit, 1 operator(+/*), 2 '='
    int eqcount=0;
    int prevRole=-1;
    for(int i=0;i<n;i++){
        int g=line[i]-'a';
        int role = (g==eqSym)?2 : (g==plusSym||g==starSym)?1 : 0;
        if(i==0 && role!=0) return false;      // must start with digit
        if(i==n-1 && role!=0) return false;    // must end with digit
        if(prevRole>0 && role>0) return false; // two adjacent non-digits
        if(role==2) eqcount++;
        prevRole=role;
    }
    return eqcount==1;
}

// min/max bound of a side [l,r) using current partial assignment (free digit = [lo,9])
void sideBound(const string& line, int l, int r, long long& smin, long long& smax){
    smin=0; smax=0;
    long long tmin=1, tmax=1;
    int i=l;
    while(i<r){
        int start=i;
        while(i<r){ int g=line[i]-'a'; if(g!=eqSym && g!=plusSym && g!=starSym) i++; else break; }
        int len=i-start;
        long long nmin=0, nmax=0;
        for(int p=start;p<i;p++){ int g=line[p]-'a'; int v=gmap[g];
            int lo,hi;
            if(v>=0){ lo=hi=v; }
            else { lo=(p==start && len>=2)?1:0; hi=9; }
            nmin=nmin*10+lo; nmax=nmax*10+hi;
        }
        tmin*=nmin; tmax*=nmax;
        if(i<r){ int g=line[i]-'a';
            if(g==starSym){ i++; }
            else if(g==plusSym){ smin+=tmin; smax+=tmax; tmin=1; tmax=1; i++; }
        }
    }
    smin+=tmin; smax+=tmax;
}

// necessary condition: the two sides' value ranges must overlap
bool boundFeasible(const string& line){
    int n=line.size(), eqpos=-1;
    for(int i=0;i<n;i++) if(line[i]-'a'==eqSym){ eqpos=i; break; }
    long long Lmin,Lmax,Rmin,Rmax;
    sideBound(line,0,eqpos,Lmin,Lmax);
    sideBound(line,eqpos+1,n,Rmin,Rmax);
    return Lmax>=Rmin && Rmax>=Lmin;
}

void recordSolution(){
    solCount++;
    for(size_t a=0;a<appList.size();a++){ int g=appList[a];
        if(!haveFirst) img[g]=gmap[g];
        else if(gmap[g]!=img[g]) ambiguous[g]=true;
    }
    haveFirst=true;
    if(numAppearing==12){
        bool pres[13]={false};
        for(size_t a=0;a<appList.size();a++) pres[gmap[appList[a]]]=true;
        for(int m=0;m<13;m++) if(!pres[m]){ leftoverSet.insert(m); break; }
    }
    bool allAmb=true;
    for(size_t a=0;a<appList.size();a++) if(!ambiguous[appList[a]]){ allAmb=false; break; }
    if(allAmb){
        if(numAppearing!=12) stopFlag=true;
        else if(leftoverSet.size()>=2) stopFlag=true;
    }
    // per-config cut: once every digit symbol of this operator config is
    // ambiguous, more solutions from this config add no determination info
    // (operator symbols are fixed within the config).
    bool allDig=true;
    for(size_t j=0;j<digitOrder.size();j++) if(!ambiguous[digitOrder[j]]){ allDig=false; break; }
    if(allDig) configStop=true;
}

void dfsDigits(int depth){
    if(stopFlag || configStop) return;
    if(depth==(int)digitOrder.size()){ recordSolution(); return; }
    int g=digitOrder[depth];
    for(int d=0; d<10; d++){
        if(usedDigit[d]) continue;
        if(d==0 && cantZero[g]) continue;
        gmap[g]=d; usedDigit[d]=true;
        bool ok=true; int dec=0;
        vector<int>& ls=linesOf[g];
        for(size_t idx=0; idx<ls.size(); idx++){
            int li=ls[idx]; remaining[li]--; dec++;
            if(remaining[li]==0){ if(!validLine(lines[li])){ ok=false; break; } }
            else if(!boundFeasible(lines[li])){ ok=false; break; }
        }
        if(ok) dfsDigits(depth+1);
        for(int j=0;j<dec;j++) remaining[ls[j]]++;
        gmap[g]=-1; usedDigit[d]=false;
        if(stopFlag || configStop) return;
    }
}

void runPhase2(){
    // digit symbols = appearing minus operators
    digitOrder.clear();
    for(size_t a=0;a<appList.size();a++){ int g=appList[a];
        if(g!=eqSym && g!=plusSym && g!=starSym) digitOrder.push_back(g);
    }
    if((int)digitOrder.size()>10) return; // impossible to give distinct digits
    // structural validity of every line
    for(size_t i=0;i<lines.size();i++) if(!structuralValid(lines[i])) return;
    // magnitude feasibility with all digits free (kills e.g. 2d+2d=4d configs)
    for(size_t i=0;i<lines.size();i++) if(!boundFeasible(lines[i])) return;
    // order digit symbols by frequency (lines count) descending
    sort(digitOrder.begin(), digitOrder.end(), [](int x,int y){ return linesOf[x].size()>linesOf[y].size(); });
    // remaining = number of distinct digit symbols per line
    for(size_t li=0; li<lines.size(); li++){
        int cnt=0;
        for(size_t j=0;j<distinctSyms[li].size();j++){ int g=distinctSyms[li][j];
            if(g!=eqSym && g!=plusSym && g!=starSym) cnt++;
        }
        remaining[li]=cnt;
    }
    // leading-digit-of-multi-digit-number -> cannot be 0
    for(int g=0;g<13;g++) cantZero[g]=false;
    for(size_t li=0; li<lines.size(); li++){
        const string& s=lines[li]; int n=s.size();
        int i=0;
        while(i<n){
            int g=s[i]-'a';
            bool isDigit = (g!=eqSym && g!=plusSym && g!=starSym);
            if(isDigit){
                int start=i;
                while(i<n){ int gg=s[i]-'a'; if(gg!=eqSym && gg!=plusSym && gg!=starSym) i++; else break; }
                if(i-start>=2) cantZero[s[start]-'a']=true; // multi-digit number's lead
            } else i++;
        }
    }
    for(int d=0;d<10;d++) usedDigit[d]=false;
    configStop=false;
    dfsDigits(0);
}

void solveCase(int N){
    lines.clear();
    for(int i=0;i<N;i++){ string s; cin>>s; lines.push_back(s); }
    for(int g=0;g<13;g++){ appears[g]=false; mustDigit[g]=false; eqOk[g]=true; linesOf[g].clear(); ambiguous[g]=false; gmap[g]=-1; img[g]=-1; }
    haveFirst=false; solCount=0; leftoverSet.clear(); stopFlag=false; appList.clear();
    distinctSyms.assign(N, vector<int>());

    for(int li=0; li<N; li++){
        const string& s=lines[li];
        int cnt[13]={0};
        for(size_t i=0;i<s.size();i++){
            int g=s[i]-'a';
            appears[g]=true; cnt[g]++;
            if(i==0 || i+1==s.size()) mustDigit[g]=true;
            if(i+1<s.size() && s[i+1]==s[i]) mustDigit[g]=true;
        }
        for(int g=0;g<13;g++){ if(cnt[g]!=1) eqOk[g]=false; }
        for(int g=0;g<13;g++) if(cnt[g]>0){ linesOf[g].push_back(li); distinctSyms[li].push_back(g); }
    }

    numAppearing=0;
    for(int g=0;g<13;g++) if(appears[g]){ numAppearing++; appList.push_back(g); }

    // Phase 1: choose operators
    vector<int> eqCand, opCandBase;
    for(int g=0;g<13;g++) if(appears[g]){
        if(eqOk[g] && !mustDigit[g]) eqCand.push_back(g);
        if(!mustDigit[g]) opCandBase.push_back(g);
    }
    for(size_t ei=0; ei<eqCand.size() && !stopFlag; ei++){
        eqSym=eqCand[ei]; gmap[eqSym]=12;
        vector<int> plusCand; plusCand.push_back(-1);
        for(size_t j=0;j<opCandBase.size();j++) if(opCandBase[j]!=eqSym) plusCand.push_back(opCandBase[j]);
        for(size_t pi=0; pi<plusCand.size() && !stopFlag; pi++){
            plusSym=plusCand[pi]; if(plusSym!=-1) gmap[plusSym]=10;
            vector<int> starCand; starCand.push_back(-1);
            for(size_t j=0;j<opCandBase.size();j++){ int g=opCandBase[j]; if(g!=eqSym && g!=plusSym) starCand.push_back(g); }
            for(size_t si=0; si<starCand.size() && !stopFlag; si++){
                starSym=starCand[si]; if(starSym!=-1) gmap[starSym]=11;
                runPhase2();
                if(starSym!=-1) gmap[starSym]=-1;
            }
            if(plusSym!=-1) gmap[plusSym]=-1;
        }
        gmap[eqSym]=-1;
    }

    if(solCount==0){ printf("noway\n"); return; }

    vector<pair<int,int> > res;
    for(size_t a=0;a<appList.size();a++){ int g=appList[a]; if(!ambiguous[g]) res.push_back(make_pair(g, img[g])); }
    if(numAppearing==12 && leftoverSet.size()==1){
        int ng=-1; for(int g=0;g<13;g++) if(!appears[g]){ ng=g; break; }
        if(ng>=0) res.push_back(make_pair(ng, *leftoverSet.begin()));
    }
    sort(res.begin(), res.end());
    for(size_t i=0;i<res.size();i++){ putchar(char('a'+res[i].first)); putchar(mc(res[i].second)); putchar('\n'); }
}

int main(){
    int N;
    while(cin>>N){ solveCase(N); }
    return 0;
}
